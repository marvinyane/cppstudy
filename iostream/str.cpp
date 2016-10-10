#include <iostream>

int main()
{
    std::string str((std::istreambuf_iterator<char>(std::cin)), std::istreambuf_iterator<char>());
    std::cout << str << "\n";

    return 0;
}
