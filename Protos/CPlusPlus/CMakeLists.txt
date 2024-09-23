cmake_minimum_required(VERSION 3.10)

project(ProtosLib LANGUAGES CXX)

# Set the output directory for the library
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# Search for header and source files only in the CPlusPlus directory and its subdirectories
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/Protos/CPlusPlus/*.h)
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/Protos/CPlusPlus/*.cc)

# Create the dynamic library
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})

# Link the protobuf library and set include directories
link_directories(${PROJECT_SOURCE_DIR}/../build)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/Protos/CPlusPlus
    ${CMAKE_SOURCE_DIR}/ThirdParty/protobuf-28.0/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE libprotobuf)
