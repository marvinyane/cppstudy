#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

int iArray[] = {1,2,3,4,5,6,7,8,9,10};
vector<int> iVec(iArray, iArray+10);

template<class T>
void display(string str, vector<T>& ivec)
{
    cout << str << endl;
    copy(ivec.begin(), ivec.end(), ostream_iterator<T>(cout, " "));
}

bool isOdd(int i)
{
    return i%2 == 1;
}
int main()
{
    display("before:", iVec);
    vector<int>::iterator iend = 
        remove_if(iVec.begin(), iVec.end(), isOdd);

    cout << "\nafter \n";
    copy(iVec.begin(), iend, ostream_iterator<int>(cout, " "));
}
