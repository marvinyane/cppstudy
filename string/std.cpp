#include <iostream>
#include <string>
#include <memory>
#include <cstring>

using namespace std;
int main()
{
    char* s = new char[20];
    memcpy(s, "Wawawawawawa!", 14);

    string t(s, 20);

    s[2] = 't';

    cout << t << endl;

    return 0;
}
