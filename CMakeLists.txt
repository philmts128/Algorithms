cmake_minimum_required(VERSION 3.5)

project(Algorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(utils/benchmark)
add_subdirectory(utils/memory)
add_subdirectory(src/recursion)
add_subdirectory(src/vector)
add_subdirectory(src/linked_list)
add_subdirectory(src/binary_tree)
