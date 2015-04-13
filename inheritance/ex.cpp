#include <iostream>

using namespace std;

class Base
{
    public:
        Base()
        {
            cout << "create Base... \n";
        }

        // this function must be virtual!
        virtual ~Base()
        {
            cout << "delete Base... \n";
        }
};

class Derived : public Base
{
    public:
        Derived()
        {
            cout << "create Derived... \n";
        }
        ~Derived()
        {
            cout << "delete Derived... \n";
        }
};

int main()
{
    Base* d = new Derived;
    delete d;
}
