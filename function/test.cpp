#include <iostream>
#include <vector>

#include <tr1/memory>
#include <tr1/functional>

using namespace std;

class Base{
    public:
        /*default*/
        virtual ~Base(){

        }
        virtual void baseFunc(int a);
};
class Derived : public Base{
    public:
        virtual void baseFunc(int a);

};

void  Base::baseFunc(int a)
{
    cout << "Base Func " << a << endl;
}
void  Derived::baseFunc(int a)
{
    cout << "Derived Func " << a << endl;
}

int main()
{
    tr1::shared_ptr<Base> sp(new Derived);
    
    typedef tr1::function<void (int)> funcPtr;

    funcPtr func = tr1::bind(&Base::baseFunc, sp,  tr1::placeholders::_1 );

    func(3);
}

int main()
{
    for(i = 0; i < MAX; i++)

}
