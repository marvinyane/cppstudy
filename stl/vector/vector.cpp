#include <iostream>
#include <vector>

using namespace std;

class Base
{
    public:
        Base(int a);
        virtual ~Base();
        void show();
    private:
        int a;
};

Base::Base(int a):a(a)
{
}

Base::~Base()
{
}

void Base::show()
{
    cout << a << endl;
}

int main()
{
    vector<Base> v1, v2;

    for(int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }

    v2.assign(v1.begin() + v1.size()/2, v1.end());

    vector<Base>::iterator iter = v2.begin();

    while(iter != v2.end())
    {
        iter->show();
        iter++;
    }

    return 0;

}

