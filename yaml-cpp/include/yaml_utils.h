#ifndef YAML_UTILS_H
#define YAML_UTILS_H

#include "yaml-cpp/yaml.h"
#include <iostream>
#include <string>
#include <vector>

namespace YAMLUtils {
    // 解析YAML文件
    YAML::Node loadFromFile(const std::string& filename);
    
    // 保存YAML到文件
    void saveToFile(const YAML::Node& node, const std::string& filename);
    
    // 打印YAML节点信息
    void printNodeInfo(const YAML::Node& node, const std::string& prefix = "");
    
    // 遍历并打印YAML节点
    void traverseNode(const YAML::Node& node, const std::string& prefix = "");
    
    // 创建示例YAML结构
    YAML::Node createSampleNode();
    
    // 演示基本操作
    void demonstrateBasicOperations();
    
    // 演示序列操作
    void demonstrateSequenceOperations();
    
    // 演示映射操作
    void demonstrateMapOperations();
    
    // 演示自定义类型转换
    struct Person {
        std::string name;
        int age;
        std::string email;
    };
    
    void demonstrateCustomTypeConversion();
}

// 为Person结构体重载<<操作符
std::ostream& operator<<(std::ostream& os, const YAMLUtils::Person& person);

#endif // YAML_UTILS_H