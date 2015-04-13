#include "Timestamp.h"
#include "Timer.h"
#include "Event.h"
#include "Mutex.h"
#include "WorkThread.h"
#include "callback.h"

#include <cstdio>
#include <cstdlib>
#include <sys/time.h>
#include <iostream>

struct timeval t_s, t_e;

unsigned int timerId = 0;
int count = 0;

class Test
{
    public:
        void func(int a)
        {
            gettimeofday(&t_e, NULL);
            int r = (t_e.tv_sec - t_s.tv_sec ) * 1000000 + (t_e.tv_usec - t_s.tv_usec);
            std::cout << "Test::func: " << r << std::endl;
            gettimeofday(&t_s, NULL);
            
            base::WorkThread* work1 = base::WorkThread::currentWorkThread();
            if (work1 && count++ > 10)
            {
                work1->stopTimer(timerId);
                std::cout << "Timer cancelled!\n";
            }
            else
            {
                std::cout << "work thread not found! \n";
            }
        }
};

int main()
{
    Test b;
    base::WorkThread w;

    base::Timestamp::TimeVal t = 3000;


    w.start();

    Closure task = Bind(&Test::func, b, 4);

    //w.postTask(task);

    gettimeofday(&t_s, NULL);

    timerId = w.addTimerTask(t, task, true);

    while (1)
    {
        sleep(10);
    }

    return 0;
}
