#pragma once


namespace dsa
{
    /*----------------------------------*/
    template <typename T>
    struct heap_node
    {
        /*----------------------------------*/
        T value;

        /*----------------------------------*/
        heap_node(const T& val) : value(val) {}
    };
}
