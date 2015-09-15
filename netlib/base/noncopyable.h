#ifndef NETLIB_NONCOPYABLE
#define NETLIB_NONCOPYABLE

namespace netlib
{

namespace base
{

class noncopyable
{
    protected:
        noncopyable() {}
        ~noncopyable() {}

    private:
        noncopyable( const noncopyable& );
        const noncopyable& operator = (const noncopyable&);
};
}
}

#endif
