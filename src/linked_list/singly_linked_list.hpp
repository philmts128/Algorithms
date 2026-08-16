#pragma once

#include <cstdlib>
#include <iostream>
#include <cassert>
#include <utility>

#include "singly_linked_list_iterator.hpp"
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
        singly_linked_list() {}

        /*----------------------------------*/
        ~singly_linked_list() {
            this->clear();
        }

        /*----------------------------------*/
        singly_linked_list(singly_linked_list&& other) {
            this->move_data(std::forward<singly_linked_list&&>(other));
        }

        /*----------------------------------*/
        singly_linked_list(const singly_linked_list& other) {
            this->copy_data(other);
        }

        /*----------------------------------*/
        template <typename... Args>
        singly_linked_list(Args... items) {
            ((void)this->push_back(items), ...);
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
        void insert_after(const T& data, size_t index)
        {
            assert(m_size > 0 && index < m_size);

            auto it = m_first;
            for (size_t k = 0; k < index; ++k)
                it = it->next;

            auto new_node = new singly_linked_list_node(data, it->next);
            it->next = new_node;

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
                m_last->next = nullptr;
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
        void remove(size_t index)
        {
            assert(m_size > 0 && index < m_size);

            auto it = m_first;
            for (size_t k = 0; k < index-1; ++k)
                it = it->next;

            if (it->next != nullptr)
            {
                auto temp = it->next->next;
                delete it->next;
                it->next = temp;
                m_size -= 1;
            }
        }

        /*----------------------------------*/
        void clear()
        {
            auto it = m_first;
            while (it != nullptr) {
                auto temp = it;
                it = it->next;
                delete temp;
            }

            m_first = m_last = nullptr;
            m_size = 0;
        }

        /*----------------------------------*/
        auto find(const T& data) const -> singly_linked_list_iterator<T>
        {
            assert(m_size > 0);

            //gambiarra aqui! refatorar depois
            auto cit = this->begin();
            auto it = *const_cast<dsa::singly_linked_list_iterator<T>*>(&cit);
            for (; it != this->end(); ++it) {
                if (*it == data)
                    return it;
            }

            return this->end();
        }

        /*----------------------------------*/
        auto exists(const T& data) const -> bool {
            return this->find(data) != this->end();
        }

        /*----------------------------------*/
        auto length() const -> size_t { return m_size; }
        auto empty()  const -> bool   { return m_size == 0; }

        /*----------------------------------*/
        auto begin() const -> singly_linked_list_iterator<T> { return { m_first      }; }
        auto end()   const -> singly_linked_list_iterator<T> { return { m_last->next }; }

        /*----------------------------------*/
        void print()
        {
            auto it = m_first;
            while (it != nullptr) {
                std::cout << it->data << " ";
                it = it->next;
            }
        }

        /*----------------------------------*/
        auto operator = (const singly_linked_list& other) -> singly_linked_list
        {
            this->copy_data(other);
            return *this;
        }

        /*----------------------------------*/
        auto operator = (singly_linked_list&& other) -> singly_linked_list
        {
            this->move_data(std::forward<singly_linked_list&&>(other));
            return *this;
        }

    private:

        /*----------------------------------*/
        void copy_data(const singly_linked_list& other)
        {
            this->clear();
            auto it = other.m_first;
            while (it != nullptr) {
                this->push_back(it->data);
                it = it->next;
            }
        }

        /*----------------------------------*/
        void move_data(singly_linked_list&& other)
        {
            this->clear();

            m_size  = other.m_size;
            m_first = other.m_first;
            m_last  = other.m_last;

            other.m_size = 0;
            other.m_first = other.m_last = nullptr;
        }
    };
}
