#pragma once

#include <exception>
#include <new>
#include <utility>

#include <qc-core/core.hpp>
#include <qc-core/list.hpp>

namespace qc::memory
{
    struct RecordAllocatorStats
    {
        unat current{};
        unat total{};
        unat allocations{};
        unat deallocations{};
    };

    namespace _minutia
    {
        inline List<RecordAllocatorStats> recordAllocatorStatsList(1u);
    }

    //
    // NOT THREAD SAFE!!!
    //
    template <typename T>
    class RecordAllocator
    {
        template <typename> friend class RecordAllocator;

        public: //--------------------------------------------------------------

        using value_type = T;
        using propagate_on_container_copy_assignment = std::true_type;
        using propagate_on_container_move_assignment = std::true_type;
        using propagate_on_container_swap = std::true_type;
        using is_always_equal = std::false_type;

        RecordAllocator() noexcept :
            _listI{_minutia::recordAllocatorStatsList.size()}
        {
            _minutia::recordAllocatorStatsList.emplace_back();
        }

        RecordAllocator(const RecordAllocator &) noexcept = default;

        template <typename U>
        RecordAllocator(const RecordAllocator<U> & other) noexcept :
            _listI{other._listI}
        {}

        RecordAllocator(RecordAllocator && other) noexcept :
            _listI{std::exchange(other._listI, 0u)}
        {}

        RecordAllocator & operator=(const RecordAllocator &) noexcept = default;

        RecordAllocator & operator=(RecordAllocator && other) noexcept
        {
            if (&other == this)
            {
                return *this;
            }

            _listI = std::exchange(other._listI, 0u);
            return *this;
        }

        ~RecordAllocator() noexcept = default;

        T * allocate(const unat n)
        {
            const unat bytes{n * sizeof(T)};
            RecordAllocatorStats & stats{this->stats()};
            stats.current += bytes;
            stats.total += bytes;
            ++stats.allocations;
            return reinterpret_cast<T *>(::operator new(bytes));
        }

        void deallocate(T * const ptr, const unat n)
        {
            const unat bytes{n * sizeof(T)};
            RecordAllocatorStats & stats{this->stats()};
            stats.current -= bytes;
            ++stats.deallocations;
            ::operator delete(ptr);
        }

        RecordAllocatorStats & stats()
        {
            return _minutia::recordAllocatorStatsList.at(_listI);
        }

        const RecordAllocatorStats & stats() const
        {
            return _minutia::recordAllocatorStatsList.at(_listI);
        }

        bool operator==(const RecordAllocator &) const noexcept = default;

        private: //-------------------------------------------------------------

        unat _listI{};
    };
}
