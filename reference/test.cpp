#include <iostream>

#include <string>

using namespace std;

int main()
{
    string s("hello");

    cout << sizeof(string) << endl;
    cout << sizeof(s) << endl;

    string &rs = s;

    cout << sizeof(rs) << endl;
}
