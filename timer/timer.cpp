#include "timer.h"

    TestTimer::TestTimer(const std::string & name) : name(name),
        start(boost::date_time::microsec_clock<boost::posix_time::ptime>::local_time())
    {

    }


    TestTimer:: ~TestTimer()
    {

        using namespace std;
        using namespace boost;

        posix_time::ptime now(date_time::microsec_clock<posix_time::ptime>::local_time());
        posix_time::time_duration d = now - start;

        cout << name << " completed in " << d.total_milliseconds() <<
            " milseconds" << endl;
    }
