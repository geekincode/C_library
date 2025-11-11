cmake_minimum_required(VERSION 3.14)
project(SpdlogExample)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置默认构建类型为Debug（如果未指定）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# 查找系统已安装的spdlog
find_package(spdlog REQUIRED)

# 添加可执行文件
add_executable(main src/main.cpp)
add_executable(spdlog_example src/example.cpp)

# 链接系统spdlog库
target_link_libraries(main PRIVATE spdlog::spdlog)
target_link_libraries(spdlog_example PRIVATE spdlog::spdlog)