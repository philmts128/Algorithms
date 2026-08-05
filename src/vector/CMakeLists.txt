add_library(vector INTERFACE vector.hpp)
add_library(vector_iterator INTERFACE vector_iterator.hpp)

target_include_directories(vector INTERFACE ${PROJECT_SOURCE_DIR}/src)

add_executable(test test.cpp)

target_link_libraries(test PRIVATE vector)
