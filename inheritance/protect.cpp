#include <iostream>

class Base
{
    protected:
        int a;
        int b;
    private:
        int c;
    public:
        int d;

        explicit Base(int a, int b, int c, int d)
            : a(a), b(b), c(c), d(d)
        {

        }

        virtual ~Base()
        {

        }

        void setD(int a);
        int getD();
        //void setProtected(int a);
        void Display();
};

void Base::setD(int a)
{
    this->d = a;
}

int Base::getD()
{
    return this->d;
}

void Base::Display()
{
    std::cout << "a : " << a << ",b : " << b << ",c : " << c << ",d : " << d << std::endl;
}

class Derived : public Base
{
    public:
        explicit Derived() : Base(1, 2, 3, 4)
        {
        }

        void setProtected(int a);

        ~Derived()
        {

        }
};

void Derived::setProtected(int a)
{
    this->a = a;
}

int main()
{
    Derived *d = new Derived;
    d->Display();

    d->setD(5);

    d->Display();

    return 0;
}
