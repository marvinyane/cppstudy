#include <functional>
#include <iostream>

class Base
{
    public:
        virtual void func(int a)
        {
            std::cout << "base " << a << "\n";
        }
};


class Derived : public Base
{
    public:
        void func(int a)
        {
            std::cout << "derived " << a << "\n";
        }
};

int main()
{
    Derived d;
    auto f1 = std::bind(&Base::func, d, 4);

    f1();

    return 0;
}
