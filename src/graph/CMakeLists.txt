add_library(graph INTERFACE graph.hpp graph_node.hpp)

target_include_directories(graph INTERFACE ${PROJECT_SOURCE_DIR}/src)

add_executable(graph_test graph_test.cpp)
target_link_libraries(graph_test PRIVATE graph)
