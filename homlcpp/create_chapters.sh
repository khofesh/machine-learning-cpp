#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")"

for i in $(seq -w 1 14); do
    mkdir -p "chapter0$i"
done
