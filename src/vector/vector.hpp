#pragma once

#include <cstdlib>
#include <cassert>
#include <utility>
#include "vector_iterator.hpp"


namespace dsa
{
    /*---------------------------------------*/
    template <typename T>
    class vector final
    {
    private:
        /*---------------------------------------*/
        T* m_data { nullptr };
        size_t m_size { 0 };
        size_t m_capacity { Block_Size };
        static constexpr int Block_Size { 64 };

    public:
        /*---------------------------------------*/
        vector(size_t blocks = 1) {
            m_data = new T[Block_Size];
        }

        /*---------------------------------------*/
        vector(const vector<T>& other) {
            this->copy_data(other);
        }

        /*---------------------------------------*/
        vector(dsa::vector<T>&& other)
        {
            this->move_data(
                std::forward<dsa::vector<T>&&>(other));
        }

        /*---------------------------------------*/
        template <typename... Args>
        vector(Args... items)
        {
            m_size = sizeof...(items);
            m_capacity = this->next_multiple(m_size);
            if (m_data)
                delete[] m_data;
            m_data = new T[m_capacity] { static_cast<T>(items)... };
        }

        /*---------------------------------------*/
        ~vector()
        {
            if (m_data) {
                delete[] m_data;
                m_data = nullptr;
            }
        }

        /*---------------------------------------*/
        void push_back(const T& item)
        {
            if (m_size == m_capacity) {
                size_t new_cap = this->next_multiple(m_size);
                this->grow(new_cap); }

            m_data[m_size++] = item;
        }

        /*---------------------------------------*/
        void push_front(const T& item) {
            this->insert(item, 0);
        }

        /*---------------------------------------*/
        void insert(const T& item, size_t place)
        {
            assert(place >= 0 && place < m_size);

            if (m_size == m_capacity) {
                size_t new_cap = this->next_multiple(m_size);
                this->grow(new_cap); }

            this->shift_right(place);
            m_data[place] = item;
            m_size += 1;
        }

        /*---------------------------------------*/
        auto pop_back() -> T
        {
            assert(m_size > 0);
            if (m_size <= m_capacity/2)
                this->shrink(this->next_multiple(m_size));
            return m_data[(m_size--) - 1];
        }

        /*---------------------------------------*/
        auto pop_front() -> T {
            assert(m_size > 0);
            return remove(0);
        }

        /*---------------------------------------*/
        auto remove(size_t index) -> T
        {
            assert(index >= 0 && index < m_size);
            if (m_size <= m_capacity/2)
                this->shrink(this->next_multiple(m_size));
            auto item = m_data[index];
            this->shift_left(index);
            m_size -= 1;
            return item;
        }

        /*---------------------------------------*/
        auto find(const T& item) const -> size_t
        {
            for (size_t i = 0; i < m_size; ++i) {
                if (item == m_data[i]) {
                    return i;
                }
            }
            return -1; //valor máximo de size_t
        }

        /*---------------------------------------*/
        auto exists(const T& item) const -> bool {
            return (this->find(item) != -1);
        }

        /*---------------------------------------*/
        auto length() const -> size_t { return m_size; }
        auto empty() const -> bool    { return m_size == 0; }
        auto capacity() const -> size_t { return m_capacity; }

        /*---------------------------------------*/
        auto at(size_t idx) const -> T{
            assert(idx >= 0 && idx < m_size);
            return m_data[idx];
        }

        /*---------------------------------------*/
        auto first() -> T {
            assert(m_size > 0);
            return m_data[0];
        }

        /*---------------------------------------*/
        auto last() -> T {
            assert(m_size > 0);
            return m_data[m_size-1];
        }

        /*---------------------------------------*/
        auto begin() const -> dsa::vector_iterator<T> {
            return { &m_data[0] };
        }

        /*---------------------------------------*/
        auto end() const -> dsa::vector_iterator<T> {
            return { &m_data[m_size] };
        }

        /*---------------------------------------*/
        auto operator[](size_t idx) -> T& {
            assert(idx >= 0 && idx < m_size);
            return m_data[idx];
        }

        /*---------------------------------------*/
        auto operator=(const dsa::vector<T>& other) -> dsa::vector<T>
        {
            this->copy_data(other);
            return *this;
        }

        /*---------------------------------------*/
        auto operator=(dsa::vector<T>&& other) -> dsa::vector<T>
        {
            this->move_data(
                std::forward<dsa::vector<T>&&>(other));
            return *this;
        }

    private:
        /*---------------------------------------*/
        void grow(const size_t size)
        {
            auto data = new T[size];
            for (size_t i = 0; i < m_size; ++i)
                data[i] = m_data[i];
            delete[] m_data;
            m_data = data;
            m_capacity = size;
        }

        /*---------------------------------------*/
        void resize(const size_t size)
        {
            auto data = new T[size];
            auto lim = (size < m_size) ? size : m_size;
            for (size_t i = 0; i < lim; ++i)
                data[i] = m_data[i];
            delete[] m_data;
            m_data = data;
            m_capacity = size;
        }

        /*---------------------------------------*/
        void shrink(const size_t size)
        {
            auto data = new T[size];
            for (size_t i = 0; i < size; ++i)
                data[i] = m_data[i];
            delete[] m_data;
            m_data = data;
            m_capacity = size;
        }

        /*---------------------------------------*/
        inline void shift_right(size_t start = 0)
        {
            for (size_t i = m_size; i >= start+1; --i)
                m_data[i] = m_data[i-1];
        }

        /*---------------------------------------*/
        inline void shift_left(size_t start = 0)
        {
            for (size_t i = start+1; i < m_size; ++i)
                m_data[i-1] = m_data[i];
        }

        /*---------------------------------------*/
        inline auto next_multiple(size_t num) -> size_t {
            return num - (num % Block_Size) + Block_Size;
        }

        /*---------------------------------------*/
        void copy_data(const dsa::vector<T>& other)
        {
            if (m_data)
                delete[] m_data;
            m_capacity = other.m_capacity;
            m_data = new T[m_capacity];
            m_size = other.m_size;
            for (size_t i = 0; i < m_size; ++i)
                m_data[i] = other.m_data[i];
        }

        /*---------------------------------------*/
        void move_data(dsa::vector<T>&& other)
        {
            if (m_data) delete[] m_data;

            m_data = other.m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            other.m_data = new T[Block_Size];
            other.m_size = 0;
            other.m_capacity = Block_Size;
        }
    };
}
