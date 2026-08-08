#pragma once

#include <cstdlib>
#include <iostream>
#include <cassert>
#include "singly_linked_list_node.hpp"


namespace dsa
{
    /*----------------------------------*/
    template <typename T>
    class singly_linked_list final
    {
    private:
        /*----------------------------------*/
        singly_linked_list_node<T>* m_first { nullptr };
        singly_linked_list_node<T>* m_last  { nullptr };
        size_t m_size { 0 };

    public:
        /*----------------------------------*/
        singly_linked_list()
        {
        }

        /*----------------------------------*/
        ~singly_linked_list()
        {
            auto it = m_first;
            while (it != nullptr) {
                auto temp = it;
                it = it->next;
                delete temp;
            }

            m_first = m_last = nullptr;
        }

        /*----------------------------------*/
        void push_back(const T& item)
        {
            if (m_first == nullptr) {
                m_first = new singly_linked_list_node(item);
                m_last = m_first;
                return;
            }

            m_last->next = new singly_linked_list_node(item);
            m_last = m_last->next;
            m_size += 1;
        }

        /*----------------------------------*/
        void push_front(const T& item)
        {
            if (m_first == nullptr) {
                m_first = new singly_linked_list_node(item);
                m_last = m_first;
                return;
            }

            auto new_node = new singly_linked_list_node(item, m_first);
            m_first = new_node;
            m_size += 1;
        }

        /*----------------------------------*/
        void pop_back()
        {
            assert(m_size > 0);

            if (m_size == 1) {
                delete m_first;
                m_first = m_last = nullptr;
            } else {
                auto it = m_first;
                while (it->next->next != nullptr)
                    it = it->next;
                delete it->next;
                m_last = it;
            }

            m_size -= 1;
        }

        /*----------------------------------*/
        void pop_front()
        {
            assert(m_size > 0);
            auto temp = m_first;
            m_first = m_first->next;
            delete temp;
            m_size -= 1;
        }

        /*----------------------------------*/
        auto length() const -> size_t { return m_size; }
        auto empty()  const -> bool   { return m_size == 0; }

        /*----------------------------------*/
        void print()
        {
            auto it = m_first;
            while (it != nullptr) {
                std::cout << it->data << " ";
                it = it->next;
            }
        }
    };
}
