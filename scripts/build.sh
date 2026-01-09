#!/bin/bash
# Build script for Personal Finance Tracker

echo "🔨 Building Personal Finance Tracker..."

# Get the project root directory (parent of the scripts directory)
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

echo "🔨 Building Personal Finance Tracker..."

# Create build directory in the project root
mkdir -p "$PROJECT_ROOT/build"
cd "$PROJECT_ROOT/build"

# Run CMake
echo "📦 Running CMake..."
cmake "$PROJECT_ROOT"

# Build the project
echo "🔧 Compiling..."
make

# Check if build was successful
if [ $? -eq 0 ]; then
    echo "✅ Build successful!"
    echo "Run ./build/finance_tracker to start the application"
else
    echo "❌ Build failed!"
    exit 1
fi
