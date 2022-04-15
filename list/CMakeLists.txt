cmake_minimum_required(VERSION 3.21)
project(list)

set(CMAKE_CXX_STANDARD 20)

file(
        GLOB SOURCES
        "*.h"
        "*.cpp"
)

add_library(
        list
        ${SOURCES}
)

target_include_directories(list INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
