#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[] = {1, 2, 3, 4};
    int *b = a;
    int len = sizeof(a);

    std::vector<int> v = std::vector<int>(a, a+len/sizeof(int));
    
    std::cout << "v length is " << v.size() << "\n";

    std::vector<int>::iterator it = v.begin();
    for (; it != v.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    int *d = (int*)malloc(len);
    memcpy(d, &v[0], len);
    for(int i = 0; i < len / sizeof(int); i++)
    {
        std::cout << d[i] << " ";
    }
    std::cout << "\n";

    v.clear();
    v.erase(std::remove(v.begin(), v.end(), 6), v.end());
    for (it = v.begin(); it != v.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    return 0;
}
