#include <iostream>
#include <string>
#include <tr1/memory>

using namespace std;

class Base{
    public:
        Base()
        {
            cout << "null base \n";
        }
        Base(int c)
        {
            cout << "Base..." << c << endl;
        }
        virtual ~Base()
        {
            cout << "delete Base..." << endl;
        }

        virtual int func1() ;
};

int Base::func1()
{
    cout << "Base func1" << endl;
}

class Derived : public Base{
    public:
        //Derived(int c):Base(createParamter(c))
        Derived(int c)
        {
            cout << "Derived... " << c << endl;
        }
        ~Derived()
        {
            cout << "Delete Derived... " << endl;
        }
        int func1()
        {
            cout << "Derived" << endl;
        }
    private:
        static int createParamter(int c)
        {
            return ++c;
        }
};



int main()
{
    tr1::shared_ptr<Base> sp(new Derived(2));
    sp->func1();
    sp->Base::func1();
    return 0;
}
