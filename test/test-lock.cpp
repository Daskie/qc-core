#include <qc-core/lock.hpp>

#include <gtest/gtest.h>

TEST(Lock, compile)
{
    qc::Lock lock{};
    lock.lock();
    lock.unlock();
    static_cast<void>(lock.tryLock());
    lock.unlock();

    qc::LockGuard guard{lock};
}

TEST(SpinLock, compile)
{
    qc::SpinLock lock{};
    lock.lock();
    lock.unlock();
    static_cast<void>(lock.tryLock());
    lock.unlock();

    qc::SpinLockGuard guard{lock};
}
