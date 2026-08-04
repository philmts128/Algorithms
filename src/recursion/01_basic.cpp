#include <iostream>
using namespace std;

int sum_digits(int n)
{
    if (n/10 == 0) return 1;
    else return sum_digits(n/10) + n%10;
}

long factorial(int n)
{
    if (n == 0) return 1;
    else return factorial(n-1) * n;
}

int main()
{
    cout << sum_digits(1234) << '\n';
    cout << factorial(5);

    cout << "\n\n";
    return 0;
}
