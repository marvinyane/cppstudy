#include <vector>
#include <memory>
#include <utility>
#include <iostream>

int main()
{
    typedef std::unique_ptr<int[]> Buffer;

    Buffer b(new int[10]);

    for(int i = 0; i < 10; i++)
    {
        b[i] = i * 2;
    }

    std::vector<Buffer> list;
    list.push_back(std::move(b));

    Buffer c = std::move(list.front());
    list.pop_back();

    for (int i = 0; i < 10; i++)
    {
        std::cout << c[i] << "\n";
    }

    return 0;
}
