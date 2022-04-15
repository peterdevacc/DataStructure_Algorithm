cmake_minimum_required(VERSION 3.21)
project(sort)

set(CMAKE_CXX_STANDARD 20)

file(
        GLOB SOURCES
        "*.h"
        "*.cpp"
)

add_library(
        sort
        ${SOURCES}
)

target_include_directories(sort INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
