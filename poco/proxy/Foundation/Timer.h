#ifndef TIMER_H
#define TIMER_H

#include <map>
#include "callback.h"
#include "Timestamp.h"
#include "Mutex.h"

namespace base {

class Timer
{
public:
    Timer();
    Timestamp::TimeVal getMinWait();
    bool stop(unsigned int id);
    unsigned int addTimerTask(Timestamp::TimeVal time, const Closure &task, bool repeat);
    void doTimerTask();
private:
    struct TimerCtrl {
        Timestamp stamp;
        Timestamp::TimeVal time;
        bool repeat;
        Closure task;
    };
    Mutex m_mutex;
    std::map< unsigned int, TimerCtrl *> m_timerList;
    unsigned int m_curId;
};
}

#endif // TIMER_H
