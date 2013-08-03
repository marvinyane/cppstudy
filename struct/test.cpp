#include <iostream>
#include <vector>
using namespace std;

struct A
{
    int a;
};

struct B : A
{
    int b;
};

int main()
{
    cout << sizeof(struct A) << endl;
    cout << sizeof(struct B) << endl;
}
