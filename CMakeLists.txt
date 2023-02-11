cmake_minimum_required(VERSION 3.21)
project(DataStructure_Algorithm)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/array)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/list)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/stack)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/queue)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/heap)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/hash)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tree)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/graph)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sort)

file(
        GLOB SOURCES
        "*.h"
        "*.cpp"
)

add_executable(DataStructure_Algorithm ${SOURCES})

target_link_libraries(
        DataStructure_Algorithm PUBLIC
        array
        list
        stack
        queue
        heap
        hash
        tree
        graph
        sort
)
