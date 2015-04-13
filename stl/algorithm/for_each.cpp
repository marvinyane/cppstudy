#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> myvector;
    myvector.push_back(10);
    myvector.push_back(20);
    myvector.push_back(30);

    for_each(myvector.begin(), myvector.end(), [](int i){std::cout << ' ' << i;});

    return 0;
}
