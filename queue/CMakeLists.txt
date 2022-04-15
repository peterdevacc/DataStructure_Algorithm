cmake_minimum_required(VERSION 3.21)
project(queue)

set(CMAKE_CXX_STANDARD 20)

file(
        GLOB SOURCES
        "*.h"
        "*.cpp"
)

add_library(
        queue
        ${SOURCES}
)

target_include_directories(queue INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
