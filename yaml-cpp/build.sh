#!/bin/bash

# YAML-CPP 教程项目构建脚本

echo "YAML-CPP 教程项目构建脚本"
echo "========================="

# 检查是否安装了必要的工具
if ! command -v cmake &> /dev/null
then
    echo "错误: 未找到 cmake，请先安装 cmake"
    exit 1
fi

if ! command -v g++ &> /dev/null && ! command -v clang++ &> /dev/null
then
    echo "错误: 未找到 C++ 编译器"
    exit 1
fi

# 创建构建目录
echo "创建构建目录..."
mkdir -p build
cd build

# 配置项目
echo "配置项目..."
cmake ..

# 构建项目
echo "构建项目..."
make -j$(nproc)

if [ $? -eq 0 ]; then
    echo "构建成功!"
    echo "可执行文件位于: build/bin/yaml_example"
    echo "运行示例: cd build && ./bin/yaml_example"
else
    echo "构建失败!"
    exit 1
fi