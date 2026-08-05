#include <iostream>
using namespace std;

#include "vector.hpp"

int main()
{
    dsa::vector<int> ints(1,2,3,4,5,6,7,8);
    auto ints_copy = std::move(ints);

    while (! ints_copy.empty())
        cout << ints_copy.pop_front() << ' ';

    cout << "\n";
    while (! ints.empty())
        cout << ints.pop_front() << ' ';

    cout << "\n\n";
    return 0;
}
