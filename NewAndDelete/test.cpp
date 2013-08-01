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
    delete t1;
}

int main()
{
    testFunc();
    return 0;
}
