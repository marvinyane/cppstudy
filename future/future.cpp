#include <iostream>
#include <future>

bool is_prime(int x)
{
    for(int i = 2; i < x; ++i)
        if (x % i ==0)
            return false;

    return true;
}

int main()
{
    std::future<bool> fut = std::async(is_prime, 313222313);

    std::cout << "checking whether 313222313 is prime.\n";
    bool ret = fut.get();
    std::cout << "over!!\n";

    if (ret)
        std::cout << "Yes!\n";
    else
        std::cout << "No!\n";

    return 0;
}
