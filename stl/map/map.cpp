#include <iostream>
#include <map>
#include <string>

using namespace std;

class Base
{
    public:
        Base(int a);
        virtual ~Base();

        void show()const;
    private:
        Base(const Base&);
        Base& operator=(const Base&);
        int a;
};

Base::Base(int a):a(a)
{
}
Base::~Base()
{
}

void Base::show()const
{
    cout << "hello show " << a << endl;
}

int main()
{
    // check why not reference
    map<string, Base*> m;
    Base *b1 = new Base(1);
    Base *b2 = new Base(2);

    m.insert(make_pair("hello", b1));
    m.insert(make_pair("world", b2));

    map<string, Base*>::iterator iter = m.begin();

    while(iter != m.end())
    {
        cout << iter->first << endl;
        iter->second->show();

        delete iter->second;

        iter++;
    }
}




