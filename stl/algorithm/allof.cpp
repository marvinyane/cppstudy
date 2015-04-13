#include <iostream>
#include <algorithm>
#include <array>

int main()
{
    std::array<int, 8> foo = {3, 5, 7, 9, 11, 13, 17, 19};

    if (std::all_of(foo.begin(), foo.end(), [](int i){return i % 2;}))
    {
        std::cout << "all the elements are odd number \n";
    }

    return 0;
}
