#include <iostream>
using namespace std;

#include "vector.hpp"

int main()
{
    dsa::vector<int> ints(1,2,3,4,5,6,7,8);
    auto ints_copy = std::move(ints);

    ints_copy.remove(4);

    for (int i : ints_copy)
        cout << i  << ' ';

    cout << "\n\n";
    return 0;
}
