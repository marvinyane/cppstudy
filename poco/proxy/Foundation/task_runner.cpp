#include "task_runner.h"

namespace base {

task_runner::task_runner():
    m_stop(false)
{
}

void task_runner::postTask(const Closure& task)
{
    m_mutex.lock();
    m_tasks.push(task);
    m_mutex.unlock();
}

void task_runner::postStopTask()
{
    m_mutex.lock();
    m_tasks.push(Bind(&task_runner::stopRunner, this));
    m_mutex.unlock();
}

bool task_runner::runTask()
{
    while (!checkEmpty()) {
        m_mutex.lock();
        Closure task = m_tasks.front();
        m_tasks.pop();
        m_mutex.unlock();
        //task.Run();
        task();
        if (m_stop) {
            m_mutex.lock();
            while (!m_tasks.empty()) {
                m_tasks.pop();
            }
            m_mutex.unlock();
            return m_stop = false;
        }
    }
    return true;
}

bool task_runner::checkEmpty()
{
    m_mutex.lock();
    bool ret = m_tasks.empty();
    m_mutex.unlock();
    return ret;
}

void task_runner::stopRunner()
{
    m_stop = true;
}

}
