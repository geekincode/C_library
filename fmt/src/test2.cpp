#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <iostream>

struct my_struct
{
    int id;
    std::string name;
};


// fmt::formatter格式化器特化的作用是fmt::print("{}",ms)将内容格式化到{}中
template <>
struct fmt::formatter<my_struct>
{
    char presentation = 'f';
    auto parse(fmt::format_parse_context &ctx) -> decltype(ctx.begin())
    {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && (*it == 'f' || *it == 'i'))
            presentation = *it++;
        if (it != end && *it != '}')
            throw "invalid format";
        return it;
    }
    template <typename FormatContext>
    auto format(const my_struct &ms, FormatContext &ctx) const -> decltype(ctx.out())
    {
        return presentation == 'f'
                   ? fmt::format_to(ctx.out(), "[my_struct]id={},name= {}", ms.id, ms.name)
                   : fmt::format_to(ctx.out(), "[my_struct]id={}", ms.id);
    }
};

int main()
{

    my_struct ms{0, "hello"};
    // {0:f}：触发完整格式化，显示id和name
    // {0:i}：触发精简格式化，仅显示id
    fmt::print("my_struct f 格式化:{0:f}\nmy_struct i 格式化:{0:i}\n", ms);
    return 0;
}