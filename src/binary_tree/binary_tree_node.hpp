#pragma once

#include <iostream>


namespace dsa
{
    /*----------------------------------*/
    template <typename T>
    struct binary_tree_node
    {
        /*----------------------------------*/
        binary_tree_node<T>* left  { nullptr };
        binary_tree_node<T>* right { nullptr };
        T data;

        /*----------------------------------*/
        binary_tree_node(const T& data)
            : data(data) {}

        /*----------------------------------*/
        ~binary_tree_node() {
           //std::cout << data << " deleted!\n";
        }

        /*----------------------------------*/
        bool is_leaf() {
            return (!left && !right);
        }
    };
}
