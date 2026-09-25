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

    cout << "min: " << langs.min() << "\n";
    cout << "max: " << langs.max() << "\n\n";

    langs.remove("Python");
    langs.print('\n');

    cout << "\n\n";
    return 0;
}
