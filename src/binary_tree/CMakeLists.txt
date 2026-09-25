add_library(binary_tree INTERFACE binary_tree.hpp
    binary_tree_node.hpp)

target_include_directories(binary_tree INTERFACE ${PROJECT_SOURCE_DIR}/src)

add_executable(bt_test bt_main_test.cpp)
#target_link_libraries(bt_test PRIVATE singly_linked_list)
