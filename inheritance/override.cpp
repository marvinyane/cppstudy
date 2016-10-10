#include <iostream>

using namespace std;

class Base
{
    public:
        virtual int func(int a)
        {
            cout << "Base" << endl;
        }
};

class Derived : public Base
{
    public:
        int func(int a)
        {
            cout << "derived " << a << endl;
        }

        int func(double b)
        {
            cout << "Derived " << endl;
        }
};

int main()
{
    Base* d = new Derived;
    d->func(3);

    return 0;
}
