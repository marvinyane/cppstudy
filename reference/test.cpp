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

    string s1("world");
    string &rs1 = s1;

    rs = rs1;

    cout << "s : " << s << "\n";
}
