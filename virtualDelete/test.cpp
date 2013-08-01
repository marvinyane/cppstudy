#include <iostream>
#include <string>

using namespace std;


class base{
    public:
        base()
        {
            cout << "create base ... \n" << endl;
        }
        virtual ~base()
        {
            cout << "delete base ... \n" << endl;
        }
};

class derive :public  base{
    public:
        derive()
        {
            cout << "create derive ... \n" << endl;
        }
        ~derive()
        {
            cout << "destroy derive... \n" << endl;
        }
};

int main()
{
    base* b = new derive;

    delete b;

    return 0;
}
