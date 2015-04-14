#ifndef __BASE_WORKTHREAD_H_
#define __BASE_WORKTHREAD_H_

#include "callback.h"
#include "Timestamp.h"
#include <map>
#include <string>

namespace Poco
{
    class Thread;
}

namespace base {

class TaskRunner;

class WorkThread
{
    public:
        WorkThread();
        WorkThread(const std::string& name);

        ~WorkThread();

        unsigned int addTimerTask(Timestamp::TimeVal time, const Closure &task, bool repeat);

        bool stopTimer(unsigned int id);

        void start();

        void stop();

        void wait(long ms);

        void postTask(const Closure& task);

        static WorkThread *currentWorkThread();
        static std::map<void*, void*> m_thread;
        
    private:
        Poco::Thread* proxy;
        TaskRunner*   m_run;

};

}

#endif // WORKTHREAD_H
