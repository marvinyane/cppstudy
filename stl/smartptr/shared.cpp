#include <memory>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Base
{
    public:
        Base(string name):name(name)
        {
            cout << name << "create \n";
        }
        ~Base()
        {
            cout << name << "destroy \n";
        }
        void print()
        {
            cout << name << " ";
        }
    private:
        string name;
};

int main()
{
    shared_ptr<string> sp1(new string("marvin"));
    shared_ptr<string> sp2(new string("kobe"), 
            [](string* p){
                cout << "delete " << *p << endl; //lambda
            });
    sp1.reset(new string("tom"));

    (*sp1)[0] = 'T';

    vector<shared_ptr<string>> whoMadeCoffee;
    whoMadeCoffee.push_back(sp1);
    whoMadeCoffee.push_back(sp2);
 //   whoMadeCoffee.push_back(sp1);
 //   whoMadeCoffee.push_back(sp2);

    for(auto sp : whoMadeCoffee)
    {
        cout << *sp << " ";
    }

    cout << endl;

    cout << "use count " << whoMadeCoffee[0].use_count() << endl;

    *sp1 = "James";
    
    cout << "use count " << whoMadeCoffee[0].use_count() << endl;

    shared_ptr<int> sp3(new int[10], 
            [](int* p){delete[] p;});

    shared_ptr<int> sp4(new int[10],
            default_delete<int[]>());

    unique_ptr<int[]> up(new int[10]); // ok
    unique_ptr<int[], void(*)(int*)> p(new int[10],
            [](int*p){delete [] p;});
}
