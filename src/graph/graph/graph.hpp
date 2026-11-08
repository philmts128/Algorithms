#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <limits>
#include "common/definitions.hpp"


DSA_NAMESPACE_BEGIN

/*-------------------------------------*/
class graph
{
private:
    /*-------------------------------------*/
    static constexpr u32 Not_Found = std::numeric_limits<u32>::max();

    /*-------------------------------------*/
    struct node_t
    {
        fvector<u32> neighbors;
        fstring label;
        u32 id;
        bool visited { false };

        node_t() = default;
        node_t(u32 id, fstring label) : id(id), label(label) {}
    };

private:
    /*-------------------------------------*/
    hash_map<uint32_t, node_t> m_nodes;
    hash_map<fstring, u32> m_labels;

public:
    /*-------------------------------------*/
    graph() = default;

public:
    /*-------------------------------------*/
    void add_node(fstr_view label)
    {
        u32 id = m_nodes.size();
        m_labels[label.data()] = id;
        m_nodes[id] = node_t(id, label.data());
    }

    /*-------------------------------------*/
    void add_edge(fstr_view node1, fstr_view node2, bool two_ways = false)
    {
        u32 id1 = m_labels[node1.data()];
        u32 id2 = m_labels[node2.data()];
        node_t& n1 = m_nodes[id1];
        n1.neighbors.push_back(id2);

        if (two_ways) {
            node_t& n2 = m_nodes[id2];
            n2.neighbors.push_back(id1);
        }
    }

    /*-------------------------------------*/
    template <typename... Args>
    void add_dir_edges(fstr_view node, Args... args)
    {
        ((this->add_edge(node, args, false)), ...);
    }

    /*-------------------------------------*/
    void depth_first_search(fstr_view start_node)
    {
        u32 start_id = m_labels[start_node.data()];
        fstack<u32> prev_nodes;

        prev_nodes.push(start_id);
        m_nodes[start_id].visited = true;
        printf("%s ", m_nodes[prev_nodes.top()].label.c_str());

        while (! prev_nodes.empty())
        {
            u32 node = this->next_unvisited_node(prev_nodes.top());

            if (node == Not_Found) {
                prev_nodes.pop();
            } else {
                prev_nodes.push(node);
                m_nodes[node].visited = true;
                printf("%s ", m_nodes[prev_nodes.top()].label.c_str());
            }
        }

        this->unvisit_nodes();
    }

    /*-------------------------------------*/
    void print()
    {
        for (const auto& [id, node] : m_nodes)
        {
            printf("(%s | %d) => ", node.label.c_str(), id);

            for (u32 nid : node.neighbors) {
                printf("(%s | %d) ", m_nodes[nid].label.c_str(), nid);
            }

            printf("\n");
        }
    }

private:
    /*-------------------------------------*/
    u32 next_unvisited_node(u32 node_id)
    {
        for (u32 id : m_nodes[node_id].neighbors) {
            if (!m_nodes[id].visited) {
                return id;
            }
        }

        return Not_Found;
    }

    /*-------------------------------------*/
    void unvisit_nodes()
    {
        for (auto& [_, node] : m_nodes) {
            node.visited = false;
        }
    }
};

DSA_NAMESPACE_END
