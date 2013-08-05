#include <iostream>
#include <string>
#include <complex>
#include <tuple>

using namespace std;

int main()
{
    tuple<string, int, int, complex<double>> t ;

    tuple<string , int , int> t1("hello11", 33, 44);

    cout << get<0>(t1) << endl;
    cout << get<1>(t1) << endl;
    cout << get<2>(t1) << endl;

    cout << "size of t1 = " << sizeof(t1) << endl;

    auto t2 = make_tuple( "world", 22, 55);

    get<1>(t1) = get<1>(t2);

    if(t1 < t2)
    {
        t1 = t2;
    }
    auto t3 = make_tuple("helllllllllll", "hellll",  3.14, 34, 'c'); 
    cout << "size of t3 = " << sizeof(t3) << endl;

    auto t4 = make_tuple(2.34);// tuple with string size is 4, with int is 4, with double is 8, why?
// because when a tuple store a string , it store a reference, when double, it's really the double
    
    auto t5 = make_tuple('c', 2); // the tuple should be assigned
    cout << "size of t5 = " << sizeof(t5) << endl;
}
