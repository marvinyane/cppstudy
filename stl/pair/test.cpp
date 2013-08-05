#include <iostream>
#include <tuple>
#include <utility> //what's this?

using namespace std;


pair<int, int> getPair()
{
    pair<int, int> p(2,3);

    return p;
}

template<typename T1, typename T2>
void printResult(pair<T1,T2>& p)
{
    cout << get<0>(p) << endl;
    cout << get<1>(p) << endl;
}

int main()
{
    pair<int, int> p = getPair();

    cout << p.first << " ... " << p.second << endl;

    printResult<tuple_element<0, pair<int, int>>::type, tuple_element<1, pair<int, int>>::type>(p);

    cout << tuple_size<pair<int, int>>::value << endl;

    tuple_element<0, pair<int, int>>::type tp = get<0>(p);

    cout << tp << endl;
}

