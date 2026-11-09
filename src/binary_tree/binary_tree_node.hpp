#pragma once

#include "common/definitions.hpp"


DSA_NAMESPACE_BEGIN

/*-----------------------------*/
template <typename T>
struct binary_tree_node final
{
    /*-----------------------------*/
    binary_tree_node<T>* left  { nullptr };
    binary_tree_node<T>* right { nullptr };
    T data;

    /*-----------------------------*/
    binary_tree_node() = default;

    /*------------------------------*/
    binary_tree_node(const T& data) : data(data) {}
 };

DSA_NAMESPACE_END
