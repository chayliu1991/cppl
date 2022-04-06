#pragma once

#include "Condition.h"
#include "Mutex.h"

#include <assert.h>
#include <deque>

namespace cppl
{
    template <typename T>
    class BoundedBlockingQueue : NonCopyable
    {
    public:
        explicit BoundedBlockingQueue(size_t maxSize) : size_(maxSize), mutex_(), notEmpty_(mutex_), notFull_(mutex_)
        {
        }

        void put(const T &x)
        {
            MutexLockGuard lock(mutex_);
            while (is_full())
            {
                notFull_.wait();
            }
            assert(!is_full.full());
            queue_.push_back(x);
            notEmpty_.notify();
        }

        void put(T &&x)
        {
            MutexLockGuard lock(mutex_);
            while (is_full())
            {
                notFull_.wait();
            }
            assert(!is_full());
            queue_.push_back(std::move(x));
            notEmpty_.notify();
        }

        T take()
        {
            MutexLockGuard lock(mutex_);
            while (is_empty())
            {
                notEmpty_.wait();
            }
            assert(!is_empty());
            T front(std::move(queue_.front()));
            queue_.pop_front();
            notFull_.notify();
            return front;
        }

        bool empty() const
        {
            MutexLockGuard lock(mutex_);
            return is_empty();
        }

        bool full() const
        {
            MutexLockGuard lock(mutex_);
            return is_full();
        }

        size_t size() const
        {
            MutexLockGuard lock(mutex_);
            return queue_.size();
        }

        size_t capacity() const
        {
            MutexLockGuard lock(mutex_);
            return queue_.capacity();
        }

    private:
        bool is_full()
        {
            return queue_.size() >= size_;
        }

        bool is_empty()
        {
            return queue_.empty();
        }

    private:
        size_t size_;
        mutable MutexLock mutex_;
        Condition notEmpty_;
        Condition notFull_;
        std::deque<T> queue_;
    };
}