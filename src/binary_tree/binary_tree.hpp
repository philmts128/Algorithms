#pragma once

#include <iostream>
#include "common/definitions.hpp"
#include "binary_tree_node.hpp"


DSA_NAMESPACE_BEGIN

/*------------------------------*/
template <typename T>
class binary_tree final
{
private:
    /*------------------------------*/
    binary_tree_node<T>* m_root { nullptr };
    fsize m_size { 0 };

public:
    /*------------------------------*/
    binary_tree() = default;

    /*------------------------------*/
    binary_tree(const binary_tree<T>& other) {
        this->copy_data(other);
    }

    /*------------------------------*/
    binary_tree(binary_tree<T>&& other) {
        this->move_data(other);
    }

    /*------------------------------*/
    ~binary_tree() {
        this->clear();
    }

    /*------------------------------*/
    bool insert(const T& item)
    {
        if (m_root == nullptr) {
            m_root = new binary_tree_node<T>(item);
            m_size += 1;
            return true;
        }

        binary_tree_node<T>* it = m_root;
        for (;;)
        {
            if (item == it->data)
            {
                return false;
            }
            else if (item > it->data)
            {
                if (it->right == nullptr) {
                    it->right = new binary_tree_node<T>(item);
                    m_size += 1;
                    return true;
                } else {
                    it = it->right;
                }
            }
            else
            {
                if (it->left == nullptr) {
                    it->left = new binary_tree_node<T>(item);
                    m_size += 1;
                    return true;
                } else {
                    it = it->left;
                }
            }
        }
    }

    /*------------------------------*/
    bool exists(const T& item)
    {
        binary_tree_node<T>* it = m_root;

        while (it != nullptr)
        {
            if (item == it->data) {
                return true;
            } else if (item > it->data) {
                it = it->right;
            } else {
                it = it->left;
            }
        }

        return false;
    }

    /*------------------------------*/
    void clear()
    {
        if (m_root)
        {
            this->post_order(m_root, [](binary_tree_node<T>* n) {
                delete n;
            });

            m_size = 0;
            m_root = nullptr;
        }
    }

    /*------------------------------*/
    void print()
    {
        this->in_order(m_root, [](binary_tree_node<T>* n) {
            std::cout << n->data << " ";
        });
    }

    /*------------------------------*/
    auto operator = (const binary_tree<T>& other) -> binary_tree<T>
    {
        this->copy_data(other);
        return *this;
    }

    /*------------------------------*/
    auto operator = (binary_tree<T>&& other) -> binary_tree<T>
    {
        this->move_data(other);
        return *this;
    }

    /*------------------------------*/
    template <typename F>
    void in_order(binary_tree_node<T>* root, F exec)
    {
        if (root != nullptr) {
            in_order(root->left,  exec);
            exec(root);
            in_order(root->right, exec);
        }
    }

    /*------------------------------*/
    template <typename F>
    void pre_order(binary_tree_node<T>* root, F exec)
    {
        if (root != nullptr) {
            exec(root);
            pre_order(root->left,  exec);
            pre_order(root->right, exec);
        }
    }

    /*------------------------------*/
    template <typename F>
    void post_order(binary_tree_node<T>* root, F exec)
    {
        if (root != nullptr) {
            post_order(root->left,  exec);
            post_order(root->right, exec);
            exec(root);
        }
    }

    /*------------------------------*/
    void copy_data(const binary_tree<T>& other)
    {
        this->clear();
        auto other_ptr = const_cast<binary_tree<T>*>(&other);
        other_ptr->pre_order(other.m_root, [&](binary_tree_node<T>* n) {
            this->insert(n->data);
        });
    }

    /*------------------------------*/
    void move_data(binary_tree<T>&& other)
    {
        this->clear();
        this->m_root = other.m_root;
        this->m_size = other.m_size;
        other.m_root = nullptr;
        other.m_size = 0;
    }
};

DSA_NAMESPACE_END
