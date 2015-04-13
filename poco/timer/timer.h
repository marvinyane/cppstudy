#ifndef __TIMER_H__
#define __TIMER_H__


class MirrorTimerRunnable;

class MirrorTimer : public Poco::Thread
{
    public:
        MirrorTimer();
        ~MirrorTimer();

        static void startTimer(MirrorThread &t, Func f, int timer);
        void startTimerProcess(MirrorThread &t, Func f, int timer);

    private:
        static MirrorTimer* instance;
        MirrorTimerRunnable *r;
};

#endif
