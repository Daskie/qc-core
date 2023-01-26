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

        Lock() noexcept = default;

        Lock(const Lock &) = delete;
        Lock(Lock &&) = delete;

        Lock & operator=(const Lock &) = delete;
        Lock & operator=(Lock &&) = delete;

        ~Lock() noexcept = default;

        void lock() noexcept;

        bool tryLock() noexcept;

        void unlock() noexcept;

      private:

        std::binary_semaphore _semaphore{1};
    };

    class SpinLock
    {
      public:

        SpinLock() noexcept = default;

        SpinLock(const Lock &) = delete;
        SpinLock(Lock &&) = delete;

        SpinLock & operator=(const Lock &) = delete;
        SpinLock & operator=(Lock &&) = delete;

        ~SpinLock() noexcept = default;

        void lock() noexcept;

        bool tryLock() noexcept;

        void unlock() noexcept;

      private:

        std::atomic_flag _flag{};
    };

    template <typename L>
    class LockGuardT
    {
      public:

        LockGuardT(L & lock) noexcept;

        LockGuardT(const LockGuardT &) = delete;
        LockGuardT(LockGuardT &&) = delete;

        LockGuardT & operator=(const LockGuardT &) = delete;
        LockGuardT & operator=(LockGuardT &&) = delete;

        ~LockGuardT() noexcept;

      private:

        L & _lock;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    void Lock::lock() noexcept
    {
        _semaphore.acquire();
    }

    bool Lock::tryLock() noexcept
    {
        return _semaphore.try_acquire();
    }

    void Lock::unlock() noexcept
    {
        _semaphore.release();
    }

    void SpinLock::lock() noexcept
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

    bool SpinLock::tryLock() noexcept
    {
        // First do a relaxed load to check if lock is free in order to prevent
        //   unnecessary cache misses if someone does while (!try_lock())
        return !_flag.test(std::memory_order_relaxed) && !_flag.test_and_set(std::memory_order_acquire);
    }

    void SpinLock::unlock() noexcept
    {
        _flag.clear(std::memory_order_release);
    }

    template <typename L>
    LockGuardT<L>::LockGuardT(L & lock) noexcept :
        _lock{lock}
    {
        _lock.lock();
    }

    template <typename L>
    LockGuardT<L>::~LockGuardT() noexcept
    {
        _lock.unlock();
    }
}
