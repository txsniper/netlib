#ifndef NETLIB_BASE_THREADINFO
#define NETLIB_BASE_THREADINFO


namespace netlib
{

namespace base
{

namespace ThreadInfo
{
    extern __thread int cacheTid;
    extern __thread char tidStr[32];
    pid_t gettid();
    pid_t tid();
    bool isMainThread();
}
}
}
#endif
