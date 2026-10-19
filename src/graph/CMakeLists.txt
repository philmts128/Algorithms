add_library(graph INTERFACE graph/graph.hpp)

target_include_directories(graph INTERFACE ${PROJECT_SOURCE_DIR}/src)

add_executable(graph_test graph/graph_test.cpp)
target_link_libraries(graph_test PRIVATE graph)


add_library(weighted_graph INTERFACE weighted_graph/weighted_graph.hpp)

target_include_directories(weighted_graph INTERFACE ${PROJECT_SOURCE_DIR}/src)

add_executable(weighted_graph_test weighted_graph/weighted_graph_test.cpp)
target_link_libraries(weighted_graph_test PRIVATE weighted_graph)
