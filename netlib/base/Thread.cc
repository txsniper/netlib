#include <pthread.h>
#include <netlib/base/Thread.h>
namespace netlib
{
namespace base
{
void defaultThreadFunc()
{

}

Thread::Thread(std::string name, ThreadFunc func)
        :threadFunc_(func),
        runBefore_(defaultThreadFunc),
        runAfter_(defaultThreadFunc),
        threadName_(name),
        started_(false),
        joined_(false)
{

}
bool Thread::start()
{
    int ret = pthread_create(&pthreadId_, NULL, beginThread, this);
    if (ret !=0)
    {
        return false;
    }
    started_ = true;
    return true;
}

void Thread::runInThread()
{
    threadFunc_();
}



void* Thread::beginThread(void* data)
{
    Thread* threadObj = static_cast<Thread*>(data);
    threadObj->runInThread();
    return NULL;
}

void Thread::join()
{
    pthread_join(pthreadId_, NULL);
    joined_ = true;
}
}
}
