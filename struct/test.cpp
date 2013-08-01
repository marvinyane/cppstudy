#include <iostream>
#include <vector>

struct A
{
    int a;
};

struct B : public struct A
{
    int b;
};

int main()
{
    cout << sizeof(struct A) << endl;
    cout << sizeof(struct B) << endl;
}
