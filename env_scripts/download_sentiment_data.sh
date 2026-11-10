#!/usr/bin/env bash
set -euo pipefail

# Downloads the IMDB sentiment corpus used by homlcpp/chapter011/pytorch
# (sentiment-pytorch) and can create a small subset for smoke tests.
#
# Primary source: the original aclImdb_v1 archive from Stanford.
# Fallback: the HuggingFace parquet mirror (https://huggingface.co/datasets/stanfordnlp/imdb),
# converted to the plain-text layout the sample expects.

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
REPO_ROOT=$(cd "${SCRIPT_DIR}/.." && pwd)

DEST="${REPO_ROOT}/development/datasets"
SUBSET=0
URL="https://ai.stanford.edu/~amaas/data/sentiment/aclImdb_v1.tar.gz"
HF_URL="https://huggingface.co/datasets/stanfordnlp/imdb/resolve/main/plain_text/train-00000-of-00001.parquet"

usage() {
  cat <<EOF
Usage: $(basename "$0") [-d destination] [-n subset_size]

  -d  directory to extract into (default: ${DEST})
  -n  also create <destination>/aclImdb_small with N reviews per class
  -h  show this help
EOF
}

while getopts ":d:n:h" opt; do
  case "$opt" in
    d) DEST="$OPTARG" ;;
    n) SUBSET="$OPTARG" ;;
    h) usage; exit 0 ;;
    :) echo "Missing argument for -$OPTARG" >&2; usage; exit 1 ;;
    \?) echo "Unknown option: -$OPTARG" >&2; usage; exit 1 ;;
  esac
done

case "$SUBSET" in
  ''|*[!0-9]*) echo "Subset size must be a non-negative integer" >&2; exit 1 ;;
esac

mkdir -p "$DEST"
DEST=$(cd "$DEST" && pwd)

download() {
  local url=$1 out=$2
  if command -v curl >/dev/null 2>&1; then
    curl -fL --connect-timeout 20 --progress-bar -o "${out}" "${url}"
  else
    wget -O "${out}" "${url}"
  fi
}

download_archive() {
  local archive="${DEST}/aclImdb_v1.tar.gz"
  echo "Downloading ${URL}"
  if ! download "${URL}" "${archive}"; then
    rm -f "${archive}"
    return 1
  fi
  tar xzf "${archive}" -C "${DEST}" || { rm -f "${archive}"; return 1; }
  rm -f "${archive}"
}

download_huggingface() {
  if ! python3 -c 'import pyarrow.parquet' >/dev/null 2>&1; then
    echo "Stanford download failed and python3 + pyarrow are not available for the HuggingFace fallback" >&2
    echo "Install with: pip install pyarrow" >&2
    return 1
  fi

  local parquet="${DEST}/imdb_train.parquet"
  echo "Downloading HuggingFace mirror ${HF_URL}"
  download "${HF_URL}" "${parquet}"

  python3 - "${parquet}" "${DEST}/aclImdb/train" <<'PY'
import os
import sys

import pyarrow.parquet as pq

parquet_path, out_dir = sys.argv[1], sys.argv[2]
table = pq.read_table(parquet_path, columns=["text", "label"])
texts = table.column("text").to_pylist()
labels = table.column("label").to_pylist()

dirs = {0: os.path.join(out_dir, "neg"), 1: os.path.join(out_dir, "pos")}
for path in dirs.values():
    os.makedirs(path, exist_ok=True)

counters = {0: 0, 1: 0}
for text, label in zip(texts, labels):
    counters[label] += 1
    with open(os.path.join(dirs[label], f"{counters[label]:05d}.txt"), "w") as f:
        f.write(text)

print(f"Wrote {counters[0]} negative and {counters[1]} positive reviews")
PY

  rm -f "${parquet}"
}

if [ -d "${DEST}/aclImdb/train/pos" ] && [ -d "${DEST}/aclImdb/train/neg" ]; then
  echo "aclImdb already extracted in ${DEST}"
else
  if ! download_archive; then
    echo "Falling back to the HuggingFace mirror"
    download_huggingface
  fi
fi

if [ ! -d "${DEST}/aclImdb/train/pos" ] || [ ! -d "${DEST}/aclImdb/train/neg" ]; then
  echo "Unexpected layout: expected ${DEST}/aclImdb/train/{pos,neg}" >&2
  exit 1
fi

echo "IMDB corpus: ${DEST}/aclImdb"

dataset="${DEST}/aclImdb"

if [ "${SUBSET}" -gt 0 ]; then
  small="${DEST}/aclImdb_small"
  rm -rf "${small}"
  mkdir -p "${small}/train/pos" "${small}/train/neg"
  for label in pos neg; do
    mapfile -t files < <(find "${DEST}/aclImdb/train/${label}" -maxdepth 1 -type f | head -n "${SUBSET}")
    for file in "${files[@]}"; do
      cp "${file}" "${small}/train/${label}/"
    done
  done
  echo "Smoke-test subset: ${small}"
  dataset="${small}"
fi

cat <<EOF

Next: export a TorchScript BERT once (requires Python torch + transformers):
  python3 -m venv .venv && . .venv/bin/activate
  pip install "transformers<5" torch tqdm
  (cd homlcpp/chapter011/pytorch && python export.py)

Then run:
  build/homlcpp/chapter011/pytorch/sentiment-pytorch \\
    ${dataset} homlcpp/chapter011/pytorch/vocab.txt homlcpp/chapter011/pytorch/bert_model.pt
EOF
