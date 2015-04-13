#include <iostream>
#include <vector>

using namespace std;

class A
{
    public:
        A(int a=1, int b=2):a1(a),a2(b)
    {

    }
    void func() const
    {
        cout << a1 << " " << a2 << endl;
    }
    private:
        int a1;
        int a2;
};

class B : public A
{
    public:
        B():A(1,2),b1(3), b2(4)
    {

    }
    void func() const 
    {
        cout << b1 << " " << b2 << endl;
    }
    private:
        int b1;
        int b2;
};

class C : public B
{
    public:
        C():B(), c1(5), c2(6)
    {

    }

    void func() const
    {
        cout << c1 << " " << c2 << endl;
    }
    private:
        int c1;
        int c2;
};

int main()
{
    B* b = new B;
    A* a = dynamic_cast<A*>(b);

    // check the different of virtual function or not
    a->func();
    b->func();
}
