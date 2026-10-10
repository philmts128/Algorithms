#pragma once

#include <iostream>
#include <cassert>
#include <map>
#include <stack>
#include <queue>

#include "graph_node.hpp"


namespace dsa
{
    /*----------------------------------*/
    class graph final
    {
    private:
        /*----------------------------------*/
        std::map<std::string, graph_node> m_nodes;

    public:
        /*----------------------------------*/
        graph() {}

        /*----------------------------------*/
        void add_node(std::string_view label)
        {
            graph_node g(label);
            m_nodes[label.data()] = g;
        }

        /*----------------------------------*/
        void add_edge(std::string_view node1, std::string_view node2, bool two_way = false)
        {
            auto& n1 = m_nodes[node1.data()].neighbors;
            n1.push_back(&m_nodes[node2.data()]);

            if (two_way) {
                auto& n2 = m_nodes[node2.data()].neighbors;
                n2.push_back(&m_nodes[node1.data()]);
            }
        }

        /*----------------------------------*/
        template <typename... Args>
        void add_edges(std::string_view node, Args... neighbors)
        {
            (this->add_edge(node, neighbors, false), ...);
        }

        /*----------------------------------*/
        void depth_first_search(std::string_view start_node)
        {
            std::stack<graph_node*> prev_nodes;
            std::map<std::string, int> time;
            graph_node* node = &m_nodes[start_node.data()];
            graph_node* prev = nullptr;

            prev_nodes.push(node);
            node->visited = true;
            this->print_path(prev, node);

            while (! prev_nodes.empty())
            {
                prev = prev_nodes.top();
                node = this->next_unvisited_node(prev_nodes.top()->label);
                time[node->label] += 1;

                if (node == nullptr) {
                    prev_nodes.pop();
                } else {
                    node->visited = true;
                    this->print_path(prev, node);
                    prev_nodes.push(node);
                }
            }

            this->unvisit_nodes();
        }

        /*----------------------------------*/
        void breadth_first_search(std::string_view start_node)
        {
            std::queue<graph_node*> wait_nodes;
            graph_node* cur_node = &m_nodes[start_node.data()];
            graph_node* prev_node = nullptr;

            wait_nodes.push(cur_node);
            cur_node->visited = true;
            this->print_path(prev_node, cur_node);

            while (!wait_nodes.empty())
            {
                cur_node = wait_nodes.front();
                wait_nodes.pop();

                for (graph_node* neighbor : cur_node->neighbors)
                {
                    if (!neighbor->visited)
                    {
                        time += 1;
                        prev_node = cur_node;
                        wait_nodes.push(neighbor);
                        neighbor->visited = true;
                        this->print_path(prev_node, neighbor);
                    }
                }
            }

            this->unvisit_nodes();
        }

        /*----------------------------------*/
        void print_nodes()
        {
             for (const auto& [label, node] : m_nodes)
             {
                 std::cout << label << ": | ";

                 for (graph_node* n : node.neighbors) {
                     std::cout << n->label << " | ";
                 }

                 std::cout << '\n';
             }
        }

        /*----------------------------------*/
        void print_neighbors(std::string_view node)
        {
            for (graph_node* g : m_nodes[node.data()].neighbors) {
                std::cout << g->label << '\n';
            }
        }

        /*----------------------------------*/
        auto next_unvisited_node(std::string_view label) -> graph_node*
        {
            auto& node = m_nodes[label.data()];
            for (graph_node* n : node.neighbors) {
                if (!n->visited) {
                    return n;
                }
            }

            return nullptr;
        }

        /*----------------------------------*/
        void unvisit_nodes()
        {
            for (auto& [label, node] : m_nodes) {
                node.visited = false;
            }
        }

        /*----------------------------------*/
        void print_path(const graph_node* prev, const graph_node* current)
        {
            std::string prev_label = (prev == nullptr) ? "none" : prev->label;
            std::cout << "(" << prev_label << " => "
                      << current->label <<  ") ";
        }
    };
}
