#pragma once

#include "Condition.h"
#include "Mutex.h"

namespace cppl
{
    class CountDownLatch : NonCopyable
    {
    public:
        explicit CountDownLatch(int count);

        void wait();

        void countDown();

        int getCount() const;

    private:
        mutable MutexLock mutex_;
        Condition condition_;
        int count_;
    };
}