#include <iostream>
using namespace std;

#include "vector.hpp"

int main()
{
    dsa::vector<int> ints;

    for ( int i = 0; i < 100; ++i)
        ints.push_back(i);

    for (int i = 0; i < 100; ++i)
        cout << ints[i] << ' ';

    cout << "\n\n";
    return 0;
}
