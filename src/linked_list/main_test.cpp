#include <iostream>
using namespace std;

#include "singly_linked_list.hpp"

int main()
{
    dsa::singly_linked_list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.push_front(555);
    l.push_front(333);
    l.push_front(111);
    l.pop_back();
    //l.pop_front();
    l.print();

    cout << "\n\n";
    return 0;
}
