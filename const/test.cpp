#include <iostream>
#include <string>

using namespace std;

class test{
    public:
        test(string str)
        {
            this->value = str;
        }
        const char& operator[](size_t position) const;
        char& operator[](size_t position);
    private:
        string value;
};


const char& test::operator[](size_t position) const
{
    return this->value[position];
}

char& test::operator[](size_t position)
{
    return const_cast<char&>(
            static_cast<const test&>(*this)
            [position]
           );
}


int main()
{
    const test t0("world");
    test t1("hello");

    t1[0] = 'H';

    cout << t1[0] << endl;

    return 0;
}
