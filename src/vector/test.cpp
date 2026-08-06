#include <iostream>
using namespace std;

#include "vector.hpp"

template <typename T>
void print(const dsa::vector<T>& items, char space = ' ')
{
    cout << "\n";
    for (const auto& i : items)
        cout << i << space;
    cout << "\n";
}

int main()
{
    dsa::vector<string> fruits;
    fruits.push_back("apple");
    fruits.push_back("grape");
    fruits.push_back("mango");

    print(fruits, '\n');

    cout << "\n\n";
    return 0;
}
