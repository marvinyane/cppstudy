#include <iostream>
#include<string>

using namespace std;

class Base{
    public:
        explicit Base()
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
            a = 20;
        }

        int a;

};

class Derived : public Base{
    public:
        explicit Derived()
        {
            this->a = 2;
        }
        virtual void plus()
        {
            //Base::plus();
            this->a++;
        }
};


int main()
{
    Derived d;
    d.Base::plus();

    d.show();
}
