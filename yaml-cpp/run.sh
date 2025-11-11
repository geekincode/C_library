#!/bin/bash

# 运行YAML-CPP教程示例

BUILD_DIR="build"

# 如果构建目录不存在，则创建它
if [ ! -d "$BUILD_DIR" ]; then
    echo "构建目录不存在，正在创建..."
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    cmake ..
    make
    cd ..
fi

# 复制示例文件到构建目录
echo "复制示例YAML文件到构建目录..."
cp examples/example1.yaml examples/example2.yaml "$BUILD_DIR"/

# 运行示例程序
echo "运行示例程序..."
cd "$BUILD_DIR"
./bin/yaml_example

echo ""
echo "程序执行完成。生成的YAML文件:"
cat generated.yaml