#include <iostream>
#include <string>
#include <memory>
#include <cstring>

using namespace std;
int main()
{
    string s(0, 0);

    std::cout << "s size is " << s.size() << "\n";

    string t(20, 0);

    memcpy(const_cast<char*>(t.data()), "hello", 6);

    t.resize(6);

    std::cout << "t size is " << t.size() << "\n";

    string data1(6, 0);
    data1[0] = 0;
    data1[1] = 0;
    data1[2] = 0;
    data1[3] = 0;
    data1[4] = 1;
    data1[5] = 10;

    std::cout << "data1 size is " << data1.size() << "length is " << data1.length() <<  "\n";

    for (int i = 0; i < data1.size(); i++)
    {
        std::cout << data1.c_str()[i] << "\n";
    }


    return 0;
}
