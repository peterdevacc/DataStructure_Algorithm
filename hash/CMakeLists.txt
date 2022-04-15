cmake_minimum_required(VERSION 3.21)
project(hash)

set(CMAKE_CXX_STANDARD 20)

file(
        GLOB SOURCES
        "*.h"
        "*.cpp"
)

add_library(
        hash
        ${SOURCES}
)

target_include_directories(hash INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
