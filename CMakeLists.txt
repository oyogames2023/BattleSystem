cmake_minimum_required(VERSION 3.10)

# 项目名称和语言
project(BattleSystem VERSION 1.0 DESCRIPTION "Battle system library" LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加 spdlog 子目录
add_subdirectory(ThirdParty/spdlog-1.14.1)
add_subdirectory(ThirdParty/jsoncpp-1.9.5)

# 自动搜索所有 .h 和 .cpp 文件
file(GLOB_RECURSE HEADER_FILES "${CMAKE_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# 添加库
add_library(BattleSystem SHARED ${SRC_FILES} ${HEADER_FILES})

# 包含目录
target_include_directories(BattleSystem PUBLIC
    ${CMAKE_SOURCE_DIR}/ThirdParty/spdlog/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/jsoncpp-1.9.5/include
    Include
    Include/Common
    Include/Common/Math
    Include/Object
    Include/Object/Actor
    Include/Object/Player
    Include/Object/Npc
    Include/Object/Monster
    Include/Scene
    Include/Battle
)

# 链接 spdlog
target_link_libraries(BattleSystem spdlog jsoncpp_lib)

# 为 Visual Studio 组织源文件
source_group(TREE "${CMAKE_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_FILES})
source_group(TREE "${CMAKE_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${SRC_FILES})

# 平台特定设置
if(WIN32)
    target_compile_definitions(BattleSystem PRIVATE WIN_EXPORT)
    # Windows 平台特有的库（如果有）
elseif(UNIX AND NOT APPLE)
    target_link_libraries(BattleSystem pthread)  # 例如链接 pthread
endif()

# 安装规则
install(TARGETS BattleSystem
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)

# 安装头文件
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Include/
        DESTINATION Include
        FILES_MATCHING PATTERN "*.h")