#ifndef NETLIB_BASE_TIMESTAMP
#define NETLIB_BASE_TIMESTAMP

#include <stdint.h>
#include <string>
namespace netlib
{
namespace base
{

    class TimeStamp
    {
        public:
            static const int MICRO_SECONDS_PER_SECOND = 1000 * 1000;
            TimeStamp()
                : microSecondsUTC_(0)
            {

            }

            TimeStamp(int64_t microSecondsUTC)
                : microSecondsUTC_(microSecondsUTC)
            {

            }

            TimeStamp(const TimeStamp& timeStamp)
            {
                microSecondsUTC_ = timeStamp.microSecondsUTC_;
            }

            TimeStamp& operator = (const TimeStamp& timeStamp)
            {
                if (&timeStamp != this)
                {
                    microSecondsUTC_ = timeStamp.microSecondsUTC_;
                }
                return *this;
            }

            void addTime(const TimeStamp& timeStamp)
            {
                microSecondsUTC_ += timeStamp.microSecondsUTC_;
            }

            void addTime(int seconds)
            {
                microSecondsUTC_ += seconds * MICRO_SECONDS_PER_SECOND;
            }

            bool isValid() const
            {
                return microSecondsUTC_ > 0;
            }

            int64_t microSeconds() const
            {
                return microSecondsUTC_;
            }


            static TimeStamp now();

            std::string toString() const;

            std::string toDateString() const;
        private:
            int64_t microSecondsUTC_;
    };

    bool operator < (TimeStamp lhs, TimeStamp rhs)
    {
        return lhs.microSeconds() < rhs.microSeconds();
    }

    bool operator == (TimeStamp lhs, TimeStamp rhs)
    {
        return lhs.microSeconds() == rhs.microSeconds();
    }
}
}
#endif
