#pragma once

#include "singly_linked_list_node.hpp"


namespace dsa
{
    /*----------------------------*/
    template <typename T>
    class singly_linked_list_iterator final
    {
    private:
        /*----------------------------*/
        using singly_node = singly_linked_list_node<T>;
        singly_node* m_first { nullptr };

    public:
        /*----------------------------*/
        singly_linked_list_iterator(singly_node* first_node ) : m_first(first_node) {}

        /*----------------------------*/
        auto operator ++ () -> singly_linked_list_iterator<T>& {
            m_first = m_first->next;
            return *this;
        }

        /*----------------------------*/
        auto operator * () -> T {
            return m_first->data;
        }

        /*----------------------------*/
        bool operator == (singly_linked_list_iterator<T> other) {
            return (m_first == other.m_first);
        }

        /*----------------------------*/
        bool operator != (singly_linked_list_iterator<T> other) {
            return !(*this == other);
        }
    };
}
