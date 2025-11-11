#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include <iostream>

int main()
{
    try 
    {
        // 控制台日志输出
        spdlog::info("Welcome to spdlog version {}!", SPDLOG_VERSION);
        spdlog::warn("Easy padding in numbers like {:08d}", 12);
        spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
        spdlog::info("Support for floats {:03.2f}", 1.23456);
        spdlog::info("Positional args are {1} {0}..", "too", "supported");
        spdlog::info("{:>8} aligned, {:<8} aligned", "right", "left");

        // 创建基本文件日志记录器
        auto file_logger = spdlog::basic_logger_mt("file_logger", "../logs/basic-log.txt");
        file_logger->info("Welcome to spdlog basic file logging!");
        file_logger->info("Another message to file logger");

        // 创建循环文件日志记录器 (保留5个文件，每个文件最大1MB)
        auto rotating_logger = spdlog::rotating_logger_mt("rotating_logger", "../logs/rotating-log.txt", 1048576, 5);
        rotating_logger->info("Welcome to spdlog rotating file logging!");
        
        // 记录大量消息以演示循环日志
        for (int i = 0; i < 10000; ++i) {
            rotating_logger->info("Message #{}", i);
        }

        // 演示日志级别
        spdlog::set_level(spdlog::level::debug); // 设置全局日志级别
        spdlog::debug("This message should be displayed now");
        
        // 输出所有日志到文件
        spdlog::info("All loggers can be retrieved by name");
        auto logger = spdlog::get("file_logger");
        if (logger) {
            logger->info("Retrieved file logger by name");
        }

        // 刷新所有日志
        spdlog::shutdown();
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
        return 1;
    }
    
    return 0;
}