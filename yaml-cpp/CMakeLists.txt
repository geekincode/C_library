cmake_minimum_required(VERSION 3.14)
project(YAML_CPP_TUTORIAL VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 查找yaml-cpp包
find_package(PkgConfig REQUIRED)
pkg_check_modules(YAML_CPP REQUIRED yaml-cpp)

# 包含头文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${YAML_CPP_INCLUDE_DIRS})

# 创建可执行文件
add_executable(yaml_example 
    src/main.cpp
    src/yaml_utils.cpp
)

# 链接yaml-cpp库
target_link_libraries(yaml_example PRIVATE ${YAML_CPP_LIBRARIES})

# 复制示例YAML文件到构建目录
configure_file(examples/example1.yaml ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/example1.yaml COPYONLY)
configure_file(examples/example2.yaml ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/example2.yaml COPYONLY)

# 启用测试
enable_testing()

# 添加测试可执行文件
add_executable(yaml_test tests/test_yaml.cpp src/yaml_utils.cpp)
target_include_directories(yaml_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(yaml_test PRIVATE ${YAML_CPP_LIBRARIES})

# 添加测试
add_test(NAME YAMLParserTest COMMAND yaml_test)