#ifndef __BASE_ATOMIC_RW_LOCK_H__
#define __BASE_ATOMIC_RW_LOCK_H__

#include "rw_lock_guard.h"
#include <atomic>
#include <thread>

namespace cyber
{
namespace base
{
    class AtomicRWLock
    {
        friend class ReadLockGuard<AtomicRWLock>;
        friend class WriteLockGuard<AtomicRWLock>;

    public:
        static const int32_t RW_LOCK_FREE = 0; // 标志位：代表此时没有线程持有锁，可读可写
        static const int32_t WRITE_EXCLUSIVE = -1; // 标志位：代表此时锁被一个写线程获取
        static const uint32_t MAX_RETRY_TIMES = 5; // 获取锁的连续重试次数，连续失败则让出线程执行权
        AtomicRWLock() {}
        explicit AtomicRWLock(bool write_first) : write_first_(write_first) {}

    private:
        // all these function only can used by ReadLockGuard/WriteLockGuard;
        void ReadLock();
        void WriteLock();

        void ReadUnlock();
        void WriteUnlock();

        AtomicRWLock(const AtomicRWLock &) = delete;
        AtomicRWLock &operator=(const AtomicRWLock &) = delete;
        std::atomic<uint32_t> write_lock_wait_num_ = {0}; // 等待写操作的的线程数
        std::atomic<int32_t> lock_num_ = {0};             // 锁的状态（-1写锁占用 >=0读锁持有数量 =0锁空闲）
        bool write_first_ = true;                         // 默认写优先
    };

    inline void AtomicRWLock::ReadLock()
    {
        uint32_t retry_times = 0;
        int32_t lock_num = lock_num_.load();
        if (write_first_) {
            do {
                // 写优先，只要有等待写的线程，等待。
                while (lock_num < RW_LOCK_FREE || write_lock_wait_num_.load() > 0) {
                    if (++retry_times == MAX_RETRY_TIMES) {
                        // saving cpu
                        std::this_thread::yield();
                        retry_times = 0;
                    }
                    lock_num = lock_num_.load();
                }
            } while (!lock_num_.compare_exchange_weak(
                lock_num, lock_num + 1, std::memory_order_acq_rel, std::memory_order_relaxed));
        } else {
            do {
                while (lock_num < RW_LOCK_FREE) {
                    if (++retry_times == MAX_RETRY_TIMES) {
                        // saving cpu
                        std::this_thread::yield();
                        retry_times = 0;
                    }
                    lock_num = lock_num_.load();
                }
            } while (!lock_num_.compare_exchange_weak(
                lock_num, lock_num + 1, std::memory_order_acq_rel, std::memory_order_relaxed));
        }
    }

    inline void AtomicRWLock::WriteLock()
    {
        int32_t rw_lock_free = RW_LOCK_FREE;
        uint32_t retry_times = 0;
        write_lock_wait_num_.fetch_add(1);
        while (!lock_num_.compare_exchange_weak(
            rw_lock_free, WRITE_EXCLUSIVE, std::memory_order_acq_rel, std::memory_order_relaxed)) {
            rw_lock_free = RW_LOCK_FREE;
            if (++retry_times == MAX_RETRY_TIMES) {
                // saving cpu
                std::this_thread::yield();
                retry_times = 0;
            }
        }
        write_lock_wait_num_.fetch_sub(1);
    }

    inline void AtomicRWLock::ReadUnlock()
    {
        lock_num_.fetch_sub(1);
    }

    inline void AtomicRWLock::WriteUnlock()
    {
        lock_num_.fetch_add(1);
    }

} // namespace base
} // namespace cyber

#endif