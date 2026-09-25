add_library(heap INTERFACE heap.hpp
    heap_node.hpp)

target_include_directories(heap INTERFACE ${PROJECT_SOURCE_DIR}/src)

add_executable(heap_test heap_main_test.cpp)
#target_link_libraries(bt_test PRIVATE singly_linked_list)
