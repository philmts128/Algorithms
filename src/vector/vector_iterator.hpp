#pragma once


namespace dsa
{
    /*----------------------------*/
    template <typename T>
    class vector_iterator final
    {
    private:
        /*----------------------------*/
        T* m_data_ptr { nullptr };

    public:
        /*----------------------------*/
        vector_iterator(T* data_ptr = nullptr) : m_data_ptr(data_ptr) {}

        /*----------------------------*/
        auto operator ++ () -> vector_iterator<T>& {
            ++m_data_ptr;
            return *this;
        }

        /*----------------------------*/
        auto operator -- () -> vector_iterator<T>& {
            --m_data_ptr;
            return *this;
        }

        /*----------------------------*/
        auto operator * () -> T {
            return *m_data_ptr;
        }

        /*----------------------------*/
        bool operator == (vector_iterator<T> other) {
            return (m_data_ptr == other.m_data_ptr);
        }

        /*----------------------------*/
        bool operator != (vector_iterator<T> other) {
            return !(*this == other);
        }
    };
}
