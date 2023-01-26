#include <gtest/gtest.h>

#include <qc-core/lock.hpp>

TEST(Lock, compile)
{
    qc::Lock lock{};
    lock.lock();
    lock.unlock();
    lock.tryLock();
    lock.unlock();

    qc::LockGuard guard{lock};
}

TEST(SpinLock, compile)
{
    qc::SpinLock lock{};
    lock.lock();
    lock.unlock();
    lock.tryLock();
    lock.unlock();

    qc::SpinLockGuard guard{lock};
}
