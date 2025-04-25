#!/bin/bash

# Detect if Homebrew is installed
if ! command -v brew &> /dev/null; then
    echo "Homebrew is not installed. Please install Homebrew first:"
    echo '/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"'
    exit 1
fi

# Make sure we're in the project directory
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR"

# Check if we need to install freeglut first
if ! brew list freeglut &>/dev/null; then
    echo "Installing freeglut dependency..."
    brew install freeglut
fi

# Install from local formula
echo "Installing solar-system from local formula..."
brew install --build-from-source ./solar-system.rb

echo "Installation complete! You can now run 'solar-system' from your terminal." 