#pragma once

#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>


namespace dsa
{
    /*------------------------------*/
    template <typename data_type>
    class weighted_graph final
    {
    private:
        /*------------------------------*/
        static constexpr auto infinity = std::numeric_limits<int>::max();

        /*------------------------------*/
        struct node
        {
            data_type data;
            std::string label;

            node() {};
            node(std::string label, const data_type& data = {})
                : label(label), data(data) { }
        };

        /*------------------------------*/
        struct edge
        {
            int weight { 1 };
            std::string to;

            edge() {};

            edge(std::string to, int weight = 1)
                : to(to), weight(weight) { }
        };

        /*------------------------------*/
        struct dijkstra_result
        {
            std::unordered_map<std::string, int> dist;
            std::unordered_map<std::string, std::string> pred;
            std::string start;

            void print_path(const std::string& target)
            {
                auto it = dist.find(target);
                if (it == dist.end() || it->second == infinity) {
                    std::cout << "There is no path to " << target << '\n';
                    return;
                }

                std::cout << "Total cost from " << start << " to " << target << ": " << it->second;
                std::cout << "\nPath: ";

                std::vector<std::string> path;
                for (std::string cur = target; !cur.empty(); cur = pred.at(cur)) {
                    path.push_back(cur);
                }

                std::reverse(path.begin(), path.end());

                for (size_t i = 0; i < path.size(); ++i) {
                    std::cout << path[i] << (i + 1 < path.size() ? "->" : "");
                }

                std::cout << "\n\n";
            }
        };

    private:
        /*------------------------------*/
        std::unordered_map<std::string, node> m_nodes;
        std::unordered_map<std::string, std::vector<edge>> m_edges;

    public:
        /*------------------------------*/
        weighted_graph() = default;

        /*------------------------------*/
        void add_node(std::string label, const data_type& data = {})
        {
            m_nodes[label] = node(label, data);
        }

        /*------------------------------*/
        void add_edge(std::string node1, std::string node2,
                      int weight = 1, bool two_ways = false)
        {
            m_edges[node1].emplace_back(node2, weight);

            if (two_ways) {
                m_edges[node2].emplace_back(node1, weight);
            }
        }

        /*------------------------------*/
        auto dijkstra(std::string start_node) -> dijkstra_result
        {
            using pq_pair = std::pair<int, std::string>;

            dijkstra_result result;
            result.start = start_node;

            for (const auto& [label, _] : m_nodes) {
                result.dist[label] = infinity;
                result.pred[label] = "";
            }

            result.dist[start_node] = 0;

            std::priority_queue<pq_pair, std::vector<pq_pair>, std::greater<pq_pair>> pq;
            pq.push({0, start_node});

            while (!pq.empty())
            {
                auto [current_dist, u] = pq.top();
                pq.pop();

                if (current_dist > result.dist[u]) {
                    continue;
                }

                auto edge_it = m_edges.find(u);
                if (edge_it != m_edges.end())
                {
                    for (const edge& e : edge_it->second)
                    {
                        const std::string& v = e.to;
                        int weight = e.weight;

                        if (result.dist[u] + weight < result.dist[v]) {
                            result.dist[v] = result.dist[u] + weight;
                            result.pred[v] = u;
                            pq.push({result.dist[v], v});
                        }
                    }
                }
            }

            return result;
        }

        /*------------------------------*/
        void print_nodes()
        {
            for (const auto& [label, n] : m_nodes)
            {
                std::cout << label << ": ";

                for (const edge& e : m_edges[label])
                {
                    std::cout << "("   << e.neighbor->label
                              << " | " << e.weight  << ") ";
                }

                std::cout << '\n';
            }
        }
    };
}
