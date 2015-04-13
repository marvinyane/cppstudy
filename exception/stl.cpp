#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

void funcA()
{
    throw "hello";
}

int funcB()
{
    try 
    {
        funcA();

        return 0;
    }
    catch(...)
    {
        return 1;
    }
}

int main()
{

    int a = funcB();

    cout << a << endl;
}
