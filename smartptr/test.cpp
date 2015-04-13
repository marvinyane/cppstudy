#include <iostream>
#include <memory>

using namespace std;

class Base{
    public:
        Base()
        {
            cout << "create" <<endl;
        }
        ~Base()
        {
            cout << "Destroy" <<endl;
        }
};

shared_ptr<Base> createFactroy(int m)
{
    shared_ptr<Base> ptr(new Base);

    return ptr;
}


int main()
{
    /*
    auto_ptr<Base> pObj(new Base());
    auto_ptr<Base> pObj2(pObj);

    cout << pObj.get() << endl;
    cout << pObj2.get() << endl;
    */

    shared_ptr<Base> ptr = createFactroy(2);
    cout << "Destroy start or over \n";
}
