#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>
#include <string>

using namespace std;

template <class T>
class funcObj
{
    public:
        typedef T first_argument_type;
        typedef T second_argument_type;
        typedef bool result_type;
        funcObj()
        {
        }
        result_type operator()(const first_argument_type& a, const second_argument_type& b)const
        {
            if(a > b)
                return true;
            return false;
        }
    private:
        T ia;
};

template<class T>
class funcObj1
{
    public:
    bool operator()(const T& t)
    {
        if(t % 2 == 0)
        {
            return true;
        }
        return false;
    }
};

int main()
{
    int array[] = {1,2,3,4,5,6,7,8,9,10};
    vector<int> iVec(array, array+10);

    vector<int>::iterator ite = 
        find_if(iVec.begin(), iVec.end(), bind2nd(funcObj<int>(), 7));

    vector<int>::iterator ite1 = find_if(iVec.begin(), iVec.end(), funcObj1<int>());

    if(ite1 != iVec.end())
    {
        cout << *ite1 << endl;
    }

    return 0;
}
