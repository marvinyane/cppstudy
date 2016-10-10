#include <iostream>
#include "test.h"

using namespace std;

template<typename T>
inline const T& MyMax(const T& a, const T& b)
{
    return a > b ? a : b;
}

ostream& operator << (ostream& s, const testCase& r)
{
    s << "hello" << r.a << ':' << r.b;
    return s;
}

bool testCase::operator > (const testCase& r)const
{
    if(this->a >> r.a && this->b >> r.b){
        return true;
    }

    return false;
}

int main()
{
    testCase t1(2,3);
    testCase t2(3,4);

    const testCase& r = MyMax(t1, t2);

    cout << r << endl;
}
