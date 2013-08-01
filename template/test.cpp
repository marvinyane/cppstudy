#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename C>
void print2nd(const C& container)
{
    if(container.size() > 2)
    {
        typename
            C::const_iterator iter(container.begin());
        ++iter;
        int value = *iter;
        cout << value;
    }
}


int main()
{
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    print2nd<vector<int> >(vec);
}

