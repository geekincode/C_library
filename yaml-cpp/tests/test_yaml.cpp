#include "yaml_utils.h"
#include <iostream>
#include <cassert>

int main() {
    std::cout << "运行YAML-CPP测试..." << std::endl;
    
    // 测试基本节点创建
    YAML::Node node;
    node["test"] = "value";
    assert(node["test"].as<std::string>() == "value");
    std::cout << "✓ 基本节点创建测试通过" << std::endl;
    
    // 测试序列操作
    YAML::Node seqNode;
    seqNode["items"].push_back("item1");
    seqNode["items"].push_back("item2");
    assert(seqNode["items"].size() == 2);
    assert(seqNode["items"][0].as<std::string>() == "item1");
    std::cout << "✓ 序列操作测试通过" << std::endl;
    
    // 测试映射操作
    YAML::Node mapNode(YAML::NodeType::Map);
    mapNode["key1"] = "value1";
    mapNode["key2"] = "value2";
    assert(mapNode.size() == 2);
    std::cout << "✓ 映射操作测试通过" << std::endl;
    
    // 测试文件加载
    YAML::Node example = YAMLUtils::loadFromFile("example1.yaml");
    if (example) {
        assert(example["name"].as<std::string>() == "John Smith");
        std::cout << "✓ 文件加载测试通过" << std::endl;
    } else {
        std::cout << "⚠ 文件加载测试跳过（文件不存在）" << std::endl;
    }
    
    // 测试节点类型检查
    YAML::Node nullNode;
    assert(nullNode.IsNull());
    YAML::Node scalarNode = YAML::Node("scalar");
    assert(scalarNode.IsScalar());
    YAML::Node sequenceNode = YAML::Node(YAML::NodeType::Sequence);
    assert(sequenceNode.IsSequence());
    YAML::Node mapNode2 = YAML::Node(YAML::NodeType::Map);
    assert(mapNode2.IsMap());
    std::cout << "✓ 节点类型检查测试通过" << std::endl;
    
    // 测试创建示例节点
    YAML::Node sampleNode = YAMLUtils::createSampleNode();
    assert(sampleNode["name"].as<std::string>() == "John Doe");
    assert(sampleNode["age"].as<int>() == 35);
    assert(sampleNode["hobbies"].size() == 3);
    std::cout << "✓ 创建示例节点测试通过" << std::endl;
    
    std::cout << "所有测试通过!" << std::endl;
    return 0;
}