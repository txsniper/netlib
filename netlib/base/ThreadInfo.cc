#include <sys/syscall.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <netlib/base/ThreadInfo.h>

namespace netlib
{
namespace base
{

namespace ThreadInfo
{
    __thread int  cacheTid = 0;
    __thread char tidStr[32];
    pid_t gettid()
    {
        return static_cast<pid_t>(::syscall(SYS_gettid));
    }

    pid_t tid()
    {
        if(cacheTid == 0)
        {
            cacheTid = gettid();
            snprintf(tidStr, sizeof(tidStr), "%5d ", cacheTid);
        }
        return cacheTid;
    }

    bool isMainThread()
    {
        return tid() == ::getpid();
    }
}
}
}
