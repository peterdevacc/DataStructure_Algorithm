cmake_minimum_required(VERSION 3.21)
project(heap)

set(CMAKE_CXX_STANDARD 20)

file(
        GLOB SOURCES
        "*.h"
        "*.cpp"
)

add_library(
        heap
        ${SOURCES}
)

target_include_directories(heap INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
