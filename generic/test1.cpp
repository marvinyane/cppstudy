#include <iostream>
#include <vector>
#include "../timer/timer.h"

using namespace std;

class TestTimer;

template <unsigned n>
struct Factorial 
{
    enum
    {
        value = n * Factorial<n-1>::value
    };
};

template<>
struct Factorial<0>
{
    enum 
    {
        value = 1
    };
};

int main()
{
    TestTimer *t1 = new TestTimer("Factorial 5");
    cout << Factorial<5>::value << endl;
    delete t1;

    t1 = new TestTimer("Factorial 10");
    cout << Factorial<10>::value << endl;
    delete t1;
}
