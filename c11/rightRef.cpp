#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

void funcA(const string& t)
{
    cout << t << endl;
}

int main()
{
    funcA(string("hello"));

    return 0;
}

