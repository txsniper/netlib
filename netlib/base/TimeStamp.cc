#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <inttypes.h>
#include <netlib/base/TimeStamp.h>
namespace netlib
{
namespace base
{
    TimeStamp TimeStamp::now()
    {
        struct timeval tm;
        gettimeofday(&tm, NULL);
        int64_t microSecs = tm.tv_sec * TimeStamp::MICRO_SECONDS_PER_SECOND + tm.tv_usec;
        return TimeStamp(microSecs);
    }

    std::string TimeStamp::toString() const
    {
        char buf[32] = {0};
        int64_t seconds = microSecondsUTC_ / MICRO_SECONDS_PER_SECOND;
        int64_t microSecs = microSecondsUTC_ % MICRO_SECONDS_PER_SECOND;
        snprintf(buf, 32, "%" PRId64 ".%06" PRId64 "", seconds, microSecs);
        return buf;
    }

    std::string TimeStamp::toDateString() const
    {
        char buf[32] = {0};
        time_t seconds = static_cast<time_t> (microSecondsUTC_ / MICRO_SECONDS_PER_SECOND);
        struct tm tmParam;
        gmtime_r(&seconds, &tmParam);
        snprintf(buf, 32, "%4d%02d%02d %02d:%02d:%02d", tmParam.tm_year + 1900,
                tmParam.tm_mon, tmParam.tm_mday, tmParam.tm_hour, tmParam.tm_min, tmParam.tm_sec);
        return buf;
    }
}
}
