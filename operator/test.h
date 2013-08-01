#include <iostream>

class testCase{

    public:
        testCase(int a, int b)
        {
            this->a = a;
            this->b = b;
        }
        ~testCase(){}

        friend std::ostream& operator << (std::ostream& s, const testCase& r);
        bool operator > (const testCase& r)const;
        
        int a;
        int b;
};

