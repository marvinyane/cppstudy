#include <iostream>
#include <functional>

class Role
{
    public:
        int compure(int a, int b);
};

int Role::compure(int a, int b)
{
    return a + b;
}

int main()
{
    Role role;

    auto fn = std::bind(&Role::compure, &role, std::placeholders::_1, std::placeholders::_2);

    std::cout << fn(4, 6) << std::endl;

    return 0;
}
