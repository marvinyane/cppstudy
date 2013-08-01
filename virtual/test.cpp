#include <iostream>
#include <string>

using namespace std;

class Base{
    public:
        virtual void a(int t)
        {
            cout << "Base print : " << t << endl;
        }
};


class Derived : public Base{
    public:
};

int main()
{
    Derived d;

    Base* pb = &d;
    Derived* pd = &d;


    pb->a(1);
    pd->a(1);

    pb->b(1);
    pd->b(1);

    pb->c(1);
    pd->c(1);

    return 0;
}

