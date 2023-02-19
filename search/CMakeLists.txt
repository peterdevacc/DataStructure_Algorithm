cmake_minimum_required(VERSION 3.21)
project(search)

set(CMAKE_CXX_STANDARD 20)

file(
        GLOB SOURCES
        "*.h"
        "*.cpp"
)

add_library(
        search
        ${SOURCES}
)

target_include_directories(search INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
