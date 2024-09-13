# 设定CMake的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(LoggerTest)

# 设置使用的C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置包含目录，这应该是相对于当前项目目录的
include_directories(
    ${PROJECT_SOURCE_DIR}/../Include
    ${PROJECT_SOURCE_DIR}/../Include/Common
	${PROJECT_SOURCE_DIR}/../Include/Common/Logger
)

# 可以添加用于查找依赖包的find_package()调用
# find_package(Boost REQUIRED)

# 指定生成目标
file(GLOB_RECURSE SOURCES "Src/*.cpp")
add_executable(${PROJECT_NAME} main.cpp)

# 确保 BattleSystem 动态库的位置在链接器的搜索路径中
link_directories(${PROJECT_SOURCE_DIR}/../build)

# 链接库文件，如果有第三方库或多个目标文件
target_link_libraries(${PROJECT_NAME} PRIVATE BattleSystem)
