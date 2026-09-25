#pragma once

#include "vector/vector.hpp"
#include "heap_node.hpp"

#include <cstdint>
#include <cassert>
#include <utility>
#include <iostream>


namespace dsa
{
    /*----------------------------------*/
    template <typename T>
    class heap final
    {
    private:
        size_t m_size     { 0 };
        size_t m_max_size { 0 };
        dsa::vector<dsa::heap_node<T>> m_data;

    public:
        /*----------------------------------*/
        explicit heap(size_t max_size) : m_max_size(max_size) {}

        /*----------------------------------*/
        bool insert(const T& item)
        {
            if (m_size == m_max_size)
                return false;

            auto node = new heap_node<T>(item);
            m_data[m_size] = node;
            this->trickleUp(m_size++);
            return true;
        }

        /*----------------------------------*/
        auto remove_max() -> heap_node<T>*
        {
            auto root = m_data[0];
            m_data[0] = m_data[--m_size];
            this->trickleDown(0);
            return root;
        }

    private:
        /*----------------------------------*/
        void trickleUp(size_t index)
        {
            size_t parent = (index-1) / 2;
            heap_node<T> bottom = m_data[index];

            while (index > 0 && m_data[parent].data < bottom.data)
            {
                m_data[index] = m_data[parent];
                index = parent;
                parent = (parent-1)/2;
            }

            m_data[index] = bottom;
        }

        /*----------------------------------*/
        void trickleDown(size_t index)
        {
            size_t larger_child;

            heap_node top = m_data[index];
            while (index < m_size/2)
            {
                size_t left_child = 2 * index + 1;
                size_t right_child = left_child + 1;

                if (right_child < m_size && m_data[left_child].data < m_data[right_child])
                    larger_child = right_child;
                else
                    larger_child = left_child;

                if (top.data >= m_data[larger_child].data)
                    break;

                m_data[index] = m_data[larger_child];
                index = larger_child;
            }

            m_data[index] = top;
        }
    };
}
