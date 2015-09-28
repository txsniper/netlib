#include <netlib/base/Logging.h>
#include <stdio.h>
#include <string.h>
namespace netlib
{
void defaultOutput(const char *msg, int len)
{
    size_t n = fwrite(msg, 1, len, stdout);
    (void)n;
}

void defaultFlush()
{
    fflush(stdout);
}

Logger::OutputFunc g_output = defaultOutput;
Logger::FlushFunc g_flush = defaultFlush;

Logger::Impl::Impl(LogLevel level, int savedErrno, const std::string& fileName, int line)
    : time_t(TimeStamp::now()),
      stream_(),
      level_(level),
      line_(line),
      baseName_(fileName)
{

}
}
