cmake_minimum_required(VERSION 3.10)  # 设置 CMake 最小版本要求

project(JSONParserTest)  # 定义项目名称

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置包含目录，这应该是相对于当前项目目录的
include_directories(
    ${PROJECT_SOURCE_DIR}/../Include
    ${PROJECT_SOURCE_DIR}/../Include/Common
    ${PROJECT_SOURCE_DIR}/../Include/Common/JSON
    ${PROJECT_SOURCE_DIR}/../ThirdParty/jsoncpp-1.9.5/include
)

# 添加要编译的源文件
add_executable(JSONParserTest main.cpp)

# 确保 BattleSystem 动态库的位置在链接器的搜索路径中
link_directories(${PROJECT_SOURCE_DIR}/../build)  # 假设动态库位于 build 目录下

# 链接 jsoncpp 库和 BattleSystem 动态库
# 假设 jsoncpp_lib 已经在 BattleSystem 中链接，这里可能不需要再次链接
target_link_libraries(JSONParserTest PRIVATE BattleSystem)