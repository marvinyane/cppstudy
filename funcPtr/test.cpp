#include <stdio.h>

using namespace std;
class base
{
    public:
        base():a(0)
        {

        }

        int geta()
        {
            return ++a;
        }

        static base* getInstance();
    private:
        static base* instance;
        int a;
};

base* base::instance = NULL;

base* base::getInstance()
{
    if (instance == NULL)
        instance = new base;

    return instance;
}

int main()
{
    base * b = base::getInstance();
    int a = b->geta();

    printf("%d \n", a);
}
