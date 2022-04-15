cmake_minimum_required(VERSION 3.21)
project(array)

set(CMAKE_CXX_STANDARD 20)

file(
        GLOB SOURCES
        "*.h"
        "*.cpp"
)

add_library(
        array
        ${SOURCES}
)

target_include_directories(array INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
