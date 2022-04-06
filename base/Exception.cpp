#include "Exception.h"

#include "CurrentThread.h"
#include <string>
#include <utility>

namespace cppl
{
    Exception::Exception(const std::string &msg) : message_(std::move(msg)), stack_(CurrentThread::stackTrace(/*demangle=*/false))
    {
    }

} // namespace muduo
