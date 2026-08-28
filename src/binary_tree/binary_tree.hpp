#pragma once

#include "binary_tree_node.hpp"

#include <cstdint>
#include <utility>
#include <iostream>


namespace dsa
{
    /*----------------------------------*/
    template <typename T>
    class binary_tree final
    {
    private:
        binary_tree_node<T>* m_root { nullptr };
        size_t m_size { 0 };

    public:
        /*----------------------------------*/
        explicit binary_tree() {}

        /*----------------------------------*/
        explicit binary_tree(const binary_tree<T>& other) {
            this->copy_data(other);
        }

        /*----------------------------------*/
        explicit binary_tree(binary_tree<T>&& other) {
            this->move_data(std::forward<binary_tree<T>>(other));
        }

        /*----------------------------------*/
        ~binary_tree() {
            this->clear();
        }

        /*----------------------------------*/
        void insert(const T& item)
        {
            this->create_node(item);

            auto it = m_root;
            while (true)
            {
                if (it->data == item)
                    return;

                if (item > it->data)
                {
                    auto new_node = new binary_tree_node<T>(item);
                    if (it->right == nullptr) it->right = new_node;
                    else it = it->right;
                }
                else if (item < it->data)
                {
                    auto new_node = new binary_tree_node<T>(item);
                    if (it->left == nullptr) it->left = new_node;
                    else it = it->left;
                }
            }
        }

        /*----------------------------------*/
        void clear()
        {
            if (m_root)
            {
                post_order(m_root, [&](binary_tree_node<T>* n) {
                    delete n;
                });

                m_root = nullptr;
                m_size = 0;
            }
        }

        /*----------------------------------*/
        void print()
        {
            in_order(m_root, [](binary_tree_node<T>* n) {
                std::cout << n->data << ' ';
            });
        }

        /*----------------------------------*/
        auto operator = (const binary_tree<T>& other) -> const binary_tree<T>&
        {
            this->copy_data(other);
            return *this;
        }

        /*----------------------------------*/
        auto operator = (binary_tree<T>&& other) -> binary_tree<T>&
        {
            this->move_data(std::forward<binary_tree<T>>(other));
            return *this;
        }

    private:
        /*----------------------------------*/
        template <typename F>
        void in_order(binary_tree_node<T>* node, F lambda)
        {
            if (node) {
                in_order(node->left, lambda);
                lambda(node);
                in_order(node->right, lambda);
            }
        }

        /*----------------------------------*/
        template <typename F>
        void pre_order(binary_tree_node<T>* node, F lambda)
        {
            if (node) {
                lambda(node);
                pre_order(node->left, lambda);
                pre_order(node->right, lambda);
            }
        }

        /*----------------------------------*/
        template <typename F>
        void post_order(binary_tree_node<T>* node, F lambda)
        {
            if (node) {
                post_order(node->left, lambda);
                post_order(node->right, lambda);
                lambda(node);
            }
        }

        /*----------------------------------*/
        void create_node(const T& item)
        {
            if (m_root == nullptr) {
                m_size = 1;
                m_root = new binary_tree_node<T>(item);
            }
        }

        /*----------------------------------*/
        void copy_data(const dsa::binary_tree<T>& other)
        {
            this->clear();
            other.in_order(other.m_root, [&](binary_tree_node<T>* n) {
                this->insert(n->data);
            });
        }

        /*----------------------------------*/
        void move_data(dsa::binary_tree<T>&& other)
        {
            this->clear();
            m_root = other.m_root;
            m_size = other.m_size;
            other.m_root = nullptr;
            other.m_size = 0;
        }
    };
}
