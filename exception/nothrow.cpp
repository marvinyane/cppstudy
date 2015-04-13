#include <iostream>
#include <exception>

class Test
{
    public:
        Test() : a(3) throw()
        {
        }
        void thow() const throw()
        {
            std::cout << a << std::endl;
        }
    private:
        int a;
};


int main()
{
    Test * t = new (std::nothrow) Test();

    try
    {
        t->thow();
    }
    catch(...)
    {

    }

    return 0;
}
