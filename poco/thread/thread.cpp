#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Event.h"

#include <iostream>
#include <queue>
#include <tr1/functional>

typedef std::tr1::function<void (void)> Func;

class MirrorRunnable : public Poco::Runnable
{
    public:
        MirrorRunnable():m_r(true)
        {
        }
        ~MirrorRunnable()
        {
        }

        void stop()
        {
            m_r = false;
            e.set();
        }

        void run()
        {
            while(1)
            {
                e.wait();

                if (!m_r)
                {
                    break;
                }

                while (!q.empty())
                {
                    Func f = q.front();
                    f();
                    q.pop();
                }
            }
        }

        void post(Func f)
        {
            q.push(f);
            e.set();
        }

    private:
        std::queue<Func> q;
        Poco::Event e;

        bool m_r;
};

class MirrorThread : public Poco::Thread
{
    public:
        MirrorThread():r()
        {
        }

        ~MirrorThread()
        {
        }

        void startOn()
        {
            start(r);
        }

        void stopOn()
        {
            r.stop();
            join();
        }

        void push(Func f)
        {
            this->sleep(10);
            r.post(f);
        }

    private:
        MirrorRunnable r;

};

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
            std::cout << "func1:" << i << b<< std::endl;
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
            std::cout << "size of Func1 : " << sizeof(f) << std::endl;
            t->push(f);
        }

        void func2(std::vector<int>& v)
        {
            Func f = std::tr1::bind(&MirrorImp::func2, *imp, v);

            std::cout << "size of Func2 : " << sizeof(f) << std::endl;
            t->push(f);
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

    Poco::Thread::sleep(1000);


    return 0;
}
