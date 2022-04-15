cmake_minimum_required(VERSION 3.21)
project(graph)

set(CMAKE_CXX_STANDARD 20)

file(
        GLOB SOURCES
        "*.h"
        "*.cpp"
)

add_library(
        graph
        ${SOURCES}
)

target_include_directories(graph INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
