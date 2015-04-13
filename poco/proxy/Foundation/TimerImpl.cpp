#include "Timer.h"

namespace base {

Timer::Timer()
{
    m_curId = 0;
}

Timestamp::TimeVal Timer::getMinWait()
{
    m_mutex.lock();
    if (!m_timerList.empty()) {
        std::map<unsigned int, TimerCtrl *>::iterator it, min;
        it = m_timerList.begin();
        for (min = it; it != m_timerList.end(); it++) {
            if (min->second->stamp.epochMicroseconds() > it->second->stamp.epochMicroseconds()) {
                min = it;
            }
        }
        Timestamp::TimeVal t = min->second->stamp.epochMicroseconds();
        m_mutex.unlock();
        t -= Timestamp().epochMicroseconds();
        if (t > 0) {
            return t;
        } else {
            return 0;
        }
    } else {
        m_mutex.unlock();
        return -1;
    }
}

bool Timer::stop(unsigned int id)
{
    m_mutex.lock();
    if (m_timerList.end() != m_timerList.find(id)) {
        delete m_timerList[id];
        m_timerList.erase(id);
        m_mutex.unlock();
        return true;
    } else {
        m_mutex.unlock();
        return false;
    }
}

unsigned int Timer::addTimerTask(Timestamp::TimeVal time, const Closure &task, bool repeat)
{
    Timestamp cur;
    cur += time * 1000;
    m_mutex.lock();
    TimerCtrl *ctrl = new TimerCtrl;
    ctrl->repeat = repeat;
    ctrl->stamp = cur;
    ctrl->task = task;
    ctrl->time = time * 1000;
    m_timerList.insert(std::make_pair<unsigned int, TimerCtrl *>(m_curId, ctrl));
    m_mutex.unlock();
    return m_curId++;
}

void Timer::doTimerTask()
{
    std::map<unsigned int, TimerCtrl *>::iterator it, min;
    while (true) {
        m_mutex.lock();
        min = m_timerList.begin();
        for (it = m_timerList.begin(); it != m_timerList.end(); it++) {
            if (min->second->stamp.epochMicroseconds() > it->second->stamp.epochMicroseconds()) {
                min = it;
            }
        }
        if (min != m_timerList.end()) {
            Timestamp tmp = min->second->stamp;
            Closure task = min->second->task;
            bool repeat = min->second->repeat;
            Timestamp stamp;
            if (tmp - stamp < 1000) {
                if (!repeat) {
                    m_timerList.erase(min);
                } else {
                    Timestamp cur;
                    min->second->stamp = cur + min->second->time;
                }
                m_mutex.unlock();
                //task.Run();
                task();
            } else {
                m_mutex.unlock();
                break;
            }
        } else {
            m_mutex.unlock();
            break;
        }
    }
}

}
