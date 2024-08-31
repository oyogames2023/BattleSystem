cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(lua VERSION 5.4.7)

# 可以通过这个选项来控制是构建静态库还是动态库，默认构建静态库
option(BUILD_SHARED_LIBS "Build as a shared library" OFF)

# Lua 源文件列表
set(LUA_SOURCES
    src/lapi.c
    src/lauxlib.c
    src/lbaselib.c
    src/lcode.c
    src/lcorolib.c
    src/lctype.c
    src/ldblib.c
    src/ldebug.c
    src/ldo.c
    src/ldump.c
    src/lfunc.c
    src/lgc.c
    src/linit.c
    src/liolib.c
    src/llex.c
    src/lmathlib.c
    src/lmem.c
    src/loadlib.c
    src/lobject.c
    src/lopcodes.c
    src/loslib.c
    src/lparser.c
    src/lstate.c
    src/lstring.c
    src/lstrlib.c
    src/ltable.c
    src/ltablib.c
    src/ltm.c
    src/lundump.c
    src/lutf8lib.c
    src/lvm.c
    src/lzio.c
)

# 添加头文件路径
include_directories(src)

# 根据选项 BUILD_SHARED_LIBS 来决定构建静态库还是动态库
if(BUILD_SHARED_LIBS)
    add_library(lua SHARED ${LUA_SOURCES})
else()
    add_library(lua STATIC ${LUA_SOURCES})
endif()

# 定义输出库的位置（可选）
set_target_properties(lua PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# 平台特定编译选项
if(WIN32)
    if(BUILD_SHARED_LIBS)
        target_compile_definitions(lua PRIVATE LUA_BUILD_AS_DLL)
    endif()
endif()
