#pragma once

#include <unordered_map>
#include <map>
#include <vector>
#include <iostream>

#include "weighted_graph_node.hpp"


namespace dsa
{
    /*----------------------------------------*/
    class weighted_graph final
    {
    private:
        /*----------------------------------------*/
        struct edge {
            uint16_t weight;
            weighted_graph_node* node;

            edge(weighted_graph_node* node, uint16_t weight = 1) {
                this->node = node;
                this->weight = weight;
            }
        };

    private:
        /*----------------------------------------*/
        std::unordered_map<std::string, dsa::weighted_graph_node> m_nodes;
        std::map<std::string, std::vector<edge>> m_edges;

    public:
        /*----------------------------------------*/
        weighted_graph() { }

        /*----------------------------------------*/
        void add_node(std::string_view label)
        {
            m_nodes[label.data()] = weighted_graph_node(label);
        }

        /*----------------------------------------*/
        void add_edge(std::string_view node1, std::string_view node2,
                      uint16_t weight = 1, bool two_ways = false)
        {
            auto* n1 = &m_nodes[node1.data()];
            auto* n2 = &m_nodes[node2.data()];

            m_edges[n1->label].emplace_back(n2, weight);
            if (two_ways)
                m_edges[n2->label].emplace_back(n1, weight);
        }

        /*----------------------------------------*/
        void dijkstra(std::string_view start_node)
        {
            auto* current_node = &m_nodes[start_node.data()];
            current_node->visited = true;

            std::map<edge*> minimum;
        }

        /*----------------------------------------*/
        void print_nodes()
        {
            for (const auto& [label, node] : m_nodes)
            {
                std::cout << label << ": ";

                for (const auto& e : m_edges[label.data()])
                {
                    std::cout << "("   << e.node->label
                              << " | " << e.weight << ") ";
                }

                std::cout << '\n';
            }
        }
    };
}
