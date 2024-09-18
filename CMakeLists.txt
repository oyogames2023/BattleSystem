cmake_minimum_required(VERSION 3.10)

# 项目名称和语言
project(BattleSystem VERSION 1.0 DESCRIPTION "Battle system library" LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 关闭第三方库的非必要工程
set(JSONCPP_WITH_TESTS OFF CACHE BOOL "Disable building jsoncpp tests")
set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF CACHE BOOL "Disable post-build unit tests")
set(JSONCPP_WITH_EXAMPLES OFF CACHE BOOL "Disable building jsoncpp examples")
set(TESTS OFF CACHE BOOL "Disable xlnt tests")
set(ZLIB_BUILD_EXAMPLES OFF CACHE BOOL "Disable zlib examples")
set(protobuf_BUILD_TESTS OFF CACHE BOOL "Disable protobuf's google test")

# 编译选项
option(BUILD_EXAMPLES "Build the examples." OFF)
option(BUILD_TOOLS "Build the tools." OFF)

# 添加 spdlog 子目录
add_subdirectory(ThirdParty/spdlog-1.14.1)
add_subdirectory(ThirdParty/jsoncpp-1.9.5)
add_subdirectory(ThirdParty/sol2-3.3.0)
add_subdirectory(ThirdParty/lua-5.4.7)
add_subdirectory(ThirdParty/libuv-1.48.0)
add_subdirectory(ThirdParty/xlnt-1.5.0)
add_subdirectory(ThirdParty/zlib-1.3.1)
add_subdirectory(ThirdParty/protobuf-28.0)

# 自动搜索所有 .h 和 .cpp 文件
file(GLOB_RECURSE HEADER_FILES "${CMAKE_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# 添加库
add_library(${PROJECT_NAME} SHARED ${SRC_FILES} ${HEADER_FILES})

# 包含目录
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/ThirdParty/spdlog/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/jsoncpp-1.9.5/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/sol2-3.3.0/include/sol
    ${CMAKE_SOURCE_DIR}/ThirdParty/lua-5.4.7/src
	${CMAKE_SOURCE_DIR}/ThirdParty/libuv-1.48.0/include
	${CMAKE_SOURCE_DIR}/ThirdParty/protobuf-28.0/src
	${CMAKE_SOURCE_DIR}/ThirdParty/xlnt-1.5.0/include
	${CMAKE_SOURCE_DIR}/ThirdParty/zlib-1.3.1
	${CMAKE_SOURCE_DIR}/ThirdParty/protobuf-28.0/src
    Include
    Include/Common
    Include/Common/Math
    Include/Common/JSON
	Include/Common/Logger
	Include/Common/DateTime
	Include/Common/Utilities
	Include/Common/GameConfig
	Include/Network
	Include/Filesystem
	Include/App
    Include/Object
    Include/Object/Actor
    Include/Object/Player
    Include/Object/Npc
    Include/Object/Monster
    Include/Scene
    Include/Battle
)

# 传递宏定义
option(USE_BATTLE_EXPORTS "Use BATTLE exports" ON)
option(BATTLE_EXPORTS "Enable BATTLE API export symbols" ON)

if(USE_BATTLE_EXPORTS)
    target_compile_definitions(${PROJECT_NAME} PUBLIC USE_BATTLE_EXPORTS)
endif()

if(BATTLE_EXPORTS)
    target_compile_definitions(${PROJECT_NAME} PUBLIC BATTLE_EXPORTS)
endif()

# 根据 BUILD_EXAMPLES 选项编译 Examples
if(BUILD_EXAMPLES)
    add_subdirectory(Examples)
endif()

# 根据 BUILD_TOOLS 选项编译 Tools
if(BUILD_TOOLS)
    add_subdirectory(Tools)
endif()

# 设置编译选项以忽略特定警告
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /wd4251)
	target_compile_options(${PROJECT_NAME} PRIVATE /wd4996)
endif()

# 链接 spdlog
target_link_libraries(${PROJECT_NAME}
	spdlog
	jsoncpp_lib
	lua
	uv_a
	xlnt
	zlib
	libprotobuf)

# 为 Visual Studio 组织源文件
source_group(TREE "${CMAKE_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_FILES})
source_group(TREE "${CMAKE_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${SRC_FILES})

# 平台特定设置
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE WIN_EXPORT)
    # Windows 平台特有的库（如果有）
elseif(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} pthread)  # 例如链接 pthread
endif()

# 安装规则
install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)

# 安装头文件
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Include/
        DESTINATION Include
        FILES_MATCHING PATTERN "*.h")
