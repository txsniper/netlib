#include <sys/time.h>
#include <errno.h>
#include <netlib/base/Condition.h>
namespace netlib
{

namespace base
{

bool Condition::waitForSecs(unsigned int nSecs)
{
    struct timespec timeNow;
    int ret = clock_gettime(CLOCK_MONOTONIC, &timeNow);
    timeNow.tv_sec += nSecs;
    ret = pthread_cond_timedwait(&cond_, mutex_.getRawMutex(), &timeNow);
    if (ret == ETIMEDOUT) {
        return false;
    }
    return true;
}
}

}
