#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <iostream>

int main()
{
    // 类似于 printf 的 % 占位符输出，fmt 使用大括号替代参数，且和参数类型无关：
    fmt::print("hello {}\n", "world");
    fmt::print("{0} {1} {0}\n", 1, 2);
    fmt::print("{:.2f}\n", 3.1415926);
    // 使用 < 表示右填充，即文本居左：
    fmt::print("{0:*<10}\n", "hello");
    // 使用 ^ 表示在两层填充，即文本居中：
    fmt::print("{0:*^10}\n", "hello");

    // 精度值也可以通过参数动态设置：
    fmt::print("{0:.{1}f}\n", 3.141596, 2);
    // 使用 + 表示正负数字都显示符号：
    fmt::print("正数:{0:+}\n负数:{1:+}\n", 30, -20);

    fmt::print("--------------数字进制格式化--------------\n");
    fmt::print("10进制:{0:d}\n", 42);
    fmt::print("2进制:{0:b}\n", 42);
    fmt::print("8进制:{0:o}\n", 42);
    fmt::print("16进制:{0:x}\n", 42);

    fmt::print("--------------fmt 库使用--------------\n");
    // 格式化内容到字符串
    auto res = fmt::format("hello {}", "world");
    std::cout << res << std::endl;
    // 格式化内容到迭代器
    std::string s;
    fmt::format_to(std::back_inserter(s), "hello {}", "world");
    std::cout << s << std::endl;

    fmt::print("--------------fmt 库使用进阶--------------\n");
    // 命名参数
    // 使用 fmt::arg 可以构建一个命名参数：
    fmt::print("{a:*<10}{b:#x}\n", fmt::arg("a", "hello"), fmt::arg("b", 100));
    // 参数列表
    // fmt::vformat 支持使用参数列表进行格式化：
    const fmt::format_args args = fmt::make_format_args(
        fmt::arg("a", "hello"),
        fmt::arg("b", 100));
    const auto s_args = fmt::vformat("{a:*<10}{b:#x}", args);
    std::cout << s_args << std::endl;

    return 0;
}