#include <iostream>
#include <string.h>
using namespace std;

class test{
    private:
        int nameLen;
        char* name;
    public:
        test(const char* value)
        {
            this->nameLen = strlen(value) + 1;
            this->name = new char[this->nameLen];
            strcpy(this->name, value);
        }

        test(const test& t)
        {
            this->name = new char[t.nameLen];
            strcpy(this->name, t.name);
        }

        void printName()
        {
            cout << this->name << endl;
        }

        ~test()
        {
            delete[] name;
        }

        test& operator = (test& t);

};

test& test::operator = (test& t)
{
    if(this->name != NULL){
        delete[] name;
        this->nameLen = 0;
    }

    this->name = new char[t.nameLen];
    strcpy(this->name, t.name);
    this->nameLen = t.nameLen;

    return *this;
}



int main()
{
    test t1("hello");
    test t2("world");
    
    t1.printName();
    t2.printName();

    t2 = t1;

    t2.printName();

    return 0;
}
