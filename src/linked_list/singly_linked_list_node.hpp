#pragma once

#include <iostream>


namespace dsa
{
    /*----------------------------------*/
    template <typename T>
    struct singly_linked_list_node
    {
        /*----------------------------------*/
        singly_linked_list_node<T>* next { nullptr };
        T data;

        /*----------------------------------*/
        singly_linked_list_node(const T& data, singly_linked_list_node<T>* next = nullptr)
            : data(data), next{next} {}

        /*----------------------------------*/
        ~singly_linked_list_node() {
            //std::cout << data << " has been destroyed!\n";
        }
    };
}
