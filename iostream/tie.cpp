#include <iostream>
#include <fstream>

int main()
{
    std::ostream* prevstr;
    std::ofstream ofs;
    ofs.open("test.txt");

    std::cout << "tie example:\n";

    *std::cin.tie() << "This is inserted into cout";
    prevstr = std::cin.tie(&ofs);
    *std::cin.tie() << "This is inserted into the file";
    std::cin.tie(prevstr);

    ofs.close();

    return 0;
}
