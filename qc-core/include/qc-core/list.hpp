#pragma once

#include <cstring>

#include <iterator>

#include <qc-core/view.hpp>

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

        List() = default;
        explicit List(u32 n);
        List(u32 n, const T & v);
        template <typename It> List(It first, It last);
        List(std::initializer_list<T> vs);
        explicit List(CView<T> vs);

        List(const List &) = delete;
        List(List && other);

        List & operator=(const List &) = delete;
        List & operator=(List && other);

        List & operator=(std::initializer_list<T> vs);
        List & operator=(CView<T> vs);

        ~List();

        nodisc finline explicit operator bool() const { return _size; }

        nodisc finline operator View<T>() { return {_data, _size}; }
        nodisc finline operator CView<T>() const { return {_data, _size}; }

        void assign(u32 n, const T & v);
        template <typename It> void assign(It first, It last);

        void fill(const T & v);

        void reserve(u32 capacity);

        void resize(u32 n);
        void resize(u32 n, const T & v);

        void shrink();

        void clear();

        T & push(const T & v);
        T & push(T && v);
        View<T> push(u32 n, const T & v);
        template <typename It> View<T> push(It first, It last);
        View<T> push(std::initializer_list<T> vs);
        View<T> push(CView<T> vs);

        template <typename... Args> T & empush(Args &&... args);

        T & bump();
        View<T> bump(u32 n);

        T * insert(T * pos, const T & v);
        T * insert(T * pos, T && v);
        View<T> insert(T * pos, u32 n, const T & v);
        template <typename It> View<T> insert(T * pos, It first, It last);
        View<T> insert(T * pos, std::initializer_list<T> vs);
        View<T> insert(T * pos, CView<T> vs);

        template <typename... Args> T * emplace(T * pos, Args &&... args);

        void pop();
        void pop(T & dst);
        void pop(u32 n);
        void pop(View<T> dst);

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

        nodisc finline bool contains(const T & v) const { return count(v); }

        template <typename Pred> bool containsIf(Pred && pred) const;

        nodisc T & operator[](const u32 i);
        nodisc const T & operator[](const u32 i) const;

        nodisc finline T & front() { return *_data; }
        nodisc finline const T & front() const { return *_data; }

        nodisc finline T & back() { return _data[_size - 1u]; }
        nodisc finline const T & back() const { return _data[_size - 1u]; }

        nodisc finline u32 capacity() const { return _capacity; }

        nodisc finline u32 size() const { return _size; };

        nodisc finline bool empty() const { return !_size; }

        nodisc finline T * data() { return _data; }
        nodisc finline const T * data() const { return _data; }

        nodisc finline View<T> view() { return {_data, _size}; }
        nodisc finline CView<T> view() const { return {_data, _size}; }
        nodisc finline CView<T> cview() const { return view(); }
        nodisc finline View<T> view(const u32 i, const u32 n) { return {_data + i, n}; }
        nodisc finline CView<T> view(const u32 i, const u32 n) const { return {_data + i, n}; }
        nodisc finline CView<T> cview(const u32 i, const u32 n) const { return view(i, n); }

        nodisc finline T * begin() { return _data; }
        nodisc finline const T * begin() const { return _data; }
        nodisc finline const T * cbegin() const { return _data; }

        nodisc finline T * end() { return _data + _size; }
        nodisc finline const T * end() const { return _data + _size; }
        nodisc finline const T * cend() const { return _data + _size; }

        nodisc finline PushIterator<T> pushIterator() { return PushIterator<T>{*this}; }

        nodisc bool operator==(const List & other) const;
        nodisc bool operator==(std::initializer_list<T> vs) const;

      private:

        inline static constexpr u32 _maxCapacity{1u << 31};

        u32 _capacity{}; // Always a power of two
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
    finline PushIterator<T> & PushIterator<T>::operator=(const T & v)
    {
        _list->push(v);

        return *this;
    }

    template <typename T>
    finline PushIterator<T> & PushIterator<T>::operator=(T && v)
    {
        _list->push(std::move(v));

        return *this;
    }

    template <typename T>
    finline List<T>::List(const u32 n)
    {
        resize(n);
    }

    template <typename T>
    finline List<T>::List(const u32 n, const T & v)
    {
        assign(n, v);
    }

    template <typename T>
    template <typename It>
    finline List<T>::List(const It first, const It last)
    {
        assign(first, last);
    }

    template <typename T>
    finline List<T>::List(const std::initializer_list<T> vs)
    {
        *this = vs;
    }

    template <typename T>
    finline List<T>::List(const CView<T> vs)
    {
        *this = vs;
    }

    template <typename T>
    finline List<T>::List(List && other) :
        _capacity{other._capacity},
        _size{other._size},
        _data{other._data}
    {
        other._capacity = 0u;
        other._size = 0u;
        other._data = nullptr;
    }

    template <typename T>
    finline List<T> & List<T>::operator=(List<T> && other)
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
    finline List<T> & List<T>::operator=(const std::initializer_list<T> vs)
    {
        return *this = CView<T>{std::data(vs), assertCast<u32>(vs.size())};
    }

    template <typename T>
    inline List<T> & List<T>::operator=(const CView<T> vs)
    {
        if constexpr (std::is_trivially_copyable_v<T>)
        {
            reserve(vs.size);
            std::memcpy(_data, vs.data, vs.size * sizeof(T));
            _size = vs.size;
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
    finline void List<T>::assign(const u32 n, const T & v)
    {
        clear();

        resize(n, v);
    }

    template <typename T>
    template <typename It>
    inline void List<T>::assign(const It first, const It last)
    {
        clear();

        const u32 n{assertCast<u32>(std::distance(first, last))};

        reserve(n);

        _size = n;

        It src{first};
        for (T & dst : *this)
        {
            new (&dst) T{*src};
            ++src;
        }

    }

    template <typename T>
    inline void List<T>::fill(const T & v)
    {
        static_assert(std::is_copy_assignable_v<T>);

        for (T & element : *this) element = v;
    }

    template <typename T>
    finline void List<T>::reserve(const u32 capacity)
    {
        if (capacity > _capacity)
        {
            _expand(capacity, 0u, 0u);
        }
    }

    template <typename T>
    inline void List<T>::resize(const u32 n)
    {
        if (n > _size)
        {
            bump(n - _size);
        }
        else if (n < _size)
        {
            pop(_size - n);
        }
    }

    template <typename T>
    inline void List<T>::resize(const u32 n, const T & v)
    {
        if (n > _size)
        {
            push(n - _size, v);
        }
        else if (n < _size)
        {
            pop(_size - n);
        }
    }

    template <typename T>
    inline void List<T>::shrink()
    {
        const u32 minCapacity{_size ? max(std::bit_ceil(_size), 2u) : 0u};

        if (minCapacity < _capacity)
        {
            if (minCapacity)
            {
                _newMemory(minCapacity, 0u, 0u);
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
            for (T & v : *this) v.~T();
        }

        _size = 0u;
    }

    template <typename T>
    finline T & List<T>::push(const T & v)
    {
        static_assert(std::is_copy_constructible_v<T>);

        return empush(v);
    }

    template <typename T>
    finline T & List<T>::push(T && v)
    {
        return empush(std::move(v));
    }

    template <typename T>
    inline View<T> List<T>::push(const u32 n, const T & v)
    {
        static_assert(std::is_copy_constructible_v<T>);

        reserve(_size + n);

        const View<T> dstView{_data + _size, n};

        for (T & dst : dstView) new (&dst) T{v};

        _size += n;

        return dstView;
    }

    template <typename T>
    template <typename It>
    inline View<T> List<T>::push(const It first, const It last)
    {
        static_assert(std::is_copy_constructible_v<T>);

        const u32 n{assertCast<u32>(std::distance(first, last))};

        reserve(_size + n);

        const View<T> dstView{_data + _size, n};

        It src{first};
        for (T & dst : dstView)
        {
            new (&dst) T{*src};
            ++src;
        };

        _size += n;

        return dstView;
    }

    template <typename T>
    finline View<T> List<T>::push(const std::initializer_list<T> vs)
    {
        return push(CView<T>{std::data(vs), assertCast<u32>(vs.size())});
    }

    template <typename T>
    inline View<T> List<T>::push(const CView<T> vs)
    {
        if constexpr (std::is_trivially_copy_constructible_v<T>)
        {
            reserve(_size + vs.size);

            T * const dstFirst{_data + _size};
            std::memcpy(dstFirst, vs.data, vs.size * sizeof(T));
            _size += vs.size;
            return {dstFirst, vs.size};
        }
        else
        {
            return push(vs.begin(), vs.end());
        }
    }

    template <typename T>
    template <typename... Args>
    inline T & List<T>::empush(Args &&... args)
    {
        reserve(_size + 1u);

        T * const pos{_data + _size};

        // Prefer brace initialization, unless the type has an initializer list constructor
        if constexpr (!sizeof...(Args) || !ConstructableByInitializerList<T>)
        {
            new (pos) T{std::forward<Args>(args)...};
        }
        else
        {
            new (pos) T(std::forward<Args>(args)...);
        }

        ++_size;

        return *pos;
    }

    template <typename T>
    T & List<T>::bump()
    {
        static_assert(std::is_default_constructible_v<T>);

        reserve(_size + 1u);

        T & v{_data[_size]};

        if constexpr (!std::is_trivially_default_constructible_v<T>)
        {
            new (&v) T{};
        }

        ++_size;

        return v;
    }

    template <typename T>
    View<T> List<T>::bump(const u32 n)
    {
        static_assert(std::is_default_constructible_v<T>);

        reserve(_size + n);

        const View<T> view{_data + _size, n};

        if constexpr (!std::is_trivially_default_constructible_v<T>)
        {
            for (T & v : view) new (&v) T{};
        }

        _size += n;

        return view;
    }

    template <typename T>
    finline T * List<T>::insert(T * const pos, const T & v)
    {
        static_assert(std::is_copy_constructible_v<T>);

        return emplace(pos, v);
    }

    template <typename T>
    finline T * List<T>::insert(T * const pos, T && v)
    {
        return emplace(pos, std::move(v));
    }

    template <typename T>
    inline View<T> List<T>::insert(T * pos, const u32 n, const T & v)
    {
        static_assert(std::is_copy_constructible_v<T>);
        static constexpr bool destruct{!std::is_trivially_destructible_v<T> && !std::is_copy_assignable_v<T>};

        ASSERT(u64(pos - _data) <= _size); // Handles negative case

        T * const constructedEnd{_shift<destruct>(pos, n)};
        T * const unconstructedEnd{pos + n};

        T * dst{pos};
        if constexpr (!destruct) for (; dst < constructedEnd; ++dst) *dst = v;
        for (; dst < unconstructedEnd; ++dst) new (dst) T{v};

        return {pos, n};
    }

    template <typename T>
    template <typename It>
    inline View<T> List<T>::insert(T * pos, const It first, const It last)
    {
        static_assert(std::is_copy_constructible_v<T>);
        static constexpr bool destruct{!std::is_trivially_destructible_v<T> && !std::is_copy_assignable_v<T>};

        ASSERT(u64(pos - _data) <= _size); // Handles negative case

        const u32 n{assertCast<u32>(std::distance(first, last))};

        T * const constructedEnd{_shift<destruct>(pos, n)};
        T * const unconstructedEnd{pos + n};

        It src{first};
        T * dst{pos};
        if constexpr (!destruct) for (; dst < constructedEnd; ++dst, ++src) *dst = *src;
        for (; dst < unconstructedEnd; ++dst, ++src) new (dst) T{*src};

        return {pos, n};
    }

    template <typename T>
    finline View<T> List<T>::insert(T * const pos, const std::initializer_list<T> vs)
    {
        return insert(pos, CView<T>{std::data(vs), assertCast<u32>(vs.size())});
    }

    template <typename T>
    inline View<T> List<T>::insert(T * pos, const CView<T> vs)
    {
        if constexpr (std::is_trivially_copyable_v<T>)
        {
            _shift<false>(pos, vs.size);
            std::memcpy(pos, vs.data, vs.size * sizeof(T));
            return {pos, vs.size};
        }
        else
        {
            return insert(pos, vs.begin(), vs.end());
        }
    }

    template <typename T>
    template <typename... Args>
    inline T * List<T>::emplace(T * pos, Args &&... args)
    {
        ASSERT(u64(pos - _data) <= _size); // Handles negative case

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
    finline void List<T>::pop()
    {
        ASSERT(_size);

        _data[--_size].~T();
    }

    template <typename T>
    finline void List<T>::pop(T & dst)
    {
        ASSERT(_size);

        T & src{_data[--_size]};
        dst = std::move(src);
        src.~T();
    }

    template <typename T>
    inline void List<T>::pop(const u32 n)
    {
        ASSERT(_size >= n);

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
    inline void List<T>::pop(const View<T> dst)
    {
        ASSERT(dst.size <= _size);

        if constexpr (std::is_trivially_copyable_v<T>)
        {
            std::memcpy(dst.data, _data + _size - dst.size, dst.size * sizeof(T));
        }
        else
        {
            T * src{_data + _size - dst.size};
            for (T & dstV : dst)
            {
                dstV = std::move(*src);
                src->~T();
                ++src;
            }
        }

        _size -= dst.size;
    }

    template <typename T>
    finline T * List<T>::erase(T * const pos)
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

        ASSERT(first >= _data && last <= _data + _size);

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
    finline u32 List<T>::erase(const T & v)
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
    finline T * List<T>::find(const T & v)
    {
        return const_cast<T *>(static_cast<const List &>(*this).find(v));
    }

    template <typename T>
    finline const T * List<T>::find(const T & v) const
    {
        return findIf([&v](const T & a) { return a == v; });
    }

    template <typename T>
    template <typename Pred>
    finline T * List<T>::findIf(Pred && pred)
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
    finline u32 List<T>::count(const T & v) const
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
    template <typename Pred>
    finline bool List<T>::containsIf(Pred && pred) const
    {
        return countIf(std::forward<Pred>(pred));
    }

    template <typename T>
    finline T & List<T>::operator[](const u32 i)
    {
        ASSERT(i < _size);

        return _data[i];
    }

    template <typename T>
    finline const T & List<T>::operator[](const u32 i) const
    {
        ASSERT(i < _size);

        return _data[i];
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
        ASSERT(minNewCapacity <= _maxCapacity);

        _newMemory(max(std::bit_ceil(minNewCapacity), 2u), gapI, gapN);
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
        if (_size >= _capacity) [[unlikely]]
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
