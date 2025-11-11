#include "yaml_utils.h"
#include <iostream>
#include <fstream>
#include <cassert>

namespace YAMLUtils {
    YAML::Node loadFromFile(const std::string& filename) {
        try {
            return YAML::LoadFile(filename);
        } catch (const YAML::Exception& e) {
            std::cerr << "Error loading YAML file: " << e.what() << std::endl;
            return YAML::Node();
        }
    }
    
    void saveToFile(const YAML::Node& node, const std::string& filename) {
        std::ofstream fout(filename);
        fout << node;
        fout.close();
    }
    
    void printNodeInfo(const YAML::Node& node, const std::string& prefix) {
        switch (node.Type()) {
            case YAML::NodeType::Null:
                std::cout << prefix << "(null)" << std::endl;
                break;
            case YAML::NodeType::Scalar:
                std::cout << prefix << "(scalar): " << node.as<std::string>() << std::endl;
                break;
            case YAML::NodeType::Sequence:
                std::cout << prefix << "(sequence): " << node.size() << " elements" << std::endl;
                break;
            case YAML::NodeType::Map:
                std::cout << prefix << "(map): " << node.size() << " pairs" << std::endl;
                break;
            case YAML::NodeType::Undefined:
                std::cout << prefix << "(undefined)" << std::endl;
                break;
        }
    }
    
    void traverseNode(const YAML::Node& node, const std::string& prefix) {
        switch (node.Type()) {
            case YAML::NodeType::Null:
                std::cout << prefix << "(null)" << std::endl;
                break;
            case YAML::NodeType::Scalar:
                std::cout << prefix << node.as<std::string>() << std::endl;
                break;
            case YAML::NodeType::Sequence:
                for (std::size_t i = 0; i < node.size(); i++) {
                    traverseNode(node[i], prefix + "[" + std::to_string(i) + "] ");
                }
                break;
            case YAML::NodeType::Map:
                for (YAML::const_iterator it = node.begin(); it != node.end(); ++it) {
                    std::cout << prefix << it->first.as<std::string>() << ": " << std::endl;
                    traverseNode(it->second, prefix + "  ");
                }
                break;
            case YAML::NodeType::Undefined:
                std::cout << prefix << "(undefined)" << std::endl;
                break;
        }
    }
    
    YAML::Node createSampleNode() {
        YAML::Node node;
        node["name"] = "John Doe";
        node["age"] = 35;
        node["email"] = "john.doe@example.com";
        node["address"]["street"] = "123 Main Street";
        node["address"]["city"] = "Anytown";
        node["address"]["country"] = "USA";
        node["hobbies"].push_back("reading");
        node["hobbies"].push_back("swimming");
        node["hobbies"].push_back("coding");
        return node;
    }
    
    void demonstrateBasicOperations() {
        std::cout << "=== 基本操作演示 ===" << std::endl;
        
        // 创建一个简单的YAML节点
        YAML::Node node;
        node["key"] = "value";
        node["number"] = 3.14;
        node["flag"] = true;
        
        std::cout << "创建的节点内容:" << std::endl;
        std::cout << node << std::endl;
        
        // 访问节点值
        std::cout << "访问节点值:" << std::endl;
        std::cout << "key: " << node["key"].as<std::string>() << std::endl;
        std::cout << "number: " << node["number"].as<double>() << std::endl;
        std::cout << "flag: " << node["flag"].as<bool>() << std::endl;
        
        // 检查键是否存在
        if (node["key"]) {
            std::cout << "key存在" << std::endl;
        }
        
        if (!node["nonexistent"]) {
            std::cout << "nonexistent键不存在" << std::endl;
        }
        
        std::cout << std::endl;
    }
    
    void demonstrateSequenceOperations() {
        std::cout << "=== 序列操作演示 ===" << std::endl;
        
        // 创建序列
        YAML::Node seqNode;
        seqNode["items"].push_back("apple");
        seqNode["items"].push_back("banana");
        seqNode["items"].push_back("orange");
        
        std::cout << "创建的序列:" << std::endl;
        std::cout << seqNode << std::endl;
        
        // 遍历序列
        std::cout << "遍历序列元素:" << std::endl;
        for (std::size_t i = 0; i < seqNode["items"].size(); i++) {
            std::cout << "  [" << i << "]: " << seqNode["items"][i].as<std::string>() << std::endl;
        }
        
        // 使用迭代器遍历序列
        std::cout << "使用迭代器遍历:" << std::endl;
        for (YAML::const_iterator it = seqNode["items"].begin(); it != seqNode["items"].end(); ++it) {
            std::cout << "  - " << it->as<std::string>() << std::endl;
        }
        
        std::cout << std::endl;
    }
    
    void demonstrateMapOperations() {
        std::cout << "=== 映射操作演示 ===" << std::endl;
        
        // 创建映射
        YAML::Node mapNode(YAML::NodeType::Map);
        mapNode["name"] = "Alice";
        mapNode["age"] = 25;
        mapNode["job"] = "Engineer";
        
        std::cout << "创建的映射:" << std::endl;
        std::cout << mapNode << std::endl;
        
        // 遍历映射
        std::cout << "遍历映射键值对:" << std::endl;
        for (YAML::const_iterator it = mapNode.begin(); it != mapNode.end(); ++it) {
            std::cout << "  " << it->first.as<std::string>() << ": " << it->second.as<std::string>() << std::endl;
        }
        
        // 检查键是否存在
        if (mapNode["name"]) {
            std::cout << "姓名: " << mapNode["name"].as<std::string>() << std::endl;
        }
        
        std::cout << std::endl;
    }
    
    void demonstrateCustomTypeConversion() {
        std::cout << "=== 自定义类型转换演示 ===" << std::endl;
        
        // 创建Person对象
        Person person;
        person.name = "Bob Smith";
        person.age = 30;
        person.email = "bob.smith@example.com";
        
        // 转换为YAML节点
        YAML::Node node;
        node["name"] = person.name;
        node["age"] = person.age;
        node["email"] = person.email;
        
        std::cout << "Person对象转换为YAML:" << std::endl;
        std::cout << node << std::endl;
        
        // 从YAML节点创建Person对象
        Person person2;
        person2.name = node["name"].as<std::string>();
        person2.age = node["age"].as<int>();
        person2.email = node["email"].as<std::string>();
        
        std::cout << "从YAML创建的Person对象:" << std::endl;
        std::cout << person2 << std::endl;
        
        std::cout << std::endl;
    }
}

// 为Person结构体重载<<操作符
std::ostream& operator<<(std::ostream& os, const YAMLUtils::Person& person) {
    os << "Name: " << person.name << ", Age: " << person.age << ", Email: " << person.email;
    return os;
}