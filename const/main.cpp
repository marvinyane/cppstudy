#include <iostream>


struct B
{
        void setName(int t) const
        {
            *b = t;
        }
    //private:
        int* b;
};



int main()
{
    const B* b = new B;
    //B * const b = new B;

    //b->setName(3);
    //
    *(b->b) = 3;

    return 0;
}
