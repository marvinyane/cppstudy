#ifndef TASK_RUNNER_H
#define TASK_RUNNER_H

#include <queue>

#include "Mutex.h"
#include "callback.h"

namespace base {

class task_runner
{

public:

    task_runner();

    void postTask(const Closure& task);

    void postStopTask();

    bool runTask();

private:

    bool checkEmpty();

    void stopRunner();

    bool m_stop;

    std::queue<Closure> m_tasks;

    Mutex m_mutex;

};

}

#endif // TASK_RUNNER_H
