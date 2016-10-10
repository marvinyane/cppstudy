#include <iostream>
#include <memory>
#include <string.h>

class Test
{
public:
    Test()
    {

    }

    ~Test()
    {
        std::cout << "Test Destrutor!\n";
    }
};

template <typename T>
struct sharedPtr_delete
{
    void operator()(T* p)
    {
        std::cout << "delete shared pointer???\n";
        delete [] p;
    }
};

class Buffer : public std::shared_ptr<Test>
{
    public:
        Buffer(Test* t) : std::shared_ptr<Test>(t, sharedPtr_delete<Test>()){}
        Buffer() : std::shared_ptr<Test>(){}
};

bool getBuffer(Buffer& b, int& len)
{
    b = Buffer(new Test[10]);

    len = 10;

    return true;
}


int main()
{
    Buffer c;
    int len = 0;
    getBuffer(c, len);

    std::cout << "complete!!!?\n";
    
    return 0;
}
