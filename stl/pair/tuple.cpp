#include <iostream>
#include <string>
#include <complex>
#include <tuple>
#include <memory>

using namespace std;
void testTupleSize()
{
    tuple<string, int, int, complex<double>> t ;

    get<0>(t) = "hello";

    cout << get<0>(t) << endl;

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

void testTupleCon()
{
    class Base
    {
        public:
            Base()
            {
                cout << "create \n";
            }
            ~Base()
            {
                cout << "destroy \n";
            }
    };
  //  shared_ptr<Base> spb(new Base);
 //  Base* spb = new Base;
    Base b;

    auto t = make_tuple(ref(b));    // if here is not reference, the ~Base may be call twice
}

template <typename... Args>
void foo(const tuple<Args...> t)
{
    cout << sizeof...(Args) << endl;
}

int main()
{
    //testTupleSize();
   // testTupleCon();
   auto t = make_tuple(43, "he");
   foo(t);
}
