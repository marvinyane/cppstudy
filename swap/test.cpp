#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Base{
    public:
        Base(int a):
            a(a)
        {

        }
        Base(const Base& t)
        {
            cout << "create Base by constru..." << endl;
        }

        Base& operator=(const Base& t)
        {
            cout << "create Base by copy,,," << endl;
        }

        void show()
        {
            cout << "number = " << this->a << endl;
        }

        void swap(Base& other)
        {
            using std::swap;
            swap(a, other.a);
        }
    private:
        int a;
};
// std::swap 特化版本， 如果需要置换Base， 调用其swap成员函数.
namespace std {
    template<>
    void swap<Base>(Base& a, Base& b)
    {
        a.swap(b);
    }
}

int main()
{
#if 0
    int a = 3;
    int b = 4;

    swap<int>(a, b);

    cout << a << " " << b << endl;


    vector<int> vec;
    vec.push_back(a);
    vec.push_back(b);

    swap<int>(vec[0], vec[1]);

    cout << vec[0] << " " << vec[1] << endl;

    string sa("hello");
    string sb("world");

    swap<string>(sa,sb);

    cout << sa << " " << sb << endl;
#endif


    Base ca(2);
    Base cb(3);

    swap<Base>(ca, cb);

    ca.show();
    cb.show();
}
