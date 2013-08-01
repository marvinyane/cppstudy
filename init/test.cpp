#include <iostream>
#include <string>
#include <list>
using namespace std;

class entry{
    public:
        entry()
        {
            cout << "create entry 1" << endl;
        }

        entry(const entry& e)
        {
            cout << "create entry 2" << endl;

        }

        const entry & operator=(const entry& e)
        {
            cout << "create entry 3" << endl;
        }
};

class test{
    private:
        string theName;
        string theAddr;
        list<int> phones;
        entry theEntry;

    public:
        test(const string& name, const string& addr, const list<int> phones, const entry& e)
            :theName(name),
            theAddr(addr),
            phones(phones),
            theEntry(e)
        {
        }   

        void show()
        {
            list<int>::iterator iter;
            cout <<"name: "<< this->theName << endl;
            cout << "address: " << this->theAddr << endl;

            for(iter = this->phones.begin(); iter != this->phones.end(); ++iter)
            {
                cout << *iter << endl;
            }

        }
};



int main()
{
    string name("marvin");
    string addr("shanghai.china");
    list<int> phones;
    phones.push_back(1);
    phones.push_back(2);

    entry e;

    test t(name, addr, phones, e);

    t.show();

    return 0;
}
