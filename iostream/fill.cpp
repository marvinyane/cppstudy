#include <iostream>
#include <fstream>

int main()
{
    std::ofstream filestr;
    filestr.open("test.txt");

    std::cout.fill('*');
    std::cout.width(40);

    filestr.copyfmt(std::cout);

    std::cout << 40;
    filestr << 40;


    return 0;
}
