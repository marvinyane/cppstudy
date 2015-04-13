#include <iostream>
#include <exception>

using namespace std;

class Base
{
    public:
        Base()
        {
            throw exception();
        }
};


int main()
{
    Base* b = new(std::nothrow) Base;

    if (b == 0)
    {
        cout << "constructor failed! \n";
    }
    
    return 0;
}
