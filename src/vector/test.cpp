#include <iostream>
#include <string>
using namespace std;

#include "vector.hpp"


/*-------------------------------*/
template <typename T>
void print(std::string_view str, const dsa::vector<T>& items, char space = ' ')
{
    cout << str << ": ";
    for (const auto& i : items)
        cout << i << space;
    cout << "\n";
}

/*-------------------------------*/
template <typename T>
void existe(const T& data, const dsa::vector<T>& items)
{
    if (items.exists(data)) {
        cout << data << " existe na posicao: " << items.find(data) << '\n';
    } else {
        cout << data << " nao existe!\n";
    }
}


/*-------------------------------*/
void test_str();
void test_int();


/*-------------------------------*/
int main()
{
    test_int();
    cout << "\n TESTANDO STRINGS \n\n";
    test_str();

    cout << "\n\n";
    return 0;
}


/*-------------------------------*/
void test_str()
{
    dsa::vector<string> fruits_a("apple", "grape", "watermelon", "guava");
    auto fruits_b = fruits_a;

    cout << "copiando fruits a para b: \n";
    print("fruits b", fruits_b);
    print("fruits a", fruits_a);

    dsa::vector<string> fruits_c;
    fruits_c = std::move(fruits_b);
    fruits_b.push_back("banana");
    fruits_b.push_front("strawberry");
    fruits_b.insert("orange", 1);

    cout << "\nmovendo ints b para c: \n";
    print("fruits c", fruits_c);
    print("fruits b", fruits_b);
    cout << "fruits b size: " << fruits_b.length() << "\n";

    cout << "\nremovendo elementos apple, watermelon e guava de fruits_a:\n";
    print("fruits a", fruits_a);
    fruits_a.pop_back();
    fruits_a.pop_front();
    fruits_a.remove(1); //watermelon está na posição 1
    print("ints a", fruits_a);

    cout << "\nusando funcao find em fruits a:\n";
    existe<string>("egg", fruits_a);
    existe<string>("grape", fruits_a);
}


/*-------------------------------*/
void test_int()
{
    dsa::vector<int> ints_a(1,2,3,4,5,6,7,8,9,10);
    auto ints_b = ints_a;

    cout << "copiando ints a para b: \n";
    print("ints_b", ints_b);
    print("ints_a", ints_a);

    auto ints_c = std::move(ints_b);
    ints_b.push_back(999);
    ints_b.push_front(111);
    ints_b.insert(455, 1);

    cout << "\nmovendo ints b para c: \n";
    print("ints c", ints_c);
    print("ints b", ints_b);
    cout << "ints b size: " << ints_b.length() << "\n";

    cout << "\nremovendo elementos 1, 10 e 5 de ints_a:\n";
    print("ints a", ints_a);
    ints_a.pop_back();
    ints_a.pop_front();
    ints_a.remove(3); //5 está na posição 3
    print("ints a", ints_a);

    cout << "\nusando funcao find em ints a:\n";
    existe(1200, ints_a);
    existe(6, ints_a);
}
