#include <queue>

#include "Poco/Runnable.h"

#include "thread.h"

#include "Poco/Event.h"
#include "timer.h"

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

MirrorThread::MirrorThread()
{
    r = new MirrorRunnable();
}

MirrorThread::~MirrorThread()
{
    delete r;
}

void MirrorThread::startOn()
{
    start(*r);
}

void MirrorThread::stopOn()
{
    r->stop();
    join();
}

void MirrorThread::postTask(Func f)
{
    r->post(f);
}

void MirrorThread::postTaskLater(Func f,int t)
{
    MirrorTimer::startTimer(*this, f, t);
}
