#pragma once

#include "Condition.h"
#include "Mutex.h"
#include "Thread.h"
#include "Types.h"

#include <deque>
#include <vector>

namespace cppl
{
    class ThreadPool : NonCopyable
    {
    public:
        typedef std::function<void()> Task;

        explicit ThreadPool(const string &nameArg = string("ThreadPool"));
        ~ThreadPool();

        // Must be called before start().
        void setMaxQueueSize(int maxSize) { maxQueueSize_ = maxSize; }
        void setThreadInitCallback(const Task &cb)
        {
            threadInitCallback_ = cb;
        }

        void start(int numThreads);
        void stop();

        const string &name() const
        {
            return name_;
        }

        size_t queueSize() const;

        void run(Task f);

    private:
        bool isFull() const;
        void runInThread();
        Task take();

        mutable MutexLock mutex_;
        Condition notEmpty_;
        Condition notFull_;
        string name_;
        Task threadInitCallback_;
        std::vector<std::unique_ptr<cppl::Thread>> threads_;
        std::deque<Task> queue_;
        size_t maxQueueSize_;
        bool running_;
    };
}