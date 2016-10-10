#include <iostream>

int main()
{
    std::cout.flags(std::ios::right | std::ios::hex | std::ios::showbase);
    std::cout.width(10);
    std::cout << 100 << "\n";

    std::cout.setf(std::ios::hex, std::ios::basefield);
    std::cout.setf(std::ios::showbase);

    std::cout << 100 << "\n";
    std::cout.unsetf(std::ios::showbase);
    std::cout << 100 << "\n";

    return 0;
}
