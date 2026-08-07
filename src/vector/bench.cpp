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

    sw.measure(5, [&]() {
        for (int i = 0; i < 10'000; ++i)
            v1.push_back(i);
    });

    cout << "push_back (1): " << sw.get_result() << "\n";

    sw.measure(5, [&]() {
        for (int i = 0; i < 10'000; ++i)
            v1.push_front(i);
    });

    cout << "push_front (n): " << sw.get_result() << "\n";

    cout << "\n\n";
    return 0;
}
