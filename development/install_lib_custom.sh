#!/usr/bin/env bash
set -x
set -e

START_DIR=$(pwd)
REPOSITORY=$1
COMMIT_HASH=$2
shift; shift;
EXTRA_COMMAND=$@

cd $START_DIR/libs/sources
REPO_NAME=$(basename "$REPOSITORY" .git)

# Check if repository directory already exists
if [ -d "$REPO_NAME" ]; then
    echo "Repository $REPO_NAME already exists, updating..."
    cd "$REPO_NAME"
    
    # Store current remote URL to check if it matches
    CURRENT_REMOTE=$(git config --get remote.origin.url || echo "")
    
    # If remotes don't match, warn but continue
    if [ "$CURRENT_REMOTE" != "$REPOSITORY" ]; then
        echo "WARNING: Existing repository has different remote URL: $CURRENT_REMOTE"
        echo "Expected: $REPOSITORY"
        echo "Continuing with existing repository..."
    fi
    
    # Fetch latest changes
    git fetch origin
else
    # Clone if not exists
    git clone $REPOSITORY
    cd "$REPO_NAME"
fi

# Checkout desired commit/tag/branch
git checkout $COMMIT_HASH || git checkout -b $COMMIT_HASH

# Fix git modules if they exist
if [ -f ".gitmodules" ]; then
    sed -i 's/git:\/\//https:\/\//g' ".gitmodules"
fi

# Update submodules
git submodule update --init --recursive
$EXTRA_COMMAND
cd ..
rm -rf build
cd $START_DIR

