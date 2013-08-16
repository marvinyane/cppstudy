#include <iostream>
#include <iterator>
#include <functional>
#include <algorithm>
#include <vector>

using namespace std;

class myClass
{
    void operator() (int i)
    {
        cout << i << " ";
    }
};

void myFunc(int i)
{
    cout << " " << i;
}

int iArray[] = {1,2,3,4,5,6,7,8,9,10};
int main()
{
    vector<int> vec(iArray, iArray+sizeof(iArray)/sizeof(int));
    cout << "sizeof vec = " << vec.size() <<" " <<sizeof(vec) << endl;

    vector<int>::iterator l = find(vec.begin(), vec.end(), 5);
    if(l != vec.end())
    {
        cout << *l << endl;
    }

    copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(vec));

    cout << "sizeof vec : " << vec.size() << endl;

    //for_each(vec.begin(), vec.end(), myClass);
    for_each(vec.begin(), vec.end(), myFunc);

}
