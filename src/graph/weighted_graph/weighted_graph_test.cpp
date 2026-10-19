#include <iostream>
#include <string>
using namespace std;

#include "graph/weighted_graph/weighted_graph.hpp"


int main()
{
    dsa::weighted_graph<int> g;

    g.add_node("A");
    g.add_node("B");
    g.add_node("C");
    g.add_node("D");
    g.add_node("E");

    g.add_edge("A", "B", 4, true);
    g.add_edge("A", "C", 2, true);
    g.add_edge("B", "C", 1, true);
    g.add_edge("B", "D", 5, true);
    g.add_edge("C", "D", 8, true);
    g.add_edge("C", "E", 10, true);
    g.add_edge("D", "E", 2, true);

    auto result = g.dijkstra("A");

    // Imprime caminhos e custos a partir do nó "A"
    result.print_path("D");
    result.print_path("E");
    result.print_path("B");

    cout << "\n\n";
    return 0;
}
