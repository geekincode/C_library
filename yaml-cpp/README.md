# YAML-CPP 教程项目

本项目演示了如何在C++中使用[yaml-cpp](https://github.com/jbeder/yaml-cpp)库来解析和生成YAML文件。

## 功能特性

- 解析YAML文件
- 创建和修改YAML节点
- 遍历YAML数据结构
- 错误处理
- 单元测试示例

## 先决条件

- C++17兼容的编译器
- CMake 3.14或更高版本
- yaml-cpp库

### 安装yaml-cpp

#### Ubuntu/Debian:
```bash
sudo apt-get install libyaml-cpp-dev
```

#### CentOS/RHEL/Fedora:
```bash
# CentOS/RHEL
sudo yum install yaml-cpp-devel
# Fedora
sudo dnf install yaml-cpp-devel
```

#### macOS (使用Homebrew):
```bash
brew install yaml-cpp
```

#### Windows (使用vcpkg):
```bash
vcpkg install yaml-cpp
```

## 构建项目

```bash
cd yaml-cpp-tutorial
mkdir build
cd build
cmake ..
make
```

## 运行示例

```bash
./bin/yaml_example
```

## 运行测试

```bash
ctest
```
或者
```bash
./bin/yaml_test
```

## 项目结构

```
├── CMakeLists.txt          # 构建配置
├── include/                # 头文件
│   └── yaml_utils.h        # 工具函数声明
├── src/                    # 源代码
│   ├── main.cpp            # 主程序
│   └── yaml_utils.cpp      # 工具函数实现
├── examples/               # 示例YAML文件
│   ├── example1.yaml       # 基本示例
│   ├── example2.yaml       # 复杂示例
│   └── generated.yaml      # 程序生成的YAML文件
└── tests/                  # 测试代码
    └── test_yaml.cpp       # 单元测试
```