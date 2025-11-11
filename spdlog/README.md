# Spdlog CMake Project Example

这是一个使用spdlog日志库的CMake项目示例。

## 项目结构

```
spdlog/
├── CMakeLists.txt          # CMake配置文件
├── src/                    # 源代码目录
│   ├── main.cpp            # 基本示例程序
│   └── example.cpp         # 高级功能示例程序
├── logs/                   # 日志文件目录（运行时创建）
└── README.md               # 本说明文件
```

## 构建项目

有两种方式可以构建项目，取决于spdlog的获取方式：

### 方式一：使用系统安装的spdlog（推荐）

如果系统中已安装spdlog，则可以直接使用：

1. 创建构建目录：
   ```bash
   mkdir build && cd build
   ```

2. 使用CMake生成构建文件：
   ```bash
   cmake ..
   ```

3. 编译项目：
   ```bash
   cmake --build .
   ```

### 方式二：自动下载spdlog

如果系统中没有安装spdlog，或者希望使用特定版本，可以使用FetchContent方式自动下载：

1. 将CMakeLists.txt中内容替换为：
   ```cmake
   cmake_minimum_required(VERSION 3.14)
   project(SpdlogExample)

   # 设置C++标准
   set(CMAKE_CXX_STANDARD 17)
   set(CMAKE_CXX_STANDARD_REQUIRED ON)

   # 包含FetchContent模块用于获取外部依赖
   include(FetchContent)

   # 获取spdlog库
   FetchContent_Declare(
       spdlog
       GIT_REPOSITORY https://github.com/gabime/spdlog.git
       GIT_TAG v1.12.0
   )

   # 使spdlog可用
   FetchContent_MakeAvailable(spdlog)

   # 添加可执行文件
   add_executable(${PROJECT_NAME} src/main.cpp)
   add_executable(spdlog_example src/example.cpp)

   # 链接spdlog库
   target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog_header_only)
   target_link_libraries(spdlog_example PRIVATE spdlog::spdlog_header_only)
   ```

2. 执行相同构建步骤：
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

## 运行程序

构建完成后，可以运行生成的可执行文件：

```bash
# 运行基本示例
./SpdlogExample

# 运行高级示例
./spdlog_example
```

## 功能说明

### main.cpp - 基本功能
- 控制台日志输出
- 文件日志记录
- 循环日志文件
- 日志级别控制
- 异常处理

### example.cpp - 高级功能
- 彩色控制台输出
- 自定义日志格式
- 每日日志文件
- 异步日志记录
- 反向追踪日志
- 二进制数据日志

## 日志输出

程序运行时会创建`logs`目录，并在其中生成以下日志文件：
- `basic-log.txt` - 基本日志文件
- `rotating-log.txt` - 循环日志文件
- `daily.txt` - 每日日志文件
- `async_log.txt` - 异步日志文件

## 依赖关系

项目可以使用以下任一方式管理依赖：
- 系统安装的spdlog（通过`find_package`）
- 使用CMake的`FetchContent`模块自动下载和管理spdlog

## 最低要求

- CMake 3.14 或更高版本
- 支持C++17的编译器
- Git (仅当使用FetchContent方式时需要)

## 自定义配置

可以通过修改[CMakeLists.txt](CMakeLists.txt)文件来：
- 切换spdlog获取方式（系统安装 vs 自动下载）
- 更改spdlog版本（仅FetchContent方式）
- 添加更多源文件
- 配置不同的构建选项

## 格式字符串结构
格式字符串由多个特殊占位符组成，每个占位符代表不同的日志信息：

1. 时间戳部分 [ %Y-%m-%d %H:%M:%S.%e ]
* %Y - 四位年份 (例如: 2023)
* %m - 月份 (01-12)
* %d - 日期 (01-31)
* %H - 小时 (24小时制, 00-23)
* %M - 分钟 (00-59)
* %S - 秒 (00-59)
* .%e - 毫秒 (000-999)
2. Logger名称部分 [ %n ]
* %n - 当前logger的名称（在代码中通过spdlog::stdout_color_mt("console")定义的"console"）
3. 日志级别部分 [ %^%l%$ ]
* %^ - 开始颜色输出（启用ANSI颜色）
* %l - 完整日志级别名称 (trace, debug, info, warn, error, critical)
* %$ - 结束颜色输出（恢复默认颜色）
4. 日志消息部分 %v
* %v - 实际日志内容（即调用info(), debug()等方法时传入的消息）

## 常用格式说明符参考
时间相关
* %Y %m %d %H %M %S - 基础时间单位
* %.3e - 精确到毫秒 (000-999)
* %.6f - 精确到微秒
* %P - 上午/下午标识 (AM/PM)
日志信息
* %L - 日志级别首字母 (T/D/I/W/E/C)
* %t - 线程ID
* %g - 源文件:行号
* %# - 源文件:行号 in 函数名
* %! - 函数名
颜色控制
* %^ - 开始颜色
* %$ - 结束颜色
* %K - 背景颜色（K=black, red, green, yellow, blue, magenta, cyan, white）

