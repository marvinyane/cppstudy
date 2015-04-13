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

    cout << "am i here???? " << endl;
    this->name = new char[t.nameLen];
    strcpy(this->name, t.name);
    this->nameLen = t.nameLen;

    return *this;
}

test createObject()
{
    test t1("helloTest");
    cout << "the address of t1 is "<< &t1 << endl;
    return t1;
}

void Func(test &t)
{
    cout << "the address of t1 is "<< &t << endl;
    t.printName();
}



int main()
{
    //Func(createObject());
    test t = createObject();
    //cout << "the address of t1 is "<< &t << endl;
    test t1 = createObject();

    t = t1;
    
    return 0;
}
