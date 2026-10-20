#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>

#include "common/definitions.hpp"


DSA_NAMESPACE_BEGIN

/*----------------------------------*/
class graph final
{
private:
    /*----------------------------------*/
    struct node
    {
        fstring label;
        uint32_t id;
        bool visited { false };

        node() = default;
        node(fstring label) : label(label) { }
    };

    /*----------------------------------*/
    hash_map<fstring, node>     m_nodes;
    hash_map<uint32_t, fstring> m_labels;
    hash_map<uint32_t, fvector<uint32_t>> m_edges;

public:
    /*----------------------------------*/
    graph() = default;

    /*----------------------------------*/
    void add_node(const fstring& label)
    {
        node n(label);
        n.id = m_nodes.size();
        m_nodes[label] = n;
        m_labels[n.id] = label;
    }

    /*----------------------------------*/
    void add_edge(fstring node1, fstring node2, bool directed = true)
    {
        auto id1 = m_nodes[node1].id;
        auto id2 = m_nodes[node2].id;
        m_edges[id1].emplace_back(id2);

        if (!directed)
            m_edges[id2].emplace_back(id1);
    }

    /*----------------------------------*/
    template <typename... Args>
    void add_edges(fstring node, Args... neighbors)
    {
         (this->add_edge(node, neighbors, false), ...);
    }

    /*----------------------------------*/
    void depth_first_search(fstring start_node)
    {

        this->unvisit_nodes();
    }

    /*----------------------------------*/
    void breadth_first_search(fstring start_node)
    {

        this->unvisit_nodes();
    }

    /*----------------------------------*/
    void print_nodes()
    {
        for (const auto& [id, neighbors] : m_edges)
        {
            fstring node_label = m_labels[id];
            printf("%s: ", node_label.c_str());

            for (uint32_t neighbor : neighbors)
            {
                fstring neighb_label = m_labels[neighbor];
                printf("%s ", neighb_label.c_str());
            }

            printf("\n");
        }
    }

    /*----------------------------------*/
    void print_neighbors(fstring label)
    {
    }

    /*----------------------------------*/
    auto next_unvisited_node(fstring label) -> node*
    {

        return nullptr;
    }

    /*----------------------------------*/
    void unvisit_nodes()
    {
        for (auto& [_, node] : m_nodes) {
            node.visited = false;
        }
    }

    /*----------------------------------*/
    void print_path(const node* prev, const node* current)
    {

    }
};

DSA_NAMESPACE_END
