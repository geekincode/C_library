cmake_minimum_required(VERSION 3.10)
project(fmt_example)

# 设置 C++11 标准（fmt 库所需）
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行文件
add_executable(test1 src/test1.cpp)
add_executable(test2 src/test2.cpp)

# 使用header-only模式的fmt库
# target_compile_definitions(test1 PRIVATE FMT_HEADER_ONLY)