#!/bin/bash
# filepath: /workspaces/edgin/scripts/dev_startup.sh

set -e

## Whisper.cpp
# Set the target directory for whisper.cpp
WHISPER_DIR="backend/logic_unit/external/whisper.cpp"

# Only clone if not already present
if [ ! -d "$WHISPER_DIR" ]; then
    echo "Cloning whisper.cpp into $WHISPER_DIR..."
    mkdir -p "$(dirname "$WHISPER_DIR")"
    git clone https://github.com/ggml-org/whisper.cpp.git "$WHISPER_DIR"
else
    echo "whisper.cpp already exists at $WHISPER_DIR, skipping clone."
fi

# Download the base model if it doesn't exist
MODEL_DIR="$WHISPER_DIR/models"
MODEL_FILE="$MODEL_DIR/ggml-base.en.bin"
if [ ! -f "$MODEL_FILE" ]; then
    echo "Downloading Whisper base.en model..."
    cd $MODEL_DIR
    sh ./download-ggml-model.sh base.en
else
    echo "Whisper base.en model already exists at $MODEL_FILE, skipping download."
fi

## libsndfile
# Set the target directory
LIBSNDFILE_DIR="backend/logic_unit/external/libsndfile"

# Only clone if not already present
if [ ! -d "$LIBSNDFILE_DIR" ]; then
    echo "Cloning libsndfile into $LIBSNDFILE_DIR..."
    mkdir -p "$(dirname "$LIBSNDFILE_DIR")"
    git clone https://github.com/libsndfile/libsndfile.git "$LIBSNDFILE_DIR"
else
    echo "libsndfile already exists at $LIBSNDFILE_DIR, skipping clone."
fi

echo "External dependencies setup complete."