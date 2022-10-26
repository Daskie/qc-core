#pragma once

#include <qc-core/core.hpp>

namespace qc
{
    using Deleter = void (*)(void *);

    template <typename T>
    class Unq
    {
        template <typename T_> friend class Unq;

      public:

        Unq() noexcept = default;
        Unq(T * ptr, Deleter deleter) noexcept;

        Unq(const Unq &) = delete;
        Unq(Unq && other) noexcept;
        template <typename T_> requires std::derived_from<T_, T> Unq(Unq<T_> && other) noexcept;

        Unq & operator=(const Unq &) = delete;
        Unq & operator=(Unq && other) noexcept;

        ~Unq() noexcept;

        explicit operator bool() const noexcept { return _ptr; }

        T & operator*() noexcept { return *_ptr; }

        const T & operator*() const noexcept { return *_ptr; }

        T * operator->() noexcept { return _ptr; }

        const T * operator->() const noexcept { return _ptr; }

        T * get() noexcept { return _ptr; }

        const T * get() const noexcept { return _ptr; }

      private:

        T * _ptr{};
        Deleter _deleter{};
    };

    template <typename T>
    class Shr
    {
        template <typename T_> friend class Shr;

      public:

        Shr() noexcept = default;
        /// `ptr` MUST BE ALIGNED ON A 8 BYTE BOUNDARY AND THERE MUST BE A ZERO U32 IMMEDIATELY BEFORE `ptr` USED FOR REFERENCE COUNTING
        Shr(T * ptr, Deleter deleter) noexcept;

        Shr(const Shr & other) noexcept;
        template <typename T_> requires std::derived_from<T_, T> Shr(const Shr<T_> & other) noexcept;
        Shr(Shr && other) noexcept;
        template <typename T_> requires std::derived_from<T_, T> Shr(Shr<T_> && other) noexcept;

        Shr & operator=(const Shr & other) noexcept;
        Shr & operator=(Shr && other) noexcept;

        ~Shr() noexcept;

        explicit operator bool() const noexcept { return _ptr; }

        T & operator*() noexcept { return *_ptr; }

        const T & operator*() const noexcept { return *_ptr; }

        T * operator->() noexcept { return _ptr; }

        const T * operator->() const noexcept { return _ptr; }

        T * get() noexcept { return _ptr; }

        const T * get() const noexcept { return _ptr; }

      private:

        T * _ptr{};
        Deleter _deleter{};

        u32 & _refCount() const noexcept;
    };

    template <typename T, typename... Args> Unq<T> makeUnique(Args &&... args);

    template <typename T, typename... Args> Shr<T> makeShared(Args &&... args);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    inline Unq<T>::Unq(T * const ptr, const Deleter deleter) noexcept :
        _ptr{ptr},
        _deleter{deleter}
    {}

    template <typename T>
    inline Unq<T>::Unq(Unq && other) noexcept :
        _ptr{std::exchange(other._ptr, nullptr)},
        _deleter{std::exchange(other._deleter, nullptr)}
    {}

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    inline Unq<T>::Unq(Unq<T_> && other) noexcept :
        _ptr{std::exchange(other._ptr, nullptr)},
        _deleter{std::exchange(other._deleter, nullptr)}
    {}

    template <typename T>
    inline Unq<T> & Unq<T>::operator=(Unq && other) noexcept
    {
        if (&other == this)
        {
            return *this;
        }

        if (_ptr)
        {
            _deleter(_ptr);
        }

        _ptr = std::exchange(other._ptr, nullptr);
        _deleter = std::exchange(other._deleter, nullptr);

        return *this;
    }

    template <typename T>
    inline Unq<T>::~Unq() noexcept
    {
        if (_ptr)
        {
            _deleter(_ptr);
        }

        if constexpr (debug)
        {
            _ptr = nullptr;
            _deleter = nullptr;
        }
    }

    template <typename T>
    inline Shr<T>::Shr(T * const ptr, const Deleter deleter) noexcept :
        _ptr{ptr},
        _deleter{deleter}
    {
        ++_refCount();
    }

    template <typename T>
    inline Shr<T>::Shr(const Shr & other) noexcept :
        _ptr{other._ptr},
        _deleter{other._deleter}
    {
        ++_refCount();
    }

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    inline Shr<T>::Shr(const Shr<T_> & other) noexcept :
        _ptr{other._ptr},
        _deleter{other._deleter}
    {
        ++_refCount();
    }

    template <typename T>
    inline Shr<T>::Shr(Shr && other) noexcept :
        _ptr{std::exchange(other._ptr, nullptr)},
        _deleter{std::exchange(other._deleter, nullptr)}
    {}

    template <typename T>
    template <typename T_> requires std::derived_from<T_, T>
    inline Shr<T>::Shr(Shr<T_> && other) noexcept :
        _ptr{std::exchange(other._ptr, nullptr)},
        _deleter{std::exchange(other._deleter, nullptr)}
    {}

    template <typename T>
    inline Shr<T> & Shr<T>::operator=(const Shr & other) noexcept
    {
        if (&other == this)
        {
            return *this;
        }

        if (_ptr)
        {
            if (!--_refCount())
            {
                _deleter(_ptr);
            }
        }

        _ptr = other._ptr;
        _deleter = other._deleter;

        if (_ptr)
        {
            ++_refCount();
        }

        return *this;
    }

    template <typename T>
    inline Shr<T> & Shr<T>::operator=(Shr && other) noexcept
    {
        if (&other == this)
        {
            return *this;
        }

        if (_ptr)
        {
            if (!--_refCount())
            {
                _deleter(_ptr);
            }
        }

        _ptr = std::exchange(other._ptr, nullptr);
        _deleter = std::exchange(other._deleter, nullptr);

        return *this;
    }

    template <typename T>
    inline Shr<T>::~Shr() noexcept
    {
        if (_ptr)
        {
            if (!--_refCount())
            {
                _deleter(_ptr);
            }
        }

        if constexpr (debug)
        {
            _ptr = nullptr;
            _deleter = nullptr;
        }
    }

    template <typename T>
    inline u32 & Shr<T>::_refCount() const noexcept
    {
        return reinterpret_cast<u32 *>(_ptr)[-1];
    }

    template <typename T, typename... Args>
    inline Unq<T> makeUnique(Args &&... args)
    {
        return Unq<T>(new T{std::forward<Args>(args)...}, [](void * ptr) { delete static_cast<T *>(ptr); });
    }

    template <typename T, typename... Args>
    inline Shr<T> makeShared(Args &&... args)
    {
        static_assert(alignof(T) <= 8u);

        static const auto deleter{[](void * const ptr)
        {
            static_cast<T *>(ptr)->~T();
            ::operator delete(static_cast<u32 *>(ptr) - 2u);
        }};

        u32 * const ptr{static_cast<u32 *>(::operator new(8u + sizeof(T))) + 2u};
        ptr[-1] = 0u;

        return Shr<T>{new (ptr) T{std::forward<Args>(args)...}, deleter};
    }
}
