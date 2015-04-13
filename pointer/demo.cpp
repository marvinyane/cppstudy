#include <iostream>
#include <cstdio>

using namespace std;

class Base
{
    public:
        void func(int a) const
        {
            cout << "Base func 1 \n";
        }

        int func(void)
        {
            cout << "Base func 2 \n";
        }

        void func(int a)
        {
            cout << "Base func 3\n";
        }

};


int main()
{

    typedef void(Base::*P1)(int)const;
    typedef int(Base::*P2)(void);
    typedef void(Base::*P3)(int);

    P1 p1 = &Base::func;
    P2 p2 = &Base::func;
    P3 p3 = &Base::func;

    cout << reinterpret_cast<void*>(p1) << endl;
    cout << reinterpret_cast<void*>(p2) << endl;
    cout << reinterpret_cast<void*>(p3) << endl;


    Base b;
    (b.*p1)(1);
    (b.*p2)();
    (b.*p3)(2);

    return 0;
}
