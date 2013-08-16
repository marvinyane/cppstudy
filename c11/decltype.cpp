#include <iostream>

using namespace std;

template <class T, class U>
auto getSum(const T& t, const U& u) -> decltype(t+u)
{
    return t + u;
}

int main()
{
    int a = 32;
    double b = 3.14;

    auto c = getSum(a, b);

    cout << c << endl;
}
