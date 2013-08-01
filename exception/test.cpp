#include <iostream>
#include <vector>
#include <exception>

using namespace std;

void func()
{
    int a = 0;
    
    throw exception();
}

int main()
{
    try{
        func();
    }
    catch(exception& e){
        cout << e.what() << endl;
    }
    catch(int){
        cout << "not here? \n";
    }
    catch(...){
        cout << "am i here ? \n";
    }
}
