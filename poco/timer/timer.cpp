#include <list>
#include <iostream>

#include "thread.h"
#include "timer.h"

class MirrorTimerRunnable : public Poco::Runnable
{
    struct TimerNode
    {
        MirrorThread    *thread;
        Func            func;
        int             timer;
    };

    public:
    MirrorTimerRunnable():mutex()
    {
    }

    ~MirrorTimerRunnable()
    {
    }

    void startTimer(MirrorThread &t, Func f, int timer)
    {
        TimerNode* node = new TimerNode;
        node->thread = &t;
        node->func = f;
        node->timer = timer;

        std::cout << "the size of Timer Node : " << sizeof(TimerNode) << std::endl;

        mutex.lock();
        if (l.empty())
        {
            l.push_front(node);
        }
        else
        {
            std::list<MirrorTimerRunnable::TimerNode*>::iterator iter = l.begin();
            int t = timer - (*iter)->timer;
            if (t < 0)
            {
                l.insert(iter, node);
            }
            else
            {
                for (; iter != l.end(); iter++)
                {
                    if ((*iter)->timer > timer)
                    {
                        l.insert(iter, node);
                        break;
                    }
                }

                if (iter == l.end())
                {
                    l.insert(iter, node);
                }
            }
        }
        mutex.unlock();
    }

    void run()
    {
        while(1)
        {
            mutex.lock();
            if (!l.empty() && (--(l.front()->timer)) == 0)
            {
                while (!l.empty() && l.front()->timer == 0)
                {
                    MirrorTimerRunnable::TimerNode* node = l.front();
                    node->thread->postTask(node->func);
                    l.pop_front();
                    delete node;
                }
            }
            mutex.unlock();

            Poco::Thread::sleep(1);
        }
    }

    private:
    std::list<MirrorTimerRunnable::TimerNode*> l;
    Poco::Mutex mutex;

};

MirrorTimer::MirrorTimer()
{
    r = new MirrorTimerRunnable;
    start(*r);
}
MirrorTimer::~MirrorTimer()
{
    delete r;
}

void MirrorTimer::startTimer(MirrorThread &t, Func f, int timer)
{
    if (instance == NULL)
    {
        instance = new MirrorTimer;
    }

    instance->startTimerProcess(t, f, timer);
}

void MirrorTimer::startTimerProcess(MirrorThread &t, Func f, int timer)
{
    r->startTimer(t, f, timer);
}

MirrorTimer* MirrorTimer::instance = NULL;

void testFunc(int a)
{
    std::cout << "testFunc " << a << std::endl;
}
