#pragma once

#include <cstdlib>
#include <cassert>


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
        static constexpr int Block_Size { 8 };

    public:
        /*---------------------------------------*/
        vector()
        {
            m_data = new T[m_capacity];
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
                size_t new_cap = this->next_multiple(m_size, Block_Size);
                this->grow(new_cap);
            }

            m_data[m_size++] = item;
        }

        /*---------------------------------------*/
        auto operator[](size_t idx) -> T&
        {
            return m_data[idx];
        }

    private:
        /*---------------------------------------*/
        void grow(const size_t size)
        {
            assert(size > m_size);
            auto data = new T[size];
            for (size_t i = 0; i < m_size; ++i)
                data[i] = m_data[i];
            delete[] m_data;
            m_data = data;
            m_capacity = size;
        }

        /*---------------------------------------*/
        auto next_multiple(size_t num, size_t mul) -> size_t {
            return num - (num % mul) + mul;
        }
    };
}
