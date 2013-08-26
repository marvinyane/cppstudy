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
        int func(double b)
        {
            cout << "Derived " << endl;
        }
};

int main()
{
    Base * d = new Derived;

    int a = 3;
    double b = 4;

    d->func(a);/*Base*/
    d->func(b);/*Base*/

    return 0;
}
