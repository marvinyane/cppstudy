#include <iostream>

using namespace std;

class Base
{
    public:
        Base()
        {
            x = 0;
        }
        static void func(Base& b);
    private:
        int x;
};

void Base::func(Base& b)
{
    cout << b.x << endl;
    b.x++;
}

int main()
{
    Base b;

    Base::func(b);
    Base::func(b);
}
