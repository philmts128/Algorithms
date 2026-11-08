#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "graph/graph/graph.hpp"


int main()
{
    dsa::graph g;

    g.add_node("A");
    g.add_node("B");
    g.add_node("C");
    g.add_node("D");

    g.add_dir_edges("A", "B", "C");
    g.add_dir_edges("B", "C");
    g.add_dir_edges("C", "D");
    g.add_dir_edges("D", "A");

    g.depth_first_search("A");

    cout << "\n\n";
    return 0;
}
