#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>


namespace dsa
{
    /*----------------------------------*/
    template <typename data_type>
    class graph final
    {
    private:
        /*----------------------------------*/
        struct node {
            data_type data;
            bool visited { false };
            std::string label;
            node() { }
            node(std::string_view label) : label(label) { }
        };

        /*----------------------------------*/
        std::unordered_map<std::string_view, node>  m_nodes;
        std::unordered_map<std::string_view, std::vector<node*>> m_edges;

    public:
        /*----------------------------------*/
        graph() {}

        /*----------------------------------*/
        void add_node(std::string_view label, data_type data = {})
        {
            auto n = node(label);
            n.data = data;
            m_nodes[label] = n;
        }

        /*----------------------------------*/
        void add_edge(std::string_view node1, std::string_view node2, bool two_way = false)
        {
            m_edges[node1].push_back(&m_nodes[node2]);

            if (two_way) {
                m_edges[node2].push_back(&m_nodes[node1]);
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
            std::stack<node*> prev_nodes;
            node* curr_node = &m_nodes[start_node];
            node* prev_node = nullptr;

            prev_nodes.push(curr_node);
            curr_node->visited = true;
            this->print_path(prev_node, curr_node);

            while (! prev_nodes.empty())
            {
                prev_node = prev_nodes.top();
                curr_node = this->next_unvisited_node(prev_nodes.top()->label);


                if (curr_node == nullptr) {
                    prev_nodes.pop();
                } else {
                    curr_node->visited = true;
                    this->print_path(prev_node, curr_node);
                    prev_nodes.push(curr_node);
                }
            }

            this->unvisit_nodes();
        }

        /*----------------------------------*/
        void breadth_first_search(std::string_view start_node)
        {
            std::queue<node*> wait_nodes;
            node* curr_node = &m_nodes[start_node];
            node* prev_node = nullptr;

            wait_nodes.push(curr_node);
            curr_node->visited = true;
            this->print_path(prev_node, curr_node);

            while (!wait_nodes.empty())
            {
                curr_node = wait_nodes.front();
                wait_nodes.pop();

                for (node* neighbor : m_edges[curr_node->label])
                {
                    if (!neighbor->visited)
                    {
                        prev_node = curr_node;
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
             for (const auto& [label, n] : m_nodes)
             {
                 std::cout << label  << ": | Data: "
                           << n.data << " | Neighbors: ";

                 for (node* neigh : m_edges[label]) {
                     std::cout << neigh->label << " | ";
                 }

                 std::cout << '\n';
             }
        }

        /*----------------------------------*/
        void print_neighbors(std::string_view label)
        {
            for (node* neighbor : m_edges[label]) {
                std::cout << neighbor->label << '\n';
            }
        }

        /*----------------------------------*/
        auto next_unvisited_node(std::string_view label) -> node*
        {
            for (node* neighbor : m_edges[label]) {
                if (!neighbor->visited) {
                    return neighbor;
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
        void print_path(const node* prev, const node* current)
        {
            std::string prev_label = (prev == nullptr) ? "none" : prev->label;
            std::cout << "(" << prev_label << " => "
                      << current->label <<  ") ";
        }
    };
}
