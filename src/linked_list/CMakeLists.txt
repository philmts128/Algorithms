add_library(singly_linked_list INTERFACE singly_linked_list.hpp
    singly_linked_list_node.hpp singly_linked_list_iterator.hpp)

target_include_directories(singly_linked_list INTERFACE ${PROJECT_SOURCE_DIR}/src)

add_executable(sll_test main_test.cpp)
target_link_libraries(sll_test PRIVATE singly_linked_list)
