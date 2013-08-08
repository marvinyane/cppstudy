#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

const int LEN = 200000;

vector<int> getVec()
{
    vector<int> vec(LEN);
    for(int i = 0; i < LEN; i++)
    {
        vec[i] = i;
    }

    return vec;
}

int main()
{
#if 0
    clock_t t0 = clock();
    vector<vector<int> > vec;
    for(int i=0; i<1000; ++i)
    {
        vec.push_back(getVec());
    }

    cout << (clock() - t0) * 1.0 / CLOCKS_PER_SEC <<endl;
#endif
    vector<int>&& v1 = getVec();
    vector<int>&& v2 = getVec();
    cout << v1.size() <<" " << v2.size() << endl;
    return 0;
}
