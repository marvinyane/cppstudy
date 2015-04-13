#include "Timestamp.h"
#include "Poco/Timestamp.h"

namespace base
{
    Timestamp::Timestamp()
    {
        proxy = new Poco::Timestamp;
    }

    Timestamp::Timestamp(TimeVal tv)
    {
        proxy = new Poco::Timestamp(tv);
    }

    Timestamp::Timestamp(const Timestamp& other)
    {
        proxy = new Poco::Timestamp(*other.proxy);
    }

    Timestamp::~Timestamp()
    {
        delete proxy;
    }

Timestamp& Timestamp::operator = (const Timestamp& other)
{
    proxy->operator=(*other.proxy);
    return *this;
}
Timestamp& Timestamp::operator = (TimeVal tv)
{
    proxy->operator=(tv);
    return *this;
}

void Timestamp::swap(Timestamp& timestamp)
{
    proxy->swap(*timestamp.proxy);
}

void Timestamp::update()
{
    proxy->update();
}

bool Timestamp::operator == (const Timestamp& ts) const
{
    return proxy->operator==(*ts.proxy);
}
bool Timestamp::operator != (const Timestamp& ts) const
{
    return proxy->operator!=(*ts.proxy);
}
bool Timestamp::operator >  (const Timestamp& ts) const
{
    return proxy->operator>(*ts.proxy);
}
bool Timestamp::operator >= (const Timestamp& ts) const
{
    return proxy->operator>=(*ts.proxy);
}
bool Timestamp::operator <  (const Timestamp& ts) const
{
    return proxy->operator<(*ts.proxy);
}
bool Timestamp::operator <= (const Timestamp& ts) const
{
    return proxy->operator<=(*ts.proxy);
}

Timestamp  Timestamp::operator +  (TimeDiff d) const
{
    Timestamp s(*this);
    s.proxy->operator+=(d);
    return s;
}
Timestamp  Timestamp::operator -  (TimeDiff d) const
{
    Timestamp s(*this);
    s.proxy->operator-=(d);
    return s;
}
Timestamp::TimeDiff Timestamp::operator -  (const Timestamp& ts) const
{
    return proxy->operator-(*ts.proxy);
}
Timestamp& Timestamp::operator += (TimeDiff d)
{
    proxy->operator+=(d);
    return *this;
}
Timestamp& Timestamp::operator -= (TimeDiff d)
{
    proxy->operator-=(d);
    return *this;
}

std::time_t Timestamp::epochTime() const
{
    return proxy->epochTime();
}

Timestamp::UtcTimeVal Timestamp::utcTime() const
{
    return proxy->utcTime();
}

Timestamp::TimeVal Timestamp::epochMicroseconds() const
{
    return proxy->epochMicroseconds();
}

Timestamp::TimeDiff Timestamp::elapsed() const
{
    return proxy->elapsed();
}

bool Timestamp::isElapsed(TimeDiff interval) const
{
    return proxy->isElapsed(interval);
}

Timestamp Timestamp::fromEpochTime(std::time_t t)
{
    return Timestamp(TimeVal(t) * resolution());
}
Timestamp Timestamp::fromUtcTime(UtcTimeVal val)
{
    val -= (TimeDiff(0x01b21dd2) << 32) + 0x13814000;
	val /= 10;
	return Timestamp(val);
}

Timestamp::TimeVal Timestamp::resolution()
{
    return Poco::Timestamp::resolution();
}

}
