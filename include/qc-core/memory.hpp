#pragma once

#include <exception>
#include <utility>

#include <qc-core/core.hpp>

namespace qc::memory {

    using namespace types;

    template <typename T> class RecordAllocator {

        template <typename> friend class RecordAllocator;

        public:

        using value_type = T;
        using propagate_on_container_copy_assignment = std::true_type;
        using propagate_on_container_move_assignment = std::true_type;
        using propagate_on_container_swap = std::true_type;
        using is_always_equal = std::true_type;

        RecordAllocator() noexcept = default;

        RecordAllocator(const RecordAllocator &) noexcept = default;

        template <typename U>
        explicit RecordAllocator(const RecordAllocator<U> & other) noexcept :
            _current{other._current},
            _total{other._total},
            _allocations{other._allocations},
            _deallocations{other._deallocations}
        {}

        RecordAllocator(RecordAllocator &&) noexcept = default;

        RecordAllocator & operator=(const RecordAllocator &) noexcept = default;

        RecordAllocator & operator=(RecordAllocator &&) noexcept = default;

        ~RecordAllocator() noexcept = default;

        T * allocate(const size_t n) {
            const size_t bytes{n * sizeof(T)};
            _current += bytes;
            _total += bytes;
            ++_allocations;
            return reinterpret_cast<T *>(::operator new(bytes));
        }

        void deallocate(T * const ptr, const size_t n) {
            const size_t bytes{n * sizeof(T)};
            _current -= bytes;
            ++_deallocations;
            ::operator delete(ptr);
        }

        size_t current() const { return _current; }
        size_t total() const { return _total; }
        size_t allocations() const { return _allocations; }
        size_t deallocations() const { return _deallocations; }

        bool operator==(const RecordAllocator &) noexcept {
            return true;
        }

        private:

        size_t _current{};
        size_t _total{};
        size_t _allocations{};
        size_t _deallocations{};

    };

    class MemoryPool {

        static_assert(std::is_same_v<size_t, u64>); // I can't be bothered to make this work with x86 rn

        public:

        static constexpr u64 minCapacity{16u};
        static constexpr u64 maxCapacity{~u64(7u) - 16u};

        MemoryPool(const size_t capacity)
        {
            if (capacity < minCapacity || capacity > maxCapacity) {
                throw std::exception{};
            }

            _chunkCapacity = (capacity + 7u) >> 3;
            _chunks = static_cast<u64 *>(::operator new((_chunkCapacity << 3) + 16u));

            _head = _chunks;
            _head[0] = _chunkCapacity;
            _head[1] = _chunkCapacity;

            size_t * const _tail{_chunks + _chunkCapacity};
            _tail[0] = 0u;
            _tail[1] = 0u;
        }

        MemoryPool(const MemoryPool &) = delete;

        MemoryPool(MemoryPool && other) noexcept :
            _chunkCapacity{std::exchange(other._chunkCapacity, 0u)},
            _chunks{std::exchange(other._chunks, nullptr)},
            _head{std::exchange(other._head, nullptr)}
        {}

        MemoryPool & operator=(const MemoryPool &) = delete;

        MemoryPool & operator=(MemoryPool && other) noexcept {
            _chunkCapacity = std::exchange(other._chunkCapacity, 0u);
            _chunks = std::exchange(other._chunks, nullptr);
            _head = std::exchange(other._head, nullptr);
            return *this;
        }

        ~MemoryPool() {
            if (_chunks) {
                ::operator delete(_chunks);
            }
        }

        template <typename T>
        T * allocate(const u64 n) {
            if (!_chunks || !n) {
                return nullptr;
            }

            const u64 chunkCount{(n * sizeof(T) + 7u) >> 3};

            u64 * block{_head};
            u64 blockSize;
            u64 nextBlockOffset;

            while (true) {
                blockSize = block[0];
                nextBlockOffset = block[1];

                if (!blockSize) {
                    return nullptr;
                }

                // There's space. Must be either a perfect fit, or at least two chunks for meta
                if ((blockSize >= chunkCount) && (blockSize - chunkCount != 1u)) {
                    break;
                }

                block += nextBlockOffset;
            }

            u64 * const nextBlock{block + chunkCount};
            if (blockSize < chunkCount) {
                nextBlock[0] = blockSize - chunkCount;
                nextBlock[1] = nextBlockOffset - chunkCount;
            }
            _head = nextBlock;

            return reinterpret_cast<T *>(block);
        }

        template <typename T>
        void deallocate(T * const ptr, const u64 n) {
            if (!_chunks || !n) {
                return nullptr;
            }

            u64 * const block{reinterpret_cast<u64 *>(ptr)};
            block[0] = (n * sizeof(T) + 7u) >> 3;

            if (block < _head) {
                block[1] = _head - block;
                if (block[1] == block[0]) {
                    block[0] += _head[0];
                    block[1] += _head[1];
                }
                _head = block;
            }
            else {
                u64 * prevBlock{_head};
                u64 * nextBlock{_head + _head[1]};
                while (nextBlock < block) {
                    prevBlock = nextBlock;
                    nextBlock = nextBlock + nextBlock[1];
                }

                // Deal with this block <-> next block
                block[1] = nextBlock - block;
                if (block[1] == block[0]) {
                    block[0] += nextBlock[0];
                    block[1] += nextBlock[1];
                }

                // Deal with prev block <-> this block
                prevBlock[1] = block - prevBlock;
                if (prevBlock[1] == prevBlock[0]) {
                    prevBlock[0] += block[0];
                    prevBlock[1] += block[1];
                }
            }
        }

        private:

        u64 _chunkCapacity{};
        u64 * _chunks{};
        u64 * _head{};

    };

    template <typename T> class PoolAllocator {

        template <typename> friend class PoolAllocator;

        public:

        using value_type = T;
        using propagate_on_container_copy_assignment = std::true_type;
        using propagate_on_container_move_assignment = std::true_type;
        using propagate_on_container_swap = std::true_type;

        PoolAllocator() noexcept = default;

        PoolAllocator(const PoolAllocator &) noexcept = default;

        template <typename U>
        explicit PoolAllocator(const PoolAllocator<U> & other) noexcept :
            _pool{other._pool}
        {}

        PoolAllocator(PoolAllocator &&) noexcept = default;

        PoolAllocator & operator=(const PoolAllocator &) noexcept = default;

        PoolAllocator & operator=(PoolAllocator &&) noexcept = default;

        ~PoolAllocator() noexcept = default;

        T * allocate(const size_t n) {
            return _pool->allocate<T>(n);
        }

        void deallocate(T * const ptr, const size_t n) {
            return _pool->deallocate(ptr, n);
        }

        bool operator==(const PoolAllocator &) const noexcept = default;

        private:

        MemoryPool * _pool{};

    };

} // namespace qc::memory
