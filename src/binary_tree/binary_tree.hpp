/**
 * Exemplo de implementação árvore binária de busca simples e semitens duplicados.
 * Operações: inserir, deletar, buscar, buscar máximo/mínimo e atravessar.
 * Autor: Philippe Matias
 */

#pragma once

#include "binary_tree_node.hpp"

#include <cstdint>
#include <cassert>
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
        explicit binary_tree() {} //O(1)

        /*----------------------------------*/
        explicit binary_tree(const binary_tree<T>& other) { //O(n)
            this->copy_data(other);
        }

        /*----------------------------------*/
        explicit binary_tree(binary_tree<T>&& other) { //O(1)
            this->move_data(std::forward<binary_tree<T>>(other));
        }

        /*----------------------------------*/
        ~binary_tree() { //O(n)
            this->clear();
        }

        /*----------------------------------*/
        auto length() const -> size_t { return m_size; } //O(1)
        auto empty()  const -> bool   { return m_size == 0; } //O(1)

        /*----------------------------------*/
        void insert(const T& item) //O(log(n)) no caso médio e O(n) no pior caso
        {
            this->create_root(item);

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
        bool remove(const T& item) //O(log(n)) no caso médio e O(n) no pior caso
        {
            assert(! this->empty());



            return false;
        }

        /*----------------------------------*/
        auto min() -> const T& //O(log(n)) no caso médio e O(n) no pior caso
        {
            assert(m_root != nullptr);

            auto it = m_root;
            while (it->left != nullptr)
                it = it->left;

            return it->data;
        }

        /*----------------------------------*/
        auto max() -> const T& //O(log(n)) no caso médio e O(n) no pior caso
        {
            assert(m_root != nullptr);

            auto it = m_root;
            while (it->right != nullptr)
                it = it->right;

            return it->data;
        }

        /*----------------------------------*/
        void clear() //O(n)
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
        void print(char sep = ' ') //O(n)
        {
            this->traverse([&](const T& i) {
                std::cout << i << sep;
            });
        }

        /*----------------------------------*/
        template <typename F, int Order = 1>
        void traverse(F lambda) //O(n)
        {
            auto f = [&](binary_tree_node<T>* node) { lambda(node->data); };

            if constexpr (Order == 1) {
                this->in_order(m_root, f);
            } else if (Order == 2) {
                this->pre_order(m_root, f);
            } else {
                this->post_order(m_root, f);
            }
        }

        /*----------------------------------*/
        auto operator = (const binary_tree<T>& other) -> const binary_tree<T>& //O(n)
        {
            this->copy_data(other);
            return *this;
        }

        /*----------------------------------*/
        auto operator = (binary_tree<T>&& other) -> binary_tree<T>& //O(1)
        {
            this->move_data(std::forward<binary_tree<T>>(other));
            return *this;
        }

    private:
        /*----------------------------------*/
        template <typename F>
        void in_order(binary_tree_node<T>* node, F lambda) //O(n)
        {
            if (node) {
                in_order(node->left, lambda);
                lambda(node);
                in_order(node->right, lambda);
            }
        }

        /*----------------------------------*/
        template <typename F>
        void pre_order(binary_tree_node<T>* node, F lambda) //O(n)
        {
            if (node) {
                lambda(node);
                pre_order(node->left, lambda);
                pre_order(node->right, lambda);
            }
        }

        /*----------------------------------*/
        template <typename F>
        void post_order(binary_tree_node<T>* node, F lambda) //O(n)
        {
            if (node) {
                post_order(node->left, lambda);
                post_order(node->right, lambda);
                lambda(node);
            }
        }

        /*----------------------------------*/
        void create_root(const T& item) //O(1)
        {
            if (m_root == nullptr) {
                m_size = 1;
                m_root = new binary_tree_node<T>(item);
            }
        }

        /*----------------------------------*/
        void copy_data(const dsa::binary_tree<T>& other) //O(n)
        {
            this->clear();
            other.in_order(other.m_root, [&](binary_tree_node<T>* n) {
                this->insert(n->data);
            });
        }

        /*----------------------------------*/
        void move_data(dsa::binary_tree<T>&& other) //O(1)
        {
            this->clear();
            m_root = other.m_root;
            m_size = other.m_size;
            other.m_root = nullptr;
            other.m_size = 0;
        }
    };
}
