cmake_minimum_required(VERSION 3.21)
project(tree)

set(CMAKE_CXX_STANDARD 20)

file(
        GLOB SOURCES
        "*.h"
        "*.cpp"
)

add_library(
        tree
        ${SOURCES}
)

target_include_directories(tree INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
