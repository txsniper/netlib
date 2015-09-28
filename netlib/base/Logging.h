#ifndef NETLIB_BASE_LOGGING
#define NETLIB_BASE_LOGGING
#include <netlib/base/LogStream.h>
#include <netlib/base/TimeStamp.h>
#include <string>
namespace netlib
{

class Logger
{
    public:
        enum LogLevel
        {
            TRACE,
            DEBUG,
            INFO,
            WARN,
            ERROR,
            FATAL,
            NUM_LOG_LEVELS,
        };
        Logger(const std::string& fileName, int line);
        Logger(const std::string& fileName, int line, LogLevel level);
        Logger(const std::string& fileName, int line, LogLevel level, const char* func);
        ~Logger();

        LogStream& stream()
        {
            return stream_;
        }

        static LogLevel logLevel();
        static void setLogLevel(LogLevel level);

        typedef void (*OutputFunc)(const char* mgs, int len);
        typedef void (*FlushFunc)();
        static void setFlush(FlushFunc);
        static void setOutput(OutputFunc);
    private:
        class Impl
        {
            typedef Logger::LogLevel LogLevel;
            Impl(LogLevel level, int old_errno, const std::string& fileName, int line);
            void formatTime();
            void finish();

            TimeStamp time_;
            LogStream stream_;
            LogLevel level_;
            int line_;
            std::string baseName_;
        };

        Impl impl_;
};

extern Logger::LogLevel g_logLevel;

inline Logger::LogLevel Logger::logLevel()
{
    return g_logLevel;
}

#define LOG_TRACE if(netlib::Logger::logLevel() <= netlib::Logger::TRACE) \
    netlib::Logger(__FILE__, __LINE__, netlib::Logger::TRACE, __func__).stream()
#define LOG_DEBUG if(netlib::Logger::logLevel() <= netlib::Logger::DEBUG) \
    netlib::Logger(__FILE__, __LINE__, netlib::Logger::DEBUG, __func__).stream()
#define LOG_INFO if (netlib::Logger::logLevel() <= netlib::Logger::INFO) \
    netlib::Logger(__FILE__, __LINE__, netlib::Logger::INFO).stream()
#define LOG_WARN netlib::Logger(__FILE__, __LINE__, netlib::Logger::WARN).stream()
#define LOG_ERROR netlib::Logger(__FILE__, __LINE__, netlib::Logger::ERROR).stream()
#define LOG_FATAL netlib::Logger(__FILE__, __LINE__, netlib::Logger::FATAL).stream()
}
#endif
