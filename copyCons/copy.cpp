#include <iostream>

using namespace std;

class A
{

    public:
        int a;
        A(): a(5)
        {
            cout << "Constructor : " << &a << endl;
        }

        void print()
        {
            cout << a << endl;
        }
    //private:
        A(const A &b)
        {
            a = b.a+1;
            cout << "Copy Constructor : " << (void*)this << (void*)&b << endl;
        }
        A& operator =  (const A &a){cout << "hello world \n"; return *this;};
};

void func(const A& a)
{
    cout << "the address of tempory : " << (void*)&a << endl;
}

int main()
{

    func(A());
}
