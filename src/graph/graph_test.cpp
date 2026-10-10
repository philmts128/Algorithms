#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
using namespace std;

#include "graph/graph.hpp"


int main()
{
    dsa::graph g;

    g.add_node("S");
    g.add_node("A");
    g.add_node("B");
    g.add_node("C");
    g.add_node("D");
    g.add_node("E");
    g.add_node("F");

    g.add_edges("S", "A", "B");
    g.add_edges("A", "S", "C", "D");
    g.add_edges("B", "S", "D", "E");
    g.add_edges("C", "A", "F");
    g.add_edges("D", "A", "B", "F");
    g.add_edges("E", "B");
    g.add_edges("F", "C");

    g.depth_first_search("S");

    cout << "\n\n";
    return 0;
}
