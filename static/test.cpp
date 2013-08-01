#include <iostream>
using namespace std;

class Month{
    public:
        static Month Jan(){
            return Month(1);
        }
        static Month Feb(){
            return Month(2);
        }
    private:
        explicit Month(int m)
        {
            cout << m << endl;
        }
};

int main()
{
    Month m = Month::Jan();
}
