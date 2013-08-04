#include <utility>
#include <tuple>
#include <iostream>
#include <functional>

using namespace std;

int main()
{
    int i = 0;
    auto p1 = std::make_pair(std::ref(i), std::ref(i));
    ++p1.first;
    ++p1.second;

    std::cout << "i = " << i << std::endl;

    std::pair<char, char> p = std::make_pair('x', 'y');

    char c;

    std::tie(std::ignore, c) = p;

    std::cout << "c = " << c << endl;

}
