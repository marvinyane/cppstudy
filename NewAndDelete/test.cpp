#include <iostream>

using namespace std;

class test{
    public:
        test()
        {
            cout << "test start..." << endl;
        }

        ~test()
        {
            cout << "test stop..." << endl;
        }
};

void testFunc()
{
    test t;
    test *t1 = new test;
    test* t2= new test[10];

    cout << &t2[0] << " " << &t2[1] << endl;
    delete t1;
    delete [] t2;
}

int main()
{
    testFunc();
    return 0;
}
