#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "singly_linked_list.hpp"

template <typename T>
void print(const dsa::singly_linked_list<T>& list, char sep=' ')
{
    for (const auto& i : list)
        cout << i << sep;
    cout << "\n\n";
}

template <typename T>
void exists(const dsa::singly_linked_list<T>& list, const T& value)
{
    auto it = list.find(value);
    if (it != list.end()) {
        cout << value << " exists!\n";
    } else {
        cout << value << " does not exist!\n";
    }
}

int main()
{
    dsa::singly_linked_list<int> ints;
    ints.push_back(111);
    ints.push_front(222);
    ints.push_back(123);
    auto ints_b = ints;
    print(ints_b);

    dsa::singly_linked_list<string> fruits("apple", "mango", "grape");
    fruits.insert_after("watermelon", 0);
    fruits.push_front("banana");
    fruits.remove(3);
    print(fruits);

    exists<string>(fruits, "avocado");
    exists<string>(fruits, "apple");

    cout << "\n\n";
    return 0;
}
