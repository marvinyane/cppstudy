#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v;
    for (int i = 0; i < 100; i++)
    {
        v.push_back(i);
    }

    std::cout << "v capibility is : " << v.capacity() << "\n";

    for (int i = 0; i < 50; i++)
    {
        v.erase(v.begin() + i);
    }
    
    std::cout << "v capibility is : " << v.capacity() << "\n";

    std::vector<int>(v).swap(v);
    
    std::cout << "v capibility is : " << v.capacity() << "\n";

    return 0;
}
