#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

template<class RandomAccessIte>
void getDiff(RandomAccessIte first, RandomAccessIte second)
{
    //typename RandomAccessIte::difference_type i, n;
 //   typename iterator_traits<RandomAccessIte>::difference_type i;

//    decltype(i) n = second - first;
    auto n = second - first;
    auto i = n - 1;

    for(i = n-1; i >= 0; i--)
    {
        cout << first[i] << endl;
    }
}


int main()
{
    int array[] ={1,2,3,4,5,6,7,8,9};
    vector<int> ivec(array, array + sizeof(array)/sizeof(array[0]));

    getDiff<vector<int>::iterator>(ivec.begin(), ivec.end());
}
