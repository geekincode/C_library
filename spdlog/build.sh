#!/bin/bash

# 构建spdlog示例项目的脚本

echo "Creating build directory..."
mkdir -p build
cd build

echo "Running CMake..."
cmake ..

if [ $? -eq 0 ]; then
    echo "Building project..."
    cmake --build .
    
    if [ $? -eq 0 ]; then
        echo "Build successful!"
        echo ""
        echo "To run the basic example:"
        echo "  cd build && ./SpdlogExample"
        echo ""
        echo "To run the advanced example:"
        echo "  cd build && ./spdlog_example"
        echo ""
        echo "Log files will be created in the 'logs' directory."
    else
        echo "Build failed!"
        exit 1
    fi
else
    echo "CMake configuration failed!"
    exit 1
fi