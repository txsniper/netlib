#ifndef NETLIB_BASE_LOGSTREAM
#define NETLIB_BASE_LOGSTREAM
#include <string.h>
#include <string>
#include <netlib/base/noncopyable.h>
namespace netlib
{
namespace base
{

    const int SMALL_BUFFER_SIZE = 4000;
    const int LARGE_BUFFER_SIZE = 4000 * 1000;
    template <int SIZE>
    class FixedBuffer : netlib::base::noncopyable
    {
        public:
            FixedBuffer()
                : cur_(data_)
            {

            }

            // 如果写入的长度超过可写的长度，则部分写入，并返回新写入数据的长度
            size_t append(const char* buf, size_t len)
            {
                size_t availSpace = static_cast<size_t>(avail());
                size_t writeSize = 0;
                if (len > availSpace)
                {
                    writeSize = len - availSpace;
                }
                else if (len < availSpace)
                {
                    writeSize = availSpace - len;
                }

                if (writeSize != 0)
                {
                    memcpy(cur_, buf, writeSize);
                }
                cur_ += writeSize;
                return writeSize;
            }

            const char* data() const
            {
                return data_;
            }

            char* cur() const
            {
                return cur_;
            }

            size_t length() const
            {
                return static_cast<size_t> (cur_ - data_);
            }

            int avail() const
            {
                return static_cast<int>(end() - cur_);
            }

            void reset()
            {
                cur_ = data_;
            }

            void addLen(size_t len)
            {
                cur_ += len;
            }

            std::string toString() const
            {
                return std::string(data_, length());
            }

        private:
            const char* end() const
            {
                return data_ + sizeof(data_);
            }
            char data_[SIZE];
            char *cur_;
    };


    class LogStream : netlib::base::noncopyable
    {
        public:
        typedef FixedBuffer<SMALL_BUFFER_SIZE> Buffer;

        LogStream& operator<<(bool b)
        {
            buffer_.append(b ? "1" : "0", 1);
            return *this;
        }

        LogStream& operator<<(short);
        LogStream& operator<<(unsigned short);
        LogStream& operator<<(int);
        LogStream& operator<<(unsigned int);
        LogStream& operator<<(long);
        LogStream& operator<<(unsigned long);
        LogStream& operator<<(long long);
        LogStream& operator<<(unsigned long long);
        LogStream& operator<<(const void*);

        LogStream& operator<<(float v)
        {
            *this << static_cast<double>(v);
            return *this;
        }

        LogStream& operator<<(double);
        LogStream& operator<<(char c)
        {
            buffer_.append(&c, 1);
            return *this;
        }

        LogStream& operator<<(const char* str)
        {
            if(str)
            {
                buffer_.append(str, strlen(str));
            }
            return *this;
        }

        LogStream& operator<<(const unsigned char* str)
        {
            return operator<<(reinterpret_cast<const char*>(str));
        }

        LogStream& operator<<(const std::string& str)
        {
            buffer_.append(str.c_str(), str.size());
            return *this;
        }

        private:
            template <typename T>
            void formatInteger(T);
            Buffer buffer_;

            static const int MAX_NUMERIC_SIZE = 32;

    };
}
}

#endif
