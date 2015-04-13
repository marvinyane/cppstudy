#ifndef __BASE_TIMESTAMP_H__
#define __BASE_TIMESTAMP_H__

#include <ctime>

namespace Poco
{
    class Timestamp;
}

namespace base
{
    class Timestamp
    {
        public:
            typedef signed long long TimeVal;
            typedef signed long long UtcTimeVal;
            typedef signed long long TimeDiff;

            Timestamp();
            /// Creates a timestamp with the current time.

            Timestamp(TimeVal tv);
            /// Creates a timestamp from the given time value.

            Timestamp(const Timestamp& other);
            /// Copy constructor.

            ~Timestamp();
            /// Destroys the timestamp

            Timestamp& operator = (const Timestamp& other);
            Timestamp& operator = (TimeVal tv);

            void swap(Timestamp& timestamp);
            /// Swaps the Timestamp with another one.

            void update();
            /// Updates the Timestamp with the current time.

            bool operator == (const Timestamp& ts) const;
            bool operator != (const Timestamp& ts) const;
            bool operator >  (const Timestamp& ts) const;
            bool operator >= (const Timestamp& ts) const;
            bool operator <  (const Timestamp& ts) const;
            bool operator <= (const Timestamp& ts) const;

            Timestamp  operator +  (TimeDiff d) const;
            Timestamp  operator -  (TimeDiff d) const;
            TimeDiff   operator -  (const Timestamp& ts) const;
            Timestamp& operator += (TimeDiff d);
            Timestamp& operator -= (TimeDiff d);

            std::time_t epochTime() const;
            /// Returns the timestamp expressed in time_t.
            /// time_t base time is midnight, January 1, 1970.
            /// Resolution is one second.

            UtcTimeVal utcTime() const;
            /// Returns the timestamp expressed in UTC-based
            /// time. UTC base time is midnight, October 15, 1582.
            /// Resolution is 100 nanoseconds.

            TimeVal epochMicroseconds() const;
            /// Returns the timestamp expressed in microseconds
            /// since the Unix epoch, midnight, January 1, 1970.

            TimeDiff elapsed() const;
            /// Returns the time elapsed since the time denoted by
            /// the timestamp. Equivalent to Timestamp() - *this.

            bool isElapsed(TimeDiff interval) const;
            /// Returns true iff the given interval has passed
            /// since the time denoted by the timestamp.

            static Timestamp fromEpochTime(std::time_t t);
            /// Creates a timestamp from a std::time_t.

            static Timestamp fromUtcTime(UtcTimeVal val);
            /// Creates a timestamp from a UTC time value.

            static TimeVal resolution();
            /// Returns the resolution in units per second.
            /// Since the timestamp has microsecond resolution,
            /// the returned value is always 1000000.

        private:
            Poco::Timestamp *proxy;
    };
}

#endif
