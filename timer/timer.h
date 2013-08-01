#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/microsec_time_clock.hpp>

class TestTimer
{
    public:
        TestTimer(const std::string& name);
        ~TestTimer();
    private:
        std::string name;
        boost::posix_time::ptime start;
};
