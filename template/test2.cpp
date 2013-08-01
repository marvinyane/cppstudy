#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class Base
{
    protected:
        void invert(size_t num)
        {
            cout << "Base " << num << endl;
        }
};

template <typename T, size_t n>
class Derived : private Base<T>
{
    private:
        using Base<T>::invert;

    public:
        void invert()
        {
            return invert(n);
        }
};

int main()
{
    Derived<int, 5> d;
    d.invert();
}
