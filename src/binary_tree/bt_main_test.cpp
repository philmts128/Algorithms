#include <iostream>
#include <string>
using namespace std;

#include "binary_tree.hpp"


int main()
{
    dsa::binary_tree<string> langs;
    langs.insert("C");
    langs.insert("C++");
    langs.insert("Python");
    langs.insert("Java");
    langs.insert("C#");

    langs.print();

    cout << "\n\n";
    return 0;
}
