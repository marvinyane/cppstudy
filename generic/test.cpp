#include <iostream>
#include <vector>

using namespace std;

template <class T>
class SmartPtr
{
    public:
        SmartPtr(T* t)
        {
            ptr = t;
        }
        ~SmartPtr()
        {
            //delete ptr;
        }

        template <typename U>
        SmartPtr(const SmartPtr<U>& u):ptr(u.get())
        {
            cout << "smart ptr copy create \n";
        }

        T* get()const
        {
            return ptr;
        }

    private:
        T* ptr;
};

class Base
{
    public:
        Base()
        {
            cout << "base create \n";
        }
        virtual ~Base()
        {
            cout << "base destroy \n";
        }
};

class Derived : public Base
{
    public:
        Derived()
        {
            cout << "Derived create \n";
        }

        ~Derived()
        {
            cout << "Derived destroy \n";
        }
};

int main()
{
    SmartPtr<Derived> sp2(new Derived);

    SmartPtr<Base> sp1(sp2);
}
