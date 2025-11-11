#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/fmt/bin_to_hex.h"
#include <iostream>
#include <memory>

void async_example();
void syslog_example();
void custom_example();

int main(int, char* [])
{
    try
    {
        // 创建控制台日志记录器（带颜色）
        auto console = spdlog::stdout_color_mt("console");
        console->info("Welcome to spdlog!");
        console->error("Some error message with arg: {}", 1);
        
        // 格式化日志
        console->warn("Easy padding in numbers like {:08d}", 12);
        console->critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
        console->info("Support for floats {:03.2f}", 1.23456);
        console->info("Positional args are {1} {0}..", "too", "supported");
        console->info("{:>30}", "right aligned");

        // 日志级别示例
        spdlog::set_level(spdlog::level::info); // 设置全局日志级别
        console->debug("This message should not be displayed!");
        console->set_level(spdlog::level::trace); // 设置特定logger的日志级别
        console->debug("This message should be displayed..");
        
        // 创建循环文件日志记录器 (5MB大小，保留3个文件)
        auto rotating_logger = spdlog::rotating_logger_mt("some_logger_name", "../logs/rotating.txt", 1048576 * 5, 3);
        for (int i = 0; i < 10; ++i)
            rotating_logger->info("{} * {} equals {:>10}", i, i, i*i);

        // 创建每日文件日志记录器 - 每天创建一个新文件
        auto daily_logger = spdlog::daily_logger_mt("daily_logger", "../logs/daily.txt");
        daily_logger->info("Daily logger example..");
        
        // 反向追踪日志
        spdlog::enable_backtrace(32); // 存储最近32条日志
        for (int i = 0; i < 100; ++i)
            spdlog::debug("Backtrace message {}", i); // 不会输出
        
        spdlog::dump_backtrace(); // 输出反向追踪日志

        // 异步日志记录
        async_example();

        // 自定义格式
        custom_example();

        // 二进制日志
        std::string_view buffer = "Hello";
        console->info("Binary example: {:n}", spdlog::to_hex(buffer));

        console->info("Ending example..");
        spdlog::shutdown();
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
        return 1;
    }
}

// 性能与顺序的权衡：
// 异步日志的主要目标是提高性能，减少主线程阻塞
// 保证严格顺序会降低性能（需要额外的同步机制）
// spdlog文档说明：
// spdlog明确指出：在多线程异步模式下，不保证日志顺序
// 这是异步日志系统的通用设计选择
void async_example()
{
    // 默认使用线程池 (4个线程，队列大小为8192项)
    spdlog::init_thread_pool(8192, 4);
    auto async_file = spdlog::basic_logger_mt<spdlog::async_factory>("async_file_logger", "../logs/async_log.txt");
    for (int i = 1; i < 101; ++i)
    {
        async_file->info("Async message #{}", i);
    }
    
    // 等待所有日志刷新
    spdlog::shutdown();
}

void custom_example()
{
    // 创建自定义格式
    // 适配旧版spdlog的API
    auto console = spdlog::stdout_color_mt("custom_console");
    console->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] %v");
    console->info("Custom format example..");
}