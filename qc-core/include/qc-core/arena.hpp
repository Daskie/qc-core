#pragma once

#include <qc-core/bubble-tracker.hpp>
#include <qc-core/paging.hpp>

namespace qc
{
    class Arena;

    template <typename T>
    class Unq
    {
        template <typename T_> friend class Unq;
        friend class Arena;

      public:

        Unq() = default;

        Unq(const Unq &) = delete;
        Unq(Unq && other);
        template <typename T_> requires std::derived_from<T_, T> Unq(Unq<T_> && other);

        Unq & operator=(const Unq &) = delete;
        Unq & operator=(Unq && other);
        template <typename T_> requires std::derived_from<T_, T> Unq & operator=(Unq<T_> && other);

        ~Unq();

        void reset();

        nodisc explicit operator bool() const { return _ptr; }

        nodisc T & operator*() { return *_ptr; }

        nodisc const T & operator*() const { return *_ptr; }

        nodisc T * operator->() { return _ptr; }

        nodisc const T * operator->() const { return _ptr; }

        nodisc T * get() { return _ptr; }

        nodisc const T * get() const { return _ptr; }

        nodisc bool operator==(const Unq & other) const { return _ptr == other._ptr; }
        nodisc friend bool operator==(const Unq & a, const T * b) { return a._ptr == b; }
        nodisc friend bool operator==(const T * a, const Unq & b) { return a == b._ptr; }

      private:

        T * _ptr{};
        Arena * _arena{};

        Unq(T * ptr, Arena * arena);
    };

    template <typename T>
    class Shr
    {
        template <typename T_> friend class Shr;
        friend class Arena;

      public:

        Shr() = default;

        Shr(const Shr & other);
        template <typename T_> requires std::derived_from<T_, T> Shr(const Shr<T_> & other);
        Shr(Shr && other);
        template <typename T_> requires std::derived_from<T_, T> Shr(Shr<T_> && other);

        Shr & operator=(const Shr & other);
        template <typename T_> requires std::derived_from<T_, T> Shr & operator=(const Shr<T_> & other);
        Shr & operator=(Shr && other);
        template <typename T_> requires std::derived_from<T_, T> Shr & operator=(Shr<T_> && other);

        ~Shr();

        void reset();

        nodisc explicit operator bool() const { return _ptr; }

        nodisc T & operator*() { return *_ptr; }

        nodisc const T & operator*() const { return *_ptr; }

        nodisc T * operator->() { return _ptr; }

        nodisc const T * operator->() const { return _ptr; }

        nodisc T * get() { return _ptr; }

        nodisc const T * get() const { return _ptr; }

        nodisc bool operator==(const Shr & other) const { return _ptr == other._ptr; }
        nodisc friend bool operator==(const Shr & a, const T * b) { return a._ptr == b; }
        nodisc friend bool operator==(const T * a, const Shr & b) { return a == b._ptr; }

      private:

        T * _ptr{};
        Arena * _arena{};

        Shr(T * ptr, Arena * arena);

        u32 & _refCount();
    };

    ///
    /// ...
    /// Each element in the arena is stored with a leading 8 byte header. Of this, the lower four bytes are used for the
    ///   size of the value (necessary for polymorphism), and the upper four bytes are used for the reference count
    ///   (used by `Shr`)
    /// Properties:
    ///   Create: O(m), where `m` is number of unallocated bubbles
    ///   Destroy: O(log(m)), where `m` is number of unallocated bubbles
    ///   Reference stable: Yes
    ///   Index stable: Yes
    ///   Order stable: Yes
    ///   Contiguous elements: No
    ///
    class Arena
    {
        template <typename> friend class Unq;
        template <typename> friend class Shr;

      public:

        explicit Arena(u64 capacity);

        Arena(const Arena &) = delete;
        Arena(Arena &&) = delete;

        Arena & operator=(const Arena &) = delete;
        Arena & operator=(Arena &&) = delete;

        ~Arena();

        template <typename T, typename... Args> nodisc Unq<T> unq(Args && ... args);

        template <typename T, typename... Args> nodisc Shr<T> shr(Args && ... args);

        void shrinkToFit();

        nodisc u64 capacity() const { return _capacity; }

        nodisc u64 size() const { return _size; }

        nodisc bool empty() const { return !_size; }

      private:

        struct _Header
        {
            u32 wordN;
            u32 refCount;
        };

        static_assert(sizeof(_Header) % 8u == 0u);
        static_assert(alignof(_Header) <= 8u);

        static constexpr u64 _headerWordN{sizeof(_Header) / 8u};
        static constexpr u64 _maxValWordN{(u64(1u) << 32) - 1u};

        static u64 _pageN(u64 capacity);


        u64 _capacity;
        u64 _size{};
        u64 * _memory;
        BubbleTracker<u64 *> _bubbles{};

        void _expand(u64 newSize);

        template <typename T, typename... Args> nodisc T * _create(Args && ... args);
        template <typename T> void _destroy(T * v);
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    inline Unq<T>::Unq(T * const ptr, Arena * const arena) :
        _ptr{ptr},
        _arena{arena}
    {}

    template <typename T>
    inline Unq<T>::Unq(Unq && other) :
        _ptr{std::exchange(other._ptr, nullptr)},
        _arena{std::exchange(other._arena, nullptr)}
    {}

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    inline Unq<T>::Unq(Unq<T_> && other) :
        _ptr{std::exchange(other._ptr, nullptr)},
        _arena{std::exchange(other._arena, nullptr)}
    {}

    template <typename T>
    inline Unq<T> & Unq<T>::operator=(Unq && other)
    {
        return this->operator=<T>(std::move(other));
    }

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    inline Unq<T> & Unq<T>::operator=(Unq<T_> && other)
    {
        if (static_cast<void *>(&other) == this)
        {
            return *this;
        }

        reset();

        _ptr = std::exchange(other._ptr, nullptr);
        _arena = std::exchange(other._arena, nullptr);

        return *this;
    }

    template <typename T>
    inline Unq<T>::~Unq()
    {
        reset();
    }

    template <typename T>
    inline void Unq<T>::reset()
    {
        if (_ptr)
        {
            _arena->_destroy(_ptr);

            _ptr = nullptr;
            _arena = nullptr;
        }
    }

    template <typename T>
    inline Shr<T>::Shr(T * const ptr, Arena * const arena) :
        _ptr{ptr},
        _arena{arena}
    {
        ++_refCount();
    }

    template <typename T>
    inline Shr<T>::Shr(const Shr & other) :
        _ptr{other._ptr},
        _arena{other._arena}
    {
        ++_refCount();
    }

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    inline Shr<T>::Shr(const Shr<T_> & other) :
        _ptr{other._ptr},
        _arena{other._arena}
    {
        ++_refCount();
    }

    template <typename T>
    inline Shr<T>::Shr(Shr && other) :
        _ptr{std::exchange(other._ptr, nullptr)},
        _arena{std::exchange(other._arena, nullptr)}
    {}

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    inline Shr<T>::Shr(Shr<T_> && other) :
        _ptr{std::exchange(other._ptr, nullptr)},
        _arena{std::exchange(other._arena, nullptr)}
    {}

    template <typename T>
    inline Shr<T> & Shr<T>::operator=(const Shr & other)
    {
        return this->operator=<T>(other);
    }

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    inline Shr<T> & Shr<T>::operator=(const Shr<T_> & other)
    {
        if (static_cast<const void *>(&other) == this)
        {
            return *this;
        }

        reset();

        _ptr = other._ptr;
        _arena = other._arena;

        if (_ptr)
        {
            ++_refCount();
        }

        return *this;
    }

    template <typename T>
    inline Shr<T> & Shr<T>::operator=(Shr && other)
    {
        return this->operator=<T>(std::move(other));
    }

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    inline Shr<T> & Shr<T>::operator=(Shr<T_> && other)
    {
        if (static_cast<void *>(&other) == this)
        {
            return *this;
        }

        reset();

        _ptr = std::exchange(other._ptr, nullptr);
        _arena = std::exchange(other._arena, nullptr);

        return *this;
    }

    template <typename T>
    inline Shr<T>::~Shr()
    {
        reset();
    }

    template <typename T>
    inline void Shr<T>::reset()
    {
        if (_ptr)
        {
            if (!--_refCount())
            {
                _arena->_destroy(_ptr);
            }

            _ptr = nullptr;
            _arena = nullptr;
        }
    }

    template <typename T>
    forceinline u32 & Shr<T>::_refCount()
    {
        return reinterpret_cast<Arena::_Header *>(_ptr)[-1].refCount;
    }

    inline Arena::Arena(const u64 capacity)
    {
        const u64 pageN{_pageN(capacity)};
        _capacity = pageN * pageSize;
        _memory = static_cast<u64 *>(reservePages(pageN));
        _bubbles.add(_memory, s64(_capacity / 8u));
    }

    inline Arena::~Arena()
    {
        // Check for dangling references
        if constexpr (debug)
        {
            ABORT_IF(_bubbles.bubbles().size() != 1u);
            const auto & bubble{_bubbles.bubbles().front()};
            ABORT_IF(bubble.pos != _memory || u64(bubble.size) * 8u != _capacity);
        }

        freePages(_memory, _pageN(_capacity));
    }

    template <typename T, typename... Args>
    inline Unq<T> Arena::unq(Args &&... args)
    {
        return Unq<T>{_create<T>(std::forward<Args>(args)...), this};
    }

    template <typename T, typename... Args>
    inline Shr<T> Arena::shr(Args &&... args)
    {
        return Shr<T>{_create<T>(std::forward<Args>(args)...), this};
    }

    inline void Arena::shrinkToFit()
    {
        const u64 freeTailSize{u64(_bubbles.tail(_memory + _capacity / 8u)) * 8u};

        // Arena is unallocated or full
        if (!freeTailSize)
        {
            return;
        }

        u64 necessaryPageN{(_capacity - freeTailSize + (pageSize - 1u)) / pageSize};
        if (necessaryPageN) necessaryPageN = std::bit_ceil(necessaryPageN);
        const u64 currentPageN{(_size + (pageSize - 1u)) / pageSize};
        const u64 unnecessaryPageN{currentPageN - necessaryPageN};

        // Free tail is smaller than hald the current size
        if (!unnecessaryPageN)
        {
            return;
        }

        // Decommit uneccessary pages
        decommitPages(reinterpret_cast<std::byte *>(_memory) + necessaryPageN * pageSize, unnecessaryPageN);

        _size = necessaryPageN * pageSize;
    }

    // TODO: Move to paging.hpp
    inline u64 Arena::_pageN(const u64 capacity)
    {
        return std::bit_ceil((capacity + (pageSize - 1u)) / pageSize);
    }

    inline void Arena::_expand(u64 newSize)
    {
        const u64 newPageN{std::bit_ceil((newSize + (pageSize - 1u)) / pageSize)};
        newSize = newPageN * pageSize;

        // Ensure we have sufficient reserved memory
        ABORT_IF(newSize > _capacity);

        // Commit new pages
        const u64 currentPageN{_size / pageSize};
        std::byte * const pages{reinterpret_cast<std::byte *>(_memory)};
        commitPages(pages + currentPageN * pageSize, newPageN - currentPageN);

        _size = newSize;
    }

    template <typename T, typename... Args>
    inline T * Arena::_create(Args &&... args)
    {
        static constexpr u64 valWordN{(sizeof(T) + 7u) / 8u};
        static_assert(valWordN <= _maxValWordN);
        static_assert(alignof(T) <= 8u);

        const u64 totalWordN{_headerWordN + valWordN};
        const auto [wasSpace, ptr]{_bubbles.remove(totalWordN)};

        // Arena is full
        ABORT_IF(!wasSpace);

        const u64 requiredSize{(u64(ptr - _memory) + totalWordN) * 8u};
        if (requiredSize > _size)
        {
            _expand(requiredSize);
        }

        _Header * const header{reinterpret_cast<_Header *>(ptr)};
        header->wordN = valWordN;
        header->refCount = 0u;
        return new (header + 1) T{std::forward<Args>(args)...};
    }

    template <typename T>
    inline void Arena::_destroy(T * const v)
    {
        v->~T();

        _Header & header{reinterpret_cast<_Header *>(v)[-1]};
        _bubbles.add(reinterpret_cast<u64 *>(&header), s64(_headerWordN + header.wordN));
    }
}
