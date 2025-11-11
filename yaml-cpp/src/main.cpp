#include "yaml_utils.h"
#include <iostream>
#include <fstream>

int main() {
    std::cout << "YAML-CPP 教程示例程序" << std::endl;
    std::cout << "========================" << std::endl << std::endl;
    
    // 演示基本操作
    YAMLUtils::demonstrateBasicOperations();
    
    // 演示序列操作
    YAMLUtils::demonstrateSequenceOperations();
    
    // 演示映射操作
    YAMLUtils::demonstrateMapOperations();
    
    // 演示自定义类型转换
    YAMLUtils::demonstrateCustomTypeConversion();
    
    // 加载并处理YAML文件
    std::cout << "=== 加载和处理YAML文件 ===" << std::endl;
    
    // 尝试加载第一个示例文件
    YAML::Node example1 = YAMLUtils::loadFromFile("example1.yaml");
    if (example1) {
        std::cout << "example1.yaml 内容:" << std::endl;
        std::cout << example1 << std::endl;
        std::cout << std::endl;
        
        std::cout << "详细遍历 example1.yaml:" << std::endl;
        YAMLUtils::traverseNode(example1);
        std::cout << std::endl;
    }
    
    // 尝试加载第二个示例文件
    YAML::Node example2 = YAMLUtils::loadFromFile("example2.yaml");
    if (example2) {
        std::cout << "example2.yaml 内容:" << std::endl;
        std::cout << example2 << std::endl;
        std::cout << std::endl;
        
        std::cout << "详细遍历 example2.yaml:" << std::endl;
        YAMLUtils::traverseNode(example2);
        std::cout << std::endl;
    }
    
    // 创建并保存新的YAML文件
    std::cout << "=== 创建并保存新的YAML文件 ===" << std::endl;
    YAML::Node sampleNode = YAMLUtils::createSampleNode();
    std::cout << "创建的示例节点:" << std::endl;
    std::cout << sampleNode << std::endl;
    
    YAMLUtils::saveToFile(sampleNode, "generated.yaml");
    std::cout << "已保存到 generated.yaml" << std::endl;
    
    // 演示错误处理
    std::cout << "=== 错误处理演示 ===" << std::endl;
    YAML::Node nonExistent = YAMLUtils::loadFromFile("nonexistent.yaml");
    if (!nonExistent) {
        std::cout << "成功检测到文件不存在错误" << std::endl;
    }
    
    return 0;
}