#include <iostream>
#include<string>

using namespace std;

class Base{
    public:
        explicit Base(int a) : a(a)
        {
            cout << "here ? \n" ;
        }

        void show()const
        {
            cout << a << endl;
        }

        virtual void plus()
        {
            cout << "am i here ? " << endl;
            a += 20;
        }

        int a;

};

void func(Base t)
{
    t.show();
}

int main()
{
    Base a(3);
    func(a);

    func(5);
}
