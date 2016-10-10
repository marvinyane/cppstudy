#include <iostream>

struct Test
{
    int m;
};

struct Derived : Test
{

};

void test_func_1()
{
    int Test::* p = &Test::m;
    Test t = {5};
    std::cout << t.*p << "\n";
    t.m = 10;
    std::cout << t.*p << "\n";
}

void test_func_2()
{
    int Test::* p = &Test::m;
    int Derived::* dp = p;
    Derived d;
    d.m = 1;
    std::cout << d.*dp << ' ' << d.*p << '\n';
}

int main()
{
    test_func_1();
    test_func_2();

    return 0;
}
