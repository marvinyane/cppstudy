#ifndef __THREAD_H__
#define __THREAD_H__

#include "Poco/Thread.h"
#include <tr1/functional>

class MirrorRunnable;

typedef std::tr1::function<void (void)> Func;

class MirrorThread : public Poco::Thread
{
    public:
        MirrorThread();

        ~MirrorThread();

        void startOn();

        void stopOn();

        void postTask(Func f);

        void postTaskLater(Func f, int t);

    private:
        MirrorRunnable *r;

};



#endif
