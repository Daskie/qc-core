#pragma once

#include <atomic>
#include <semaphore>

#include <qc-core/core.hpp>

namespace qc
{
    class Lock;
    class SpinLock;
    template <typename L> class LockGuardT;

    using LockGuard = LockGuardT<Lock>;
    using SpinLockGuard = LockGuardT<SpinLock>;

    class Lock
    {
      public:

        Lock() = default;

        Lock(const Lock &) = delete;
        Lock(Lock &&) = delete;

        Lock & operator=(const Lock &) = delete;
        Lock & operator=(Lock &&) = delete;

        ~Lock() = default;

        void lock();

        nodisc bool tryLock();

        void unlock();

      private:

        std::binary_semaphore _semaphore{1};
    };

    class SpinLock
    {
      public:

        SpinLock() = default;

        SpinLock(const Lock &) = delete;
        SpinLock(Lock &&) = delete;

        SpinLock & operator=(const Lock &) = delete;
        SpinLock & operator=(Lock &&) = delete;

        ~SpinLock() = default;

        void lock();

        nodisc bool tryLock();

        void unlock();

      private:

        std::atomic_flag _flag{};
    };

    template <typename L>
    class LockGuardT
    {
      public:

        LockGuardT(L & lock);

        LockGuardT(const LockGuardT &) = delete;
        LockGuardT(LockGuardT &&) = delete;

        LockGuardT & operator=(const LockGuardT &) = delete;
        LockGuardT & operator=(LockGuardT &&) = delete;

        ~LockGuardT();

      private:

        L & _lock;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    finline void Lock::lock()
    {
        _semaphore.acquire();
    }

    finline bool Lock::tryLock()
    {
        return _semaphore.try_acquire();
    }

    finline void Lock::unlock()
    {
        _semaphore.release();
    }

    inline void SpinLock::lock()
    {
        while (true)
        {
            // Optimistically assume the lock is free on the first try
            if (!_flag.test_and_set(std::memory_order_acquire))
            {
                break;
            }

            // Wait for lock to be released without generating cache misses
            while (_flag.test(std::memory_order_relaxed));
        }
    }

    finline bool SpinLock::tryLock()
    {
        // First do a relaxed load to check if lock is free in order to prevent
        //   unnecessary cache misses if someone does while (!try_lock())
        return !_flag.test(std::memory_order_relaxed) && !_flag.test_and_set(std::memory_order_acquire);
    }

    finline void SpinLock::unlock()
    {
        _flag.clear(std::memory_order_release);
    }

    template <typename L>
    finline LockGuardT<L>::LockGuardT(L & lock) :
        _lock{lock}
    {
        _lock.lock();
    }

    template <typename L>
    finline LockGuardT<L>::~LockGuardT()
    {
        _lock.unlock();
    }
}
