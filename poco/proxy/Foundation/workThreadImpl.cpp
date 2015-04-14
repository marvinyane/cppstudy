#include "callback.h"

#include "Timer.h"
#include "Event.h"

#include "task_runner.h"
#include "Timestamp.h"


#include "Poco/Thread.h"
#include "Poco/Runnable.h"

#include "WorkThread.h"

namespace base {

class TaskRunner : public Poco::Runnable {
    public:
        TaskRunner()
            :m_running(false) {}

        ~TaskRunner() {}

        unsigned int addTimerTask(base::Timestamp::TimeVal time, const Closure &task, bool repeat)
        {
            unsigned int r = m_timer.addTimerTask(time, task, repeat);
            m_waitEvent.set();
            return r;
        }

        bool stopTimer(unsigned int id)
        {
            bool r = m_timer.stop(id);
            m_waitEvent.set();
            return r;
        }

        void start()
        {
            m_running = true;
        }

        void stop()
        {
            m_runner.postStopTask();
            m_waitEvent.set();
        }

        void wait(long ms)
        {
            m_waitEvent.set();
            m_event.wait(ms);
        }

        void postTask(const Closure& task)
        {
            m_runner.postTask(task);
            m_waitEvent.set();
        }

        void run()
        {
            while (m_running) {
                if (!m_runner.runTask()) {
                    m_running = false;
                } else {
                    base::Timestamp::TimeVal val = m_timer.getMinWait();
                    if (0 > val) {
                        m_waitEvent.wait();
                    } else if (0 < val){
                        m_waitEvent.wait(val/1000);
                    } else {
                        m_waitEvent.wait(-1);
                    }
                    m_timer.doTimerTask();
                }
            }
            m_event.set();
        }

    private:

        base::task_runner m_runner;

        base::Event m_event;

        base::Event m_waitEvent;

        base::Timer m_timer;

        bool m_running;

};

std::map<void*, void*> WorkThread::m_thread;

WorkThread::WorkThread()
{
    m_run = new TaskRunner;
    proxy = new Poco::Thread;
        
    m_thread.insert(std::pair<void*, void*>((void*)proxy, (void*)this));
}

WorkThread::WorkThread(const std::string& name)
{
    
    m_run = new TaskRunner;
    proxy = new Poco::Thread(name);
        
    m_thread.insert(std::pair<void*, void*>((void*)proxy, (void*)this));
}

WorkThread::~WorkThread()
{
    m_run->stop();
    m_run->wait(1000);

    delete m_run;
        
    m_thread.erase((void*)proxy);
    
    delete proxy;
}

unsigned int WorkThread::addTimerTask(base::Timestamp::TimeVal time, const Closure &task, bool repeat)
{
    return m_run->addTimerTask(time, task, repeat);
}

bool WorkThread::stopTimer(unsigned int id)
{
    return m_run->stopTimer(id);
}

void WorkThread::start()
{
    m_run->start();

    proxy->start(*m_run);
}

void WorkThread::stop()
{
    m_run->stop();
}

void WorkThread::wait(long ms)
{
    m_run->wait(ms);
}

void WorkThread::postTask(const Closure& task)
{
    m_run->postTask(task);
}

WorkThread* WorkThread::currentWorkThread()
{
    void* proxy = static_cast<void*>(Poco::Thread::current());

    return static_cast<WorkThread*>(WorkThread::m_thread[proxy]);
}

} //namespace
