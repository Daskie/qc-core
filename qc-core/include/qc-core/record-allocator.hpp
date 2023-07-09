#pragma once

#include <new>
#include <utility>

#include <qc-core/core.hpp>
#include <qc-core/list.hpp>

namespace qc::memory
{
    struct RecordAllocatorStats
    {
        u64 current{};
        u64 total{};
        u64 allocations{};
        u64 deallocations{};
    };

    namespace _private::record_allocator
    {
        inline List<RecordAllocatorStats> statsList(1u);
    }

    //
    // NOT THREAD SAFE!!!
    //
    template <typename T>
    class RecordAllocator
    {
        template <typename> friend class RecordAllocator;

      public:

        using value_type = T;
        using propagate_on_container_copy_assignment = std::true_type;
        using propagate_on_container_move_assignment = std::true_type;
        using propagate_on_container_swap = std::true_type;
        using is_always_equal = std::false_type;

        RecordAllocator() :
            _listI{_private::record_allocator::statsList.size()}
        {
            _private::record_allocator::statsList.push();
        }

        RecordAllocator(const RecordAllocator &) = default;

        template <typename U>
        RecordAllocator(const RecordAllocator<U> & other) :
            _listI{other._listI}
        {}

        RecordAllocator(RecordAllocator && other) :
            _listI{other._listI}
        {
            other._listI = 0u;
        }

        RecordAllocator & operator=(const RecordAllocator &) = default;

        RecordAllocator & operator=(RecordAllocator && other)
        {
            if (&other == this)
            {
                return *this;
            }

            _listI = other._listI;
            other._listI = 0u;

            return *this;
        }

        ~RecordAllocator() = default;

        T * allocate(const u64 n)
        {
            const u64 bytes{n * sizeof(T)};
            RecordAllocatorStats & stats{this->stats()};
            stats.current += bytes;
            stats.total += bytes;
            ++stats.allocations;
            return reinterpret_cast<T *>(::operator new(bytes));
        }

        void deallocate(T * const ptr, const u64 n)
        {
            const u64 bytes{n * sizeof(T)};
            RecordAllocatorStats & stats{this->stats()};
            stats.current -= bytes;
            ++stats.deallocations;
            ::operator delete(ptr);
        }

        RecordAllocatorStats & stats()
        {
            return _private::record_allocator::statsList[_listI];
        }

        const RecordAllocatorStats & stats() const
        {
            return _private::record_allocator::statsList[_listI];
        }

        bool operator==(const RecordAllocator &) const = default;

      private:

        u64 _listI{};
    };
}
