#!/bin/bash

# Check if project name is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <ProjectName> [ProjectPath]"
    exit 1
fi

PROJECT_NAME=$1
DEFAULT_PROJECT_PATH="../../"  # Default location outside Neun
PROJECT_PATH=${2:-$DEFAULT_PROJECT_PATH}

# Convert project path to an absolute path
PROJECT_PATH=$(realpath "$PROJECT_PATH")

# Define the Neun installation path
NEUN_PATH="/usr/local/Neun/0.3.2"

# Check if Neun exists
if [ ! -d "$NEUN_PATH" ]; then
    echo "⚠️  Warning: Neun library not found at $NEUN_PATH"
    echo "   Please make sure you first run 'make install'"
    exit 1
fi

# Create the project structure
mkdir -p "$PROJECT_PATH/$PROJECT_NAME"/{src,bin,build}

# Create a sample main.cpp file
cat > "$PROJECT_PATH/$PROJECT_NAME/src/main.cpp" <<EOL
#include <iostream>

int main() {
    std::cout << "Hello, Neun!" << std::endl;
    return 0;
}
EOL

# Create the CMakeLists.txt file
cat > "$PROJECT_PATH/$PROJECT_NAME/CMakeLists.txt" <<EOL
cmake_minimum_required(VERSION 3.10)
project($PROJECT_NAME)

# Enable C++11 or higher
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the path where the Neun library is installed
set(NEUN_PATH "$NEUN_PATH")

# Include the Neun headers
include_directories(\${NEUN_PATH})

# Find all source files automatically
file(GLOB SOURCES "src/*.cpp")

# Set the output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \${CMAKE_SOURCE_DIR}/bin)

# Create the executable
add_executable(\${PROJECT_NAME} \${SOURCES})
EOL

# Success message
echo "✅ Project '$PROJECT_NAME' created successfully at '$PROJECT_PATH/$PROJECT_NAME'"
echo "To build and run:"
echo "cd $PROJECT_PATH/$PROJECT_NAME/build"
echo "cmake .."
echo "make"
echo "../bin/$PROJECT_NAME"
