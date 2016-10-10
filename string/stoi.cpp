#include <string>
#include <iostream>

int main()
{
    std::string a;

    //int t = std::stoi(a, NULL, 16);

    int t = strtol(a.c_str(), NULL, 16);

    std::cout << t << "\n";

    return 0;
}
