#include <iostream>

using namespace std;

class A
{
    public:
        int a1;
    private:
        int a2;
};

class B : public A
{
    public:
        int b1;
    private:
        int b2;
};

class C : public B
{
    public:
        int c1;
    private:
        int c2;
};

int main()
{
    B* b = new C;
    A* a = dynamic_cast<A*>(b);
    
}
