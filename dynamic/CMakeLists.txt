cmake_minimum_required(VERSION 3.21)
project(dynamic)

set(CMAKE_CXX_STANDARD 20)

file(
        GLOB SOURCES
        "*.h"
        "*.cpp"
)

add_library(
        dynamic
        ${SOURCES}
)

target_include_directories(dynamic INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
