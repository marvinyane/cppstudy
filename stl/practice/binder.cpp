#include <iostream>
#include <list>
#include <functional>
#include <algorithm>
#include <iterator>

using namespace std;

int iarray[] = {1,2,3,4,5,6,7,8,9,10};

list<int> ilist(iarray, iarray+(sizeof(iarray)/sizeof(iarray[0])));

template<class T>
void display(list<T>& l)
{
    copy(l.begin(), l.end(), ostream_iterator<T>(cout, "\t"));
}

int main()
{
    int k = 0;
 //   display<int>(ilist);
    k =  count_if(ilist.begin(), ilist.end(), bind2nd(greater<int>(), 7));
    cout << "Number elements < 7 = " << k << endl;

    list<int>::iterator start = find_if(ilist.begin(), ilist.end(),
            not1(bind1st(greater<int>(), 7)));

    if(start != ilist.end())
    {
        cout << "start = " << *start << endl;
    }
    return 0;
}

