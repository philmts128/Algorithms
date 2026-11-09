#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "binary_tree.hpp"


int main()
{
    dsa::binary_tree<int> tree;

    for (int i = 100; i >= 0; --i)
        tree.insert(i);

    auto t2 = tree;
    t2.print();

    cout << boolalpha << t2.exists(999);

    cout << "\n\n";
    return 0;
}
