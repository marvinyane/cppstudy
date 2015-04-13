#include <iostream>

#include "thread.h"

#include <sys/time.h>
#include <unistd.h>

struct timeval start;
struct timeval stop;


class MirrorImp
{
    public:
        MirrorImp()
        {
        }
        ~MirrorImp()
        {
        }

        void func1(int i, int b)
        {
            gettimeofday(&stop, NULL);
            std::cout << "func1:" << i << b<< std::endl;

            long s = stop.tv_sec - start.tv_sec;
            long us = stop.tv_usec - start.tv_usec;

            long r = s * 1000000 + us;

            std::cout << r << "us.\n";
        }

        void func2(std::vector<int> v)
        {
            std::cout << "func2:" << std::endl;

            std::vector<int>::iterator iter = v.begin();

            for (; iter != v.end(); iter++)
            {
                std::cout << *iter << std::endl;
            }
        }

};


class MirrorProxy
{
    public:
        MirrorProxy():
            imp(new MirrorImp),
            t(new MirrorThread)
        {
            t->startOn();
        }
        ~MirrorProxy()
        {
            t->stopOn();
            delete t;
            delete imp;
        }

        void fun1(int i)
        {
            Func f = std::tr1::bind(&MirrorImp::func1, *imp, i, 4);
            //t->postTask(f);
            t->postTaskLater(f, 5000);

            gettimeofday(&start, NULL);
        }

        void func2(std::vector<int>& v)
        {
            Func f = std::tr1::bind(&MirrorImp::func2, *imp, v);

            t->postTask(f);
        }

    private:
        MirrorThread *t;
        MirrorImp *imp;
};


int main()
{
    MirrorProxy p;
    p.fun1(5);

    std::vector<int> v;

    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    p.func2(v);

    v[3] = 11;

    Poco::Thread::sleep(10000);

    return 0;
}
