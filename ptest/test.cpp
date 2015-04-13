#include <iostream>
#include "BluetoothTools.hpp"

int main()
{
    BDADDR a(0x01, 0x02, 0x03, 0x04, 0x05, 0x06);
    a.Display();

    BDADDR b(a);
    b.Display();

    BDADDR c = b;
    c.Display();

    BDADDR d;

    if (d == 0)
    {
        std::cout << "new address is empty" << std::endl;
    }

    if (a == c)
    {
        std::cout << "a is equal c" << std::endl;
    }

    return 0;
}
