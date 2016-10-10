#include <iostream>
#include <fstream>

int main()
{
    std::streambuf *psbuf, *backup;
    std::ofstream filestr;
    filestr.open("test.txt");

    backup = std::cout.rdbuf();

    psbuf = filestr.rdbuf();
    std::cout.rdbuf(psbuf);

    std::cout << "This is written to the file";

    std::cout.rdbuf(backup);

    filestr.close();

    return 0;
}
