#ifndef NETLIB_BASE_SINGLETON
#define NETLIB_BASE_SINGLETON

#include <pthread.h>
#include <stdlib.h>
#include <netlib/base/noncopyable.h>
namespace netlib
{
namespace base
{

    template  <typename T>
    class SingletonT : netlib::base::noncopyable
    {
        public:

            static T* getInstance()
            {
                pthread_once(&ponce_, Init);
                return instance_;
            }
        private:
            static void Init()
            {
                instance_ = new T();
                ::atexit(UnInit);
            }
            static void UnInit()
            {
                if(instance_)
                {
                    delete instance_;
                }
            }
            SingletonT();
        private:
            static pthread_once_t ponce_;
            static T* instance_;
    };

    template <typename T>
    pthread_once_t SingletonT<T>::ponce_ = PTHREAD_ONCE_INIT;

    template <typename T>
    T* SingletonT<T>::instance_ = NULL;

}
}
#endif
