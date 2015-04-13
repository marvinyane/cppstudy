#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    int myinst[] = {1, 2, 3, 4, 5, 6, 7};

    std::vector<int> myvector(7);

    std::copy(myinst, myinst+7, myvector.begin());

    for(std::vector<int>::iterator it = myvector.begin(); it < myvector.end(); ++it)
    {
        std::cout << ' ' << *it;
    }

    std::cout << "\n";

    return 0;
}
