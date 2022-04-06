#include "CurrentThread.h"
#include "Timestamp.h"

#include <errno.h>
#include <linux/unistd.h>
#include <stdio.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <type_traits>
#include <unistd.h>
namespace cppl
{
    namespace detail
    {
        pid_t gettid()
        {
            return static_cast<pid_t>(::syscall(SYS_gettid));
        }
    }
    namespace CurrentThread
    {
        __thread int t_cachedTid = 0;
        __thread char t_tidString[32];
        __thread int t_tidStringLength = 6;
        __thread const char *t_threadName = "unknown";
        static_assert(std::is_same<int, pid_t>::value, "pid_t should be int");

        void cacheTid()
        {
            if (t_cachedTid == 0)
            {
                t_cachedTid = detail::gettid();
                t_tidStringLength = snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid);
            }
        }

        bool isMainThread()
        {
            return tid() == ::getpid();
        }

        void sleepUsec(int64_t usec)
        {
            struct timespec ts = {0, 0};
            ts.tv_sec = static_cast<time_t>(usec / Timestamp::kMicroSecondsPerSecond);
            ts.tv_nsec = static_cast<long>(usec % Timestamp::kMicroSecondsPerSecond * 1000);
            ::nanosleep(&ts, NULL);
        }
    }
}
