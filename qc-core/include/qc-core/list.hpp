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

    template <typename T>
    class List
    {
      public:

        static_assert(std::is_move_constructible_v<T>);

        using value_type = T;
        using reference = T &;
        using size_type = unat;
        using difference_type = ptrdiff_t;
        using const_reference = const T &;
        using pointer = T *;
        using const_pointer = const T *;
        using iterator = T *;
        using const_iterator = const T *;
        using reverse_iterator = T *;
        using const_reverse_iterator = const T *;

        static constexpr unat max_size() { return unat{1u} << (std::numeric_limits<unat>::digits - 1); }

        List() = default;
        List(unat n);
        List(unat n, const T & v);
        template <typename It> List(It first, It last);
        List(std::initializer_list<T> vs);
        List(std::span<const T> vs);

        List(const List &) = delete;
        List(List && other);

        List & operator=(const List &) = delete;
        List & operator=(List && other);

        List & operator=(std::initializer_list<T> vs);
        List & operator=(std::span<const T> vs);

        ~List();

        void assign(unat n, const T & v);
        template <typename It> void assign(It first, It last);

        void reserve(unat capacity);

        void resize(unat n);
        void resize(unat n, const T & v);

        void shrink();

        void clear();

        template <typename... Args> T & push(Args &&... args);

        T & bump() requires std::is_trivially_default_constructible_v<T>;
        std::span<T> bump(unat n) requires std::is_trivially_default_constructible_v<T>;

        T * insert(T * pos, const T & v);
        T * insert(T * pos, T && v);
        T * insert(T * pos, unat n, const T & v);
        template <typename It> T * insert(T * pos, It first, It last);
        T * insert(T * pos, std::initializer_list<T> vs);

        template <typename... Args> T * emplace(T * pos, Args &&... args);

        void pop();
        void pop(unat n);

        T * erase(T * pos);
        T * erase(T * first, T * last);

        template <typename Pred> unat eraseIf(Pred && pred);

        T & operator[](const unat i);
        const T & operator[](const unat i) const;

        T & front() { return *_data; }
        const T & front() const { return *_data; }

        T & back() { return _data[_size - 1u]; }
        const T & back() const { return _data[_size - 1u]; }

        unat capacity() const { return _capacity; }

        unat size() const { return _size; }

        bool empty() const { return !_size; }

        T * data() { return _data; }
        const T * data() const { return _data; }

        std::span<T> span() { return {_data, _size}; }
        std::span<const T> span() const { return {_data, _size}; }
        std::span<T> span(const unat i, const unat n) { return {_data + i, n}; }
        std::span<const T> span(const unat i, const unat n) const { return {_data + i, n}; }

        T * begin() { return _data; }
        const T * begin() const { return _data; }
        const T * cbegin() const { return _data; }

        T * end() { return _data + _size; }
        const T * end() const { return _data + _size; }
        const T * cend() const { return _data + _size; }

        PushIterator<T> pushIterator() { return PushIterator<T>{*this}; }

        bool operator==(const List & other) const;
        bool operator==(std::initializer_list<T> other) const;

      private:

        static constexpr unat _defaultMinCapacity{16u};

        unat _capacity{};
        unat _size{};
        T * _data{};

        void _newMemory(unat capacity, unat gapI, unat gapN);

        void _shift(T * & pos);
        template <bool destruct> T * _shift(T * & pos, unat n);
    };

    template <typename T> concept ConstructableByInitializerList = std::is_constructible_v<T, std::initializer_list<typename T::value_type>>;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    inline PushIterator<T> & PushIterator<T>::operator=(const T & v)
    {
        _list->push(v);

        return *this;
    }
    template <typename T>
    inline PushIterator<T> & PushIterator<T>::operator=(T && v)
    {
        _list->push(std::move(v));

        return *this;
    }

    template <typename T>
    inline List<T>::List(const unat n)
    {
        resize(n);
    }

    template <typename T>
    inline List<T>::List(const unat n, const T & v)
    {
        assign(n, v);
    }

    template <typename T>
    template <typename It>
    inline List<T>::List(It first, const It last)
    {
        assign(first, last);
    }

    template <typename T>
    inline List<T>::List(const std::initializer_list<T> vs)
    {
        *this = vs;
    }

    template <typename T>
    inline List<T>::List(const std::span<const T> vs)
    {
        *this = vs;
    }

    template <typename T>
    inline List<T>::List(List && other) :
        _capacity{std::exchange(other._capacity, 0u)},
        _size{std::exchange(other._size, 0u)},
        _data{std::exchange(other._data, nullptr)}
    {}

    template <typename T>
    inline List<T> & List<T>::operator=(List<T> && other)
    {
        _capacity = std::exchange(other._capacity, 0u);
        _size = std::exchange(other._size, 0u);
        _data = std::exchange(other._data, nullptr);

        return *this;
    }

    template <typename T>
    inline List<T> & List<T>::operator=(const std::initializer_list<T> vs)
    {
        return *this = std::span<const T>{std::data(vs), vs.size()};
    }

    template <typename T>
    inline List<T> & List<T>::operator=(const std::span<const T> vs)
    {
        if constexpr (std::is_trivially_copyable_v<T>)
        {
            clear();

            reserve(vs.size());

            std::memcpy(_data, vs.data(), vs.size() * sizeof(T));

            _size = vs.size();
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
                for (T & v: *this) v.~T();
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
    inline void List<T>::assign(const unat n, const T & v)
    {
        clear();

        resize(n, v);
    }

    template <typename T>
    template <typename It>
    inline void List<T>::assign(It first, const It last)
    {
        clear();

        const unat count{unat(std::distance(first, last))};

        reserve(count);

        for (T * dst{_data}; first != last; ++first, ++dst)
        {
            new (dst) T{*first};
        }

        _size = count;
    }

    template <typename T>
    inline void List<T>::reserve(const unat capacity)
    {
        if (capacity > _capacity)
        {
            _newMemory(capacity, 0u, 0u);
        }
    }

    template <typename T>
    inline void List<T>::resize(const unat n)
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
    inline void List<T>::resize(const unat n, const T & v)
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
            _newMemory(max(_capacity * 2u, _defaultMinCapacity), 0u, 0u);
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
    inline T & List<T>::bump() requires std::is_trivially_default_constructible_v<T>
    {
        if (_size == _capacity) [[unlikely]]
        {
            _newMemory(max(_capacity * 2u, _defaultMinCapacity), 0u, 0u);
        }

        return _data[_size++];
    }

    template <typename T>
    inline std::span<T> List<T>::bump(const unat n) requires std::is_trivially_default_constructible_v<T>
    {
        if (_size + n > _capacity) [[unlikely]]
        {
            _newMemory(max(_capacity + max(_capacity, n), _defaultMinCapacity), 0u, 0u);
        }

        T * pos{_data + _size};
        _size += n;
        return {pos, n};
    }

    template <typename T>
    inline T * List<T>::insert(T * const pos, const T & v)
    {
        static_assert(std::is_copy_constructible_v<T>);

        return emplace(pos, v);
    }

    template <typename T>
    inline T * List<T>::insert(T * const pos, T && v)
    {
        return emplace(pos, std::move(v));
    }

    template <typename T>
    inline T * List<T>::insert(T * pos, const unat n, const T & v)
    {
        static_assert(std::is_copy_constructible_v<T>);
        static constexpr bool destruct{!std::is_trivially_destructible_v<T> && !std::is_copy_assignable_v<T>};

        assert(unat(pos - _data) <= _size);

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

        assert(unat(pos - _data) <= _size);

        const unat n{unat(std::distance(first, last))};
        T * const constructedEnd{_shift<destruct>(pos, n)};
        T * const unconstructedEnd{pos + n};

        T * dst{pos};
        if constexpr (!destruct) for (; dst < constructedEnd; ++dst, ++first) *dst = *first;
        for (; dst < unconstructedEnd; ++dst, ++first) new (dst) T{*first};

        return pos;
    }

    template <typename T>
    inline T * List<T>::insert(T * pos, const std::initializer_list<T> vs)
    {
        return insert(pos, vs.begin(), vs.end());
    }

    template <typename T>
    template <typename... Args>
    inline T * List<T>::emplace(T * pos, Args &&... args)
    {
        assert(unat(pos - _data) <= _size);

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
    inline void List<T>::pop()
    {
        assert(_size);

        _data[--_size].~T();
    }

    template <typename T>
    inline void List<T>::pop(const unat n)
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
    inline T * List<T>::erase(T * const pos)
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
            std::memmove(first, last, unat(_data + _size - last) * sizeof(T));
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

        _size -= last - first;
        return first;
    }

    template <typename T>
    template <typename Pred>
    inline unat List<T>::eraseIf(Pred && pred)
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

        const unat n{unat(end - dst)};
        pop(n);
        return n;
    }

    template <typename T>
    inline T & List<T>::operator[](const unat i)
    {
        assert(i < _size);

        return _data[i];
    }

    template <typename T>
    inline const T & List<T>::operator[](const unat i) const
    {
        assert(i < _size);

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
    inline bool List<T>::operator==(const std::initializer_list<T> other) const
    {
        if (_size != other.size())
        {
            return false;
        }

        const T * otherV{other.begin()};
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
    inline void List<T>::_newMemory(const unat newCapacity, const unat gapI, const unat gapN)
    {
        T * const newData{static_cast<T *>(::operator new (newCapacity * sizeof(T), std::align_val_t{alignof(T)}))};
        T * dst{newData};

        const unat headN{gapN ? gapI : _size};

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
            const unat tailN{_size - headN};
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
            const unat i{unat(pos - _data)};
            _newMemory(max(_capacity * 2u, _defaultMinCapacity), i, 1u);
            pos = _data + i;
        }
        else
        {
            T * const end{_data + _size};

            if (pos < end)
            {
                if constexpr (std::is_trivially_copyable_v<T>)
                {
                    std::memmove(pos + 1, pos, unat(end - pos) * sizeof(T));
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
    inline T * List<T>::_shift(T * & pos, const unat n)
    {
        if (n == 0u)
        {
            return pos;
        }

        // The end of the range of slots that already have constructed elements
        T * constructedEnd;

        if (_size + n > _capacity) [[unlikely]]
        {
            const unat i{unat(pos - _data)};
            _newMemory(max(_capacity + max(_capacity, n), _defaultMinCapacity), i, n);
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
