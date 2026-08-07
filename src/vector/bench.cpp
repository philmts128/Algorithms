#include <iostream>
#include <string>
using namespace std;

#include "benchmark/stopwatch.hpp"
#include "vector.hpp"

int main()
{
    dsa::vector<int> v1;
    dsa::vector<int> v2;

    long long a = 0;

    dsa::stopwatch sw;

    sw.measure(10, [&]() {
        for (int i = 0; i < 50'000; ++i)
            v1.push_back(i);
        //v1.clear();

    });
    v1.clear();
    cout << "push_back O(1): " << sw.get_result() << "\n";

    sw.measure(10, [&]() {
        for (int i = 0; i < 50'000; ++i)
            v2.push_front(i);
        //v2.clear();
    });
    v2.clear();
    cout << "push_front O(n): " << sw.get_result() << "\n";

    cout << "\n\n";
    return 0;
}
