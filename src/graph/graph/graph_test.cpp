#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
using namespace std;

#include "graph/graph/graph.hpp"


int main()
{
    dsa::graph<int> g;

    g.add_node("S", 1);
    g.add_node("A", 2);
    g.add_node("B", 3);
    g.add_node("C", 4);
    g.add_node("D", 5);
    g.add_node("E", 6);
    g.add_node("F", 7);

    g.add_edges("S", "A", "B");
    g.add_edges("A", "S", "C", "D");
    g.add_edges("B", "S", "D", "E");
    g.add_edges("C", "A", "F");
    g.add_edges("D", "A", "B", "F");
    g.add_edges("E", "B");
    g.add_edges("F", "C");

    cout << "BFS: ";
    g.breadth_first_search("S");
    cout << "\n\nDFS: ";
    g.depth_first_search("S");

    cout << "\n\nGraph nodes:\n";
    g.print_nodes();

    cout << "\n\n";
    return 0;
}
