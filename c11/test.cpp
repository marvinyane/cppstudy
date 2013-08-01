#include <iostream>
#include <vector>

using namespace std;

class Base{
    public:
        Base (int a, int b)
        {
            cout << "first" << endl;
            cout << a << b << endl;
        }
#if 0
        Base(initializer_list<int> l )
        {
            cout << "second" << endl;
            auto s = l.begin();
            for(; s < l.end(); s++)
            {
                cout << *s << endl;
            }
        }
#endif
        explicit Base(int a, int b, int c)
        {
            cout << "third" << endl;


        }
};

template <typename T>
void printElements(const T& coll)
{
    for(const auto & ele : coll){
        cout << ele << endl;
    }
}

int main()
{
 //   Base a(1,2);
 //   Base b{1,2};
 //   Base c{1,2,3};

 //   Base e = {1,2,3};
 //   
    vector<double> vec;
    vec.push_back(3.14);
    vec.push_back(3.15);

    printElements<vector<double>>(vec);
}
