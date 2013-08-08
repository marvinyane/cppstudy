#include <iostream>

using namespace std;

class A
{
    public:
        A(int a):i_a(a)
        {
            cout << "create " << i_a << endl;
        }
        ~A()
        {
            cout << "delete " << i_a << endl;
        }
        A operator+(const A& a2)
        {
            return A(this->i_a + a2.i_a);
        }

        int i_a;
};

int main()
{
    A a1(1);
    A a2(2);

    const A& a3 = a1 + a2;
    cout << "--------------------------\n";
}
