#pragma once

#include <cstring>

#include <iterator>
#include <span>

#include <qc-core/core.hpp>

namespace qc
{
    template <typename T> class List;

    template <typename T>
    class PushIterator
    {
      public:

        PushIterator(List<T> & list) : _list{&list} {}

        PushIterator & operator=(const T & v);
        PushIterator & operator=(T && v);

        PushIterator & operator*() { return *this; };

        PushIterator & operator++() { return *this; };
        PushIterator & operator++(int) { return *this; };

      private:

        List<T> * _list;
    };

    ///
    /// ...
    /// Properties:
    ///   Insertion: O(n) general, or O(1) at back
    ///   Erasure: O(n) general, or O(1) at back
    ///   Access: O(1)
    ///   Reference stable: No
    ///   Index stable: No
    ///   Order stable: Yes
    ///   Contiguous elements: Yes
    ///
    template <typename T>
    class List
    {
      public:

        static_assert(std::is_move_constructible_v<T>);

        using value_type = T;
        using reference = T &;
        using size_type = u32;
        using difference_type = s64;
        using const_reference = const T &;
        using pointer = T *;
        using const_pointer = const T *;
        using iterator = T *;
        using const_iterator = const T *;

        static constexpr u32 max_size() { return _maxCapacity; }

        List() = default;
        explicit List(u32 n);
        List(u32 n, const T & v);
        template <typename It> List(It first, It last);
        List(std::initializer_list<T> vs);
        explicit List(std::span<const T> vs);

        List(const List &) = delete;
        List(List && other);

        List & operator=(const List &) = delete;
        List & operator=(List && other);

        List & operator=(std::initializer_list<T> vs);
        List & operator=(std::span<const T> vs);

        ~List();

        void assign(u32 n, const T & v);
        template <typename It> void assign(It first, It last);

        void reserve(u32 capacity);

        void resize(u32 n);
        void resize(u32 n, const T & v);

        void shrink();

        void clear();

        template <typename... Args> T & push(Args &&... args);

        T & bump() requires std::is_trivially_default_constructible_v<T>;
        std::span<T> bump(u32 n) requires std::is_trivially_default_constructible_v<T>;

        T * insert(T * pos, const T & v);
        T * insert(T * pos, T && v);
        T * insert(T * pos, u32 n, const T & v);
        template <typename It> T * insert(T * pos, It first, It last);
        T * insert(T * pos, std::initializer_list<T> vs);

        template <typename... Args> T * emplace(T * pos, Args &&... args);

        void pop();
        void pop(T & dst);
        void pop(u32 n);

        T * erase(T * pos);
        T * erase(T * first, T * last);
        u32 erase(const T & v);

        template <typename Pred> u32 eraseIf(Pred && pred);

        T * find(const T & v);
        const T * find(const T & v) const;

        template <typename Pred> T * findIf(Pred && pred);
        template <typename Pred> const T * findIf(Pred && pred) const;

        u32 count(const T & v) const;

        template <typename Pred> u32 countIf(Pred && pred) const;

        bool contains(const T & v) const;

        template <typename Pred> bool containsIf(Pred && pred) const;

        nodisc T & operator[](const u32 i);
        nodisc const T & operator[](const u32 i) const;

        nodisc T & front();
        nodisc const T & front() const;

        nodisc T & back();
        nodisc const T & back() const;

        nodisc u32 capacity() const;

        nodisc u32 size() const;

        nodisc bool empty() const;

        nodisc T * data();
        nodisc const T * data() const;

        nodisc std::span<T> span();
        nodisc std::span<const T> span() const;
        nodisc std::span<const T> cspan() const;
        nodisc std::span<T> span(const u32 i, const u32 n);
        nodisc std::span<const T> span(const u32 i, const u32 n) const;
        nodisc std::span<const T> cspan(const u32 i, const u32 n) const;

        nodisc T * begin();
        nodisc const T * begin() const;
        nodisc const T * cbegin() const;

        nodisc T * end();
        nodisc const T * end() const;
        nodisc const T * cend() const;

        nodisc PushIterator<T> pushIterator();

        nodisc bool operator==(const List & other) const;
        nodisc bool operator==(std::initializer_list<T> vs) const;

      private:

        static constexpr u32 _autoInitCapacity{16u};
        static constexpr u32 _maxCapacity{std::numeric_limits<u32>::max()};

        u32 _capacity{};
        u32 _size{};
        T * _data{};

        void _expand(u32 minNewCapacity, u32 gapI, u32 gapN);

        void _newMemory(u32 capacity, u32 gapI, u32 gapN);

        void _shift(T * & pos);
        template <bool destruct> T * _shift(T * & pos, u32 n);
    };

    template <typename T> concept ConstructableByInitializerList = std::is_constructible_v<T, std::initializer_list<typename T::value_type>>;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    forceinline PushIterator<T> & PushIterator<T>::operator=(const T & v)
    {
        _list->push(v);

        return *this;
    }

    template <typename T>
    forceinline PushIterator<T> & PushIterator<T>::operator=(T && v)
    {
        _list->push(std::move(v));

        return *this;
    }

    template <typename T>
    forceinline List<T>::List(const u32 n)
    {
        resize(n);
    }

    template <typename T>
    forceinline List<T>::List(const u32 n, const T & v)
    {
        assign(n, v);
    }

    template <typename T>
    template <typename It>
    forceinline List<T>::List(const It first, const It last)
    {
        assign(first, last);
    }

    template <typename T>
    forceinline List<T>::List(const std::initializer_list<T> vs)
    {
        *this = vs;
    }

    template <typename T>
    forceinline List<T>::List(const std::span<const T> vs)
    {
        *this = vs;
    }

    template <typename T>
    forceinline List<T>::List(List && other) :
        _capacity{other._capacity},
        _size{other._size},
        _data{other._data}
    {
        other._capacity = 0u;
        other._size = 0u;
        other._data = nullptr;
    }

    template <typename T>
    forceinline List<T> & List<T>::operator=(List<T> && other)
    {
        _capacity = other._capacity;
        _size = other._size;
        _data = other._data;

        other._capacity = 0u;
        other._size = 0u;
        other._data = nullptr;

        return *this;
    }

    template <typename T>
    forceinline List<T> & List<T>::operator=(const std::initializer_list<T> vs)
    {
        return *this = std::span<const T>{std::data(vs), vs.size()};
    }

    template <typename T>
    inline List<T> & List<T>::operator=(const std::span<const T> vs)
    {
        if constexpr (std::is_trivially_copyable_v<T>)
        {
            const u32 n{assertCast<u32>(vs.size())};

            reserve(n);

            std::memcpy(_data, vs.data(), n * sizeof(T));

            _size = n;
        }
        else
        {
            assign(vs.begin(), vs.end());
        }

        return *this;
    }

    template <typename T>
    inline List<T>::~List()
    {
        if (_capacity)
        {
            if constexpr (!std::is_trivially_destructible_v<T>)
            {
                for (T & v : *this)
                {
                    v.~T();
                }
            }

            ::operator delete(_data, std::align_val_t{alignof(T)});

            if constexpr (debug)
            {
                _capacity = 0u;
                _size = 0u;
                _data = nullptr;
            }
        }
    }

    template <typename T>
    forceinline void List<T>::assign(const u32 n, const T & v)
    {
        clear();

        resize(n, v);
    }

    template <typename T>
    template <typename It>
    inline void List<T>::assign(It first, const It last)
    {
        clear();

        const u32 n{assertCast<u32>(std::distance(first, last))};

        reserve(n);

        for (T * dst{_data}; first != last; ++first, ++dst)
        {
            new (dst) T{*first};
        }

        _size = n;
    }

    template <typename T>
    forceinline void List<T>::reserve(const u32 capacity)
    {
        if (capacity > _capacity)
        {
            _newMemory(capacity, 0u, 0u);
        }
    }

    template <typename T>
    inline void List<T>::resize(const u32 n)
    {
        if (n > _size)
        {
            reserve(n);

            if constexpr (!std::is_trivially_default_constructible_v<T>)
            {
                for (T * p{_data + _size}, * end{_data + _capacity}; p < end; ++p)
                {
                    new (p) T{};
                }
            }
        }
        else
        {
            if constexpr (!std::is_trivially_destructible_v<T>)
            {
                for (T * p{_data + n}, * end{_data + _size}; p < end; ++p)
                {
                    p->~T();
                }
            }
        }

        _size = n;
    }

    template <typename T>
    inline void List<T>::resize(const u32 n, const T & v)
    {
        if (n > _size)
        {
            reserve(n);

            for (T * p{_data + _size}, * end{_data + _capacity}; p < end; ++p)
            {
                new (p) T{v};
            }
        }
        else
        {
            if constexpr (!std::is_trivially_destructible_v<T>)
            {
                for (T * p{_data + n}, * end{_data + _size}; p < end; ++p)
                {
                    p->~T();
                }
            }
        }

        _size = n;
    }

    template <typename T>
    inline void List<T>::shrink()
    {
        if (_size < _capacity)
        {
            if (_size)
            {
                _newMemory(_size, 0u, 0u);
            }
            else
            {
                ::operator delete(_data, std::align_val_t{alignof(T)});
                _capacity = 0u;
                _size = 0u;
                _data = nullptr;
            }
        }
    }

    template <typename T>
    inline void List<T>::clear()
    {
        if constexpr (!std::is_trivially_destructible_v<T>)
        {
            for (T & v: *this) v.~T();
        }

        _size = 0u;
    }

    template <typename T>
    template <typename... Args>
    inline T & List<T>::push(Args &&... args)
    {
        if (_size == _capacity) [[unlikely]]
        {
            _expand(_size + 1u, 0u, 0u);
        }

        T * const pos{_data + _size};
        if constexpr (sizeof...(Args) || !std::is_trivially_default_constructible_v<T>)
        {
            // Prefer brace initialization, unless the type has an initializer list constructor
            if constexpr (!ConstructableByInitializerList<T>)
            {
                new (pos) T{std::forward<Args>(args)...};
            }
            else
            {
                new (pos) T(std::forward<Args>(args)...);
            }
        }
        ++_size;
        return *pos;
    }

    template <typename T>
    forceinline T & List<T>::bump() requires std::is_trivially_default_constructible_v<T>
    {
        if (_size == _capacity) [[unlikely]]
        {
            _expand(_size + 1u, 0u, 0u);
        }

        return _data[_size++];
    }

    template <typename T>
    forceinline std::span<T> List<T>::bump(const u32 n) requires std::is_trivially_default_constructible_v<T>
    {
        if (_size + n > _capacity) [[unlikely]]
        {
            _expand(_size + n, 0u, 0u);
        }

        T * pos{_data + _size};
        _size += n;
        return {pos, n};
    }

    template <typename T>
    forceinline T * List<T>::insert(T * const pos, const T & v)
    {
        static_assert(std::is_copy_constructible_v<T>);

        return emplace(pos, v);
    }

    template <typename T>
    forceinline T * List<T>::insert(T * const pos, T && v)
    {
        return emplace(pos, std::move(v));
    }

    template <typename T>
    inline T * List<T>::insert(T * pos, const u32 n, const T & v)
    {
        static_assert(std::is_copy_constructible_v<T>);
        static constexpr bool destruct{!std::is_trivially_destructible_v<T> && !std::is_copy_assignable_v<T>};

        assert(u64(pos - _data) <= _size); // Handles negative case

        T * const constructedEnd{_shift<destruct>(pos, n)};
        T * const unconstructedEnd{pos + n};

        T * dst{pos};
        if constexpr (!destruct) for (; dst < constructedEnd; ++dst) *dst = v;
        for (; dst < unconstructedEnd; ++dst) new (dst) T{v};

        return pos;
    }

    template <typename T>
    template <typename It>
    inline T * List<T>::insert(T * pos, It first, const It last)
    {
        static_assert(std::is_copy_constructible_v<T>);
        static constexpr bool destruct{!std::is_trivially_destructible_v<T> && !std::is_copy_assignable_v<T>};

        assert(u64(pos - _data) <= _size); // Handles negative case

        const u32 n{assertCast<u32>(std::distance(first, last))};

        T * const constructedEnd{_shift<destruct>(pos, n)};
        T * const unconstructedEnd{pos + n};

        T * dst{pos};
        if constexpr (!destruct) for (; dst < constructedEnd; ++dst, ++first) *dst = *first;
        for (; dst < unconstructedEnd; ++dst, ++first) new (dst) T{*first};

        return pos;
    }

    template <typename T>
    forceinline T * List<T>::insert(T * pos, const std::initializer_list<T> vs)
    {
        return insert(pos, vs.begin(), vs.end());
    }

    template <typename T>
    template <typename... Args>
    inline T * List<T>::emplace(T * pos, Args &&... args)
    {
        assert(u64(pos - _data) <= _size); // Handles negative case

        _shift(pos);

        // Prefer brace initialization, unless the type has an initializer list constructor
        if constexpr (!ConstructableByInitializerList<T>)
        {
            new (pos) T{std::forward<Args>(args)...};
        }
        else
        {
            new (pos) T(std::forward<Args>(args)...);
        }

        return pos;
    }

    template <typename T>
    forceinline void List<T>::pop()
    {
        assert(_size);

        _data[--_size].~T();
    }

    template <typename T>
    forceinline void List<T>::pop(T & dst)
    {
        assert(_size);

        T & src{_data[--_size]};
        dst = std::move(src);
        src.~T();
    }

    template <typename T>
    inline void List<T>::pop(const u32 n)
    {
        assert(_size >= n);

        if constexpr (!std::is_trivially_destructible_v<T>)
        {
            for (T * end{_data + _size}, * pos{end - n}; pos < end; ++pos)
            {
                pos->~T();
            }
        }

        _size -= n;
    }

    template <typename T>
    forceinline T * List<T>::erase(T * const pos)
    {
        return erase(pos, pos + 1);
    }

    template <typename T>
    inline T * List<T>::erase(T * const first, T * const last)
    {
        if (first >= last)
        {
            return first;
        }

        assert(first >= _data && last <= _data + _size);

        if constexpr (std::is_trivially_copyable_v<T> && std::is_trivially_destructible_v<T>)
        {
            std::memmove(first, last, u64(_data + _size - last) * sizeof(T));
        }
        else
        {
            T * const end{_data + _size};
            T * dst{first};
            for (T * src{last}; src < end; ++src, ++dst)
            {
                if constexpr (std::is_move_assignable_v<T>)
                {
                    *dst = std::move(*src);
                }
                else
                {
                    dst->~T();
                    new (dst) T{std::move(*src)};
                }
            }
            for (; dst < end; ++dst)
            {
                dst->~T();
            }
        }

        _size -= u32(last - first);
        return first;
    }

    template <typename T>
    forceinline u32 List<T>::erase(const T & v)
    {
        return eraseIf([&v](const T & a) { return a == v; });
    }

    template <typename T>
    template <typename Pred>
    inline u32 List<T>::eraseIf(Pred && pred)
    {
        T * const end{_data + _size};
        T * dst{_data};

        while (dst < end && !pred(*dst)) ++dst;

        for (T * src{dst + 1}; ; ++dst, ++src)
        {
            while (src < end && pred(*src)) ++src;

            if (src >= end)
            {
                break;
            }

            *dst = std::move(*src);
        }

        const u32 n{u32(end - dst)};
        pop(n);
        return n;
    }

    template <typename T>
    forceinline T * List<T>::find(const T & v)
    {
        return const_cast<T *>(static_cast<const List &>(*this).find(v));
    }

    template <typename T>
    forceinline const T * List<T>::find(const T & v) const
    {
        return findIf([&v](const T & a) { return a == v; });
    }

    template <typename T>
    template <typename Pred>
    forceinline T * List<T>::findIf(Pred && pred)
    {
        return const_cast<T *>(static_cast<const List &>(*this).findIf(std::forward<Pred>(pred)));
    }

    template <typename T>
    template <typename Pred>
    inline const T * List<T>::findIf(Pred && pred) const
    {
        for (const T & v : *this)
        {
            if (pred(v))
            {
                return &v;
            }
        }

        return end();
    }

    template <typename T>
    forceinline u32 List<T>::count(const T & v) const
    {
        return countIf([&v](const T & a) { return a == v; });
    }

    template <typename T>
    template <typename Pred>
    inline u32 List<T>::countIf(Pred && pred) const
    {
        u32 n{0u};

        for (const T & v : *this)
        {
            n += pred(v);
        }

        return n;
    }

    template <typename T>
    forceinline bool List<T>::contains(const T & v) const
    {
        return count(v);
    }

    template <typename T>
    template <typename Pred>
    forceinline bool List<T>::containsIf(Pred && pred) const
    {
        return countIf(std::forward<Pred>(pred));
    }

    template <typename T>
    forceinline T & List<T>::operator[](const u32 i)
    {
        assert(i < _size);

        return _data[i];
    }

    template <typename T>
    forceinline const T & List<T>::operator[](const u32 i) const
    {
        assert(i < _size);

        return _data[i];
    }

    template <typename T>
    forceinline T & List<T>::front()
    {
        return *_data;
    }

    template <typename T>
    forceinline const T & List<T>::front() const
    {
        return *_data;
    }

    template <typename T>
    forceinline T & List<T>::back()
    {
        return _data[_size - 1u];
    }

    template <typename T>
    forceinline const T & List<T>::back() const
    {
        return _data[_size - 1u];
    }

    template <typename T>
    forceinline u32 List<T>::capacity() const
    {
        return _capacity;
    }

    template <typename T>
    forceinline u32 List<T>::size() const
    {
        return _size;
    }

    template <typename T>
    forceinline bool List<T>::empty() const
    {
        return !_size;
    }

    template <typename T>
    forceinline T * List<T>::data()
    {
        return _data;
    }

    template <typename T>
    forceinline const T * List<T>::data() const
    {
        return _data;
    }

    template <typename T>
    forceinline std::span<T> List<T>::span()
    {
        return {_data, _size};
    }

    template <typename T>
    forceinline std::span<const T> List<T>::span() const
    {
        return {_data, _size};
    }

    template <typename T>
    forceinline std::span<const T> List<T>::cspan() const
    {
        return span();
    }

    template <typename T>
    forceinline std::span<T> List<T>::span(const u32 i, const u32 n)
    {
        return {_data + i, n};
    }

    template <typename T>
    forceinline std::span<const T> List<T>::span(const u32 i, const u32 n) const
    {
        return {_data + i, n};
    }

    template <typename T>
    forceinline std::span<const T> List<T>::cspan(const u32 i, const u32 n) const
    {
        return span(i, n);
    }

    template <typename T>
    forceinline T * List<T>::begin()
    {
        return _data;
    }

    template <typename T>
    forceinline const T * List<T>::begin() const
    {
        return _data;
    }

    template <typename T>
    forceinline const T * List<T>::cbegin() const
    {
        return _data;
    }

    template <typename T>
    forceinline T * List<T>::end()
    {
        return _data + _size;
    }

    template <typename T>
    forceinline const T * List<T>::end() const
    {
        return _data + _size;
    }

    template <typename T>
    forceinline const T * List<T>::cend() const
    {
        return _data + _size;
    }

    template <typename T>
    forceinline PushIterator<T> List<T>::pushIterator()
    {
        return PushIterator<T>{*this};
    }

    template <typename T>
    inline bool List<T>::operator==(const List & other) const
    {
        if (this == &other)
        {
            return true;
        }

        if (_size != other._size)
        {
            return false;
        }

        const T * otherV{other._data};
        for (const T & v : *this)
        {
            if (v != *otherV)
            {
                return false;
            }

            ++otherV;
        }

        return true;
    }

    template <typename T>
    inline bool List<T>::operator==(const std::initializer_list<T> vs) const
    {
        if (_size != vs.size())
        {
            return false;
        }

        const T * otherV{vs.begin()};
        for (const T & v : *this)
        {
            if (v != *otherV)
            {
                return false;
            }

            ++otherV;
        }

        return true;
    }

    template <typename T>
    inline void List<T>::_expand(const u32 minNewCapacity, const u32 gapI, const u32 gapN)
    {
        u64 newCapacity{max(u64(minNewCapacity), u64(_capacity) * 2u, u64(_autoInitCapacity))};

        // If new capacity is within 50% of max capacity, just expand up to max capacity
        if (newCapacity + newCapacity / 2u >= _maxCapacity)
        {
            newCapacity = _maxCapacity;
        }

        _newMemory(u32(newCapacity), gapI, gapN);
    }

    template <typename T>
    inline void List<T>::_newMemory(const u32 newCapacity, const u32 gapI, const u32 gapN)
    {
        T * const newData{static_cast<T *>(::operator new (newCapacity * sizeof(T), std::align_val_t{alignof(T)}))};
        T * dst{newData};

        const u32 headN{gapN ? gapI : _size};

        // Move over the head
        if constexpr (std::is_trivially_copyable_v<T> && std::is_trivially_destructible_v<T>)
        {
            std::memcpy(dst, _data, headN * sizeof(T));
            dst += headN;
        }
        else
        {
            for (T * src{_data}, * srcEnd{_data + headN}; src < srcEnd; ++src, ++dst)
            {
                new (dst) T{std::move(*src)};
                src->~T();
            }
        }

        // Skip the gap
        dst += gapN;

        // Move over the tail
        if constexpr (std::is_trivially_copyable_v<T> && std::is_trivially_destructible_v<T>)
        {
            const u32 tailN{_size - headN};
            std::memcpy(dst, _data + headN, tailN * sizeof(T));
            dst += tailN;
        }
        else
        {
            for (T * src{_data + headN}, * srcEnd{_data + _size}; src < srcEnd; ++src, ++dst)
            {
                new (dst) T{std::move(*src)};
                src->~T();
            }
        }

        ::operator delete(_data, std::align_val_t{alignof(T)});

        _capacity = newCapacity;
        _data = newData;
    }

    template <typename T>
    inline void List<T>::_shift(T * & pos)
    {
        if (_size == _capacity) [[unlikely]]
        {
            const u32 i{u32(pos - _data)};
            _expand(_size + 1u, i, 1u);
            pos = _data + i;
        }
        else
        {
            T * const end{_data + _size};

            if (pos < end)
            {
                if constexpr (std::is_trivially_copyable_v<T>)
                {
                    #ifdef QC_GCC
                        // GCC doesn't correctly consider the `pos < end` check above when `_data` and `pos` are null
                        #pragma GCC diagnostic push
                        #pragma GCC diagnostic ignored "-Wnonnull"
                    #endif

                    std::memmove(pos + 1, pos, u64(end - pos) * sizeof(T));

                    #ifdef QC_GCC
                        #pragma GCC diagnostic pop
                    #endif
                }
                else
                {
                    T * dst{end};
                    T * src{dst - 1};
                    new (dst) T{std::move(*src)};
                    --src;
                    --dst;

                    for (; src >= pos; --src, --dst)
                    {
                        if constexpr (std::is_move_assignable_v<T>)
                        {
                            *dst = std::move(*src);
                        }
                        else
                        {
                            dst->~T();
                            new (dst) T{std::move(*src)};
                        }
                    }
                }

                pos->~T();
            }
        }

        ++_size;
    }

    template <typename T>
    template <bool destruct>
    inline T * List<T>::_shift(T * & pos, const u32 n)
    {
        if (n == 0u)
        {
            return pos;
        }

        // The end of the range of slots that already have constructed elements
        T * constructedEnd;

        if (_size + n > _capacity) [[unlikely]]
        {
            const u32 i{u32(pos - _data)};
            _expand(_size + n, i, n);
            pos = _data + i;
            constructedEnd = pos;
        }
        else
        {
            T * const oldTailEnd{_data + _size};
            T * const newTailStart{pos + n};
            T * src{oldTailEnd - 1};
            T * dst{src + n};

            // A portion of the elements will be freshly constructed in new slots
            for (T * firstConstructP{max(newTailStart, oldTailEnd)}; dst >= firstConstructP; --src, --dst)
            {
                new (dst) T{std::move(*src)};
            }

            // The remainder of the elements will be moved
            for (; dst >= newTailStart; --src, --dst)
            {
                if constexpr (std::is_move_assignable_v<T>)
                {
                    *dst = std::move(*src);
                }
                else
                {
                    dst->~T();
                    new (dst) T{std::move(*src)};
                }
            }

            // Destruct now empty elements if necessary
            if constexpr (destruct)
            {
                for (; dst >= pos; --dst)
                {
                    dst->~T();
                }

                constructedEnd = pos;
            }
            else
            {
                constructedEnd = min(newTailStart, oldTailEnd);
            }
        }

        _size += n;
        return constructedEnd;
    }
}
