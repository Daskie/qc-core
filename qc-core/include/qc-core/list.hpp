#pragma once

#include <cstring>

#include <iterator>
#include <span>

#include <qc-core/core.hpp>

namespace qc
{
    template <typename T>
    class List
    {
      public:

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

        List() noexcept = default;
        List(unat n);
        List(unat n, const T & v);
        template <typename It> List(It first, It last);
        List(std::initializer_list<T> vs);
        List(std::span<const T> vs);

        List(const List &) = delete;
        List(List && other) noexcept;

        List & operator=(const List &) = delete;
        List & operator=(List && other) noexcept;

        List & operator=(std::initializer_list<T> vs) noexcept;
        List & operator=(std::span<const T> vs) noexcept;

        ~List() noexcept;

        void assign(unat n, const T & v);
        template <typename It> void assign(It first, It last);
        void assign(std::initializer_list<T> vs);
        void assign(std::span<const T> vs);

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

        void pop() noexcept;
        void pop(unat n) noexcept;

        T * erase(T * pos) noexcept;
        T * erase(T * first, T * last) noexcept;

        template <typename Pred> unat eraseIf(Pred && pred) noexcept;

        T & operator[](const unat i) noexcept { return _data[i]; };
        const T & operator[](const unat i) const noexcept { return _data[i]; };

        T & front() noexcept { return *_data; }
        const T & front() const noexcept { return *_data; }

        T & back() noexcept { return _data[_size - 1u]; }
        const T & back() const noexcept { return _data[_size - 1u]; }

        unat capacity() const noexcept { return _capacity; }

        unat size() const noexcept { return _size; }

        bool empty() const noexcept { return !_size; }

        T * data() noexcept { return _data; }
        const T * data() const noexcept { return _data; }

        T * begin() noexcept { return _data; }
        const T * begin() const noexcept { return _data; }
        const T * cbegin() const noexcept { return _data; }

        T * end() noexcept { return _data + _size; }
        const T * end() const noexcept { return _data + _size; }
        const T * cend() const noexcept { return _data + _size; }

        bool operator==(const List & other) const noexcept;
        bool operator==(std::initializer_list<T> other) const noexcept;

      private:

        static constexpr unat _defaultMinCapacity{16u};

        unat _capacity{};
        unat _size{};
        T * _data{};

        void _newMemory(unat capacity, unat gapI, unat gapN);

        void _shift(T * & pos);
        T * _shift(T * & pos, unat n);
    };

    template <typename T> concept ConstructableByInitializerList = std::is_constructible_v<T, std::initializer_list<typename T::value_type>>;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
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
        assign(vs);
    }

    template <typename T>
    inline List<T>::List(const std::span<const T> vs)
    {
        assign(vs);
    }

    template <typename T>
    inline List<T>::List(List && other) noexcept :
        _capacity{std::exchange(other._capacity, 0u)},
        _size{std::exchange(other._size, 0u)},
        _data{std::exchange(other._data, nullptr)}
    {}

    template <typename T>
    inline List<T> & List<T>::operator=(List<T> && other) noexcept
    {
        _capacity = std::exchange(other._capacity, 0u);
        _size = std::exchange(other._size, 0u);
        _data = std::exchange(other._data, nullptr);

        return *this;
    }

    template <typename T>
    inline List<T> & List<T>::operator=(const std::initializer_list<T> vs) noexcept
    {
        assign(vs);

        return *this;
    }

    template <typename T>
    inline List<T> & List<T>::operator=(const std::span<const T> vs) noexcept
    {
        assign(vs);

        return *this;
    }

    template <typename T>
    inline List<T>::~List() noexcept
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
            new(dst) T{*first};
        }

        _size = count;
    }

    template <typename T>
    inline void List<T>::assign(const std::initializer_list<T> vs)
    {
        clear();

        reserve(vs.size());

        T * dst{_data};
        for (const T & v: vs)
        {
            new (dst) T{v};
            ++dst;
        }

        _size = vs.size();
    }

    template <typename T>
    inline void List<T>::assign(const std::span<const T> vs)
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
        assert(unat(pos - _data) <= _size);

        T * const constructedEnd{_shift(pos, n)};
        T * const unconstructedEnd{pos + n};

        T * dst{pos};
        for (; dst < constructedEnd; ++dst) *dst = v;
        for (; dst < unconstructedEnd; ++dst) new (dst) T{v};

        return pos;
    }

    template <typename T>
    template <typename It>
    inline T * List<T>::insert(T * pos, It first, const It last)
    {
        assert(unat(pos - _data) <= _size);

        const unat n{unat(std::distance(first, last))};
        T * const constructedEnd{_shift(pos, n)};
        T * const unconstructedEnd{pos + n};

        T * dst{pos};
        for (; dst < constructedEnd; ++dst, ++first) *dst = *first;
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
    inline void List<T>::pop() noexcept
    {
        assert(_size);

        _data[--_size].~T();
    }

    template <typename T>
    inline void List<T>::pop(const unat n) noexcept
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
    inline T * List<T>::erase(T * const pos) noexcept
    {
        return erase(pos, pos + 1);
    }

    template <typename T>
    inline T * List<T>::erase(T * const first, T * const last) noexcept
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
                *dst = std::move(*src);
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
    inline unat List<T>::eraseIf(Pred && pred) noexcept
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
    inline bool List<T>::operator==(const List & other) const noexcept
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
    inline bool List<T>::operator==(const std::initializer_list<T> other) const noexcept
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
                        *dst = std::move(*src);
                    }
                }

                pos->~T();
            }
        }

        ++_size;
    }

    template <typename T>
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

            // The remainder of the elements will be move assigned
            for (; dst >= newTailStart; --src, --dst)
            {
                *dst = std::move(*src);
            }

            constructedEnd = min(newTailStart, oldTailEnd);
        }

        _size += n;
        return constructedEnd;
    }
}
