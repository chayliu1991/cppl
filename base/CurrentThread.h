#pragma once

#include "Types.h"
namespace cppl
{
    namespace CurrentThread
    {
        extern __thread int t_cachedTid;
        extern __thread char t_tidString[32];
        extern __thread int t_tidStringLength;
        extern __thread const char *t_threadName;
        void cacheTid();

        inline int tid()
        {
            if (__builtin_expect(t_cachedTid == 0, 0))
            {
                cacheTid();
            }
            return t_cachedTid;
        }

        inline const char *tidString()
        {
            return t_tidString;
        }

        inline int tidStringLength()
        {
            return t_tidStringLength;
        }

        inline const char *name()
        {
            return t_threadName;
        }

        bool isMainThread();

        pid_t gettid();

        void sleepUsec(int64_t usec);

        std::string stackTrace(bool demangle = false);

    }
}