#include <iostream>
using namespace std;

class test
{
    public:
        test()
        {
            cout << "create me ..." << endl;
        }
        ~test()
        {
            cout << "destroy me ... " << endl;
        }
        void copy()
        {
            test t2(*this);
        }
    private:
        test(const test&);
        test& operator = (const test&);
};

int main()
{
    test t1;
    t1.copy();
    return 0;
}
