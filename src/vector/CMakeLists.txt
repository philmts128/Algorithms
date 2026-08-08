add_library(vector INTERFACE vector.hpp)
add_library(vector_iterator INTERFACE vector_iterator.hpp)

target_include_directories(vector INTERFACE ${PROJECT_SOURCE_DIR}/src)

add_executable(main_test main_test.cpp)
target_link_libraries(main_test PRIVATE vector)

add_executable(bench1 benchmarks/bench1.cpp)
target_link_libraries(bench1 PRIVATE vector benchmark)

