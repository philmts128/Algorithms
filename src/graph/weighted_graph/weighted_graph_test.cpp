#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
using namespace std;

#include "graph/weighted_graph/weighted_graph.hpp"


int main()
{
    dsa::weighted_graph g;

    g.add_node("A");
    g.add_node("B");
    g.add_node("C");
    g.add_node("D");

    g.add_edge("A", "B");
    g.add_edge("B", "C");
    g.add_edge("C", "D");
    g.add_edge("D", "A");
    g.add_edge("C", "A");

    g.print_nodes();

    cout << "\n\n";
    return 0;
}
