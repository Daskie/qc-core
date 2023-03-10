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

        Unq() = default;
        Unq(T * ptr, Deleter deleter);

        Unq(const Unq &) = delete;
        Unq(Unq && other);
        template <typename T_> requires (std::derived_from<T_, T>) Unq(Unq<T_> && other);

        Unq & operator=(const Unq &) = delete;
        Unq & operator=(Unq && other);

        ~Unq();

        nodisc explicit operator bool() const { return _ptr; }

        nodisc T & operator*() { return *_ptr; }

        nodisc const T & operator*() const { return *_ptr; }

        nodisc T * operator->() { return _ptr; }

        nodisc const T * operator->() const { return _ptr; }

        nodisc T * get() { return _ptr; }

        nodisc const T * get() const { return _ptr; }

      private:

        T * _ptr{};
        Deleter _deleter{};
    };

    template <typename T>
    class Shr
    {
        template <typename T_> friend class Shr;

      public:

        Shr() = default;
        /// `ptr` MUST BE ALIGNED ON A 8 BYTE BOUNDARY AND THERE MUST BE A ZERO U32 IMMEDIATELY BEFORE `ptr` USED FOR REFERENCE COUNTING
        Shr(T * ptr, Deleter deleter);

        Shr(const Shr & other);
        template <typename T_> requires (std::derived_from<T_, T>) Shr(const Shr<T_> & other);
        Shr(Shr && other);
        template <typename T_> requires (std::derived_from<T_, T>) Shr(Shr<T_> && other);

        Shr & operator=(const Shr & other);
        Shr & operator=(Shr && other);

        ~Shr();

        nodisc explicit operator bool() const { return _ptr; }

        nodisc T & operator*() { return *_ptr; }

        nodisc const T & operator*() const { return *_ptr; }

        nodisc T * operator->() { return _ptr; }

        nodisc const T * operator->() const { return _ptr; }

        nodisc T * get() { return _ptr; }

        nodisc const T * get() const { return _ptr; }

      private:

        T * _ptr{};
        Deleter _deleter{};

        u32 & _refCount() const;
    };

    template <typename T, typename... Args> nodisc Unq<T> makeUnique(Args &&... args);

    template <typename T, typename... Args> nodisc Shr<T> makeShared(Args &&... args);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    inline Unq<T>::Unq(T * const ptr, const Deleter deleter) :
        _ptr{ptr},
        _deleter{deleter}
    {}

    template <typename T>
    inline Unq<T>::Unq(Unq && other) :
        _ptr{std::exchange(other._ptr, nullptr)},
        _deleter{std::exchange(other._deleter, nullptr)}
    {}

    template <typename T>
    template <typename T_> requires (std::derived_from<T_, T>)
    inline Unq<T>::Unq(Unq<T_> && other) :
        _ptr{std::exchange(other._ptr, nullptr)},
        _deleter{std::exchange(other._deleter, nullptr)}
    {}

    template <typename T>
    inline Unq<T> & Unq<T>::operator=(Unq && other)
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
    inline Unq<T>::~Unq()
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
    inline Shr<T>::Shr(T * const ptr, const Deleter deleter) :
        _ptr{ptr},
        _deleter{deleter}
    {
        ++_refCount();
    }

    template <typename T>
    inline Shr<T>::Shr(const Shr & other) :
        _ptr{other._ptr},
        _deleter{other._deleter}
    {
        ++_refCount();
    }

    template <typename T>
    template <typename T_> requires (std::derived_from<T_, T>)
    inline Shr<T>::Shr(const Shr<T_> & other) :
        _ptr{other._ptr},
        _deleter{other._deleter}
    {
        ++_refCount();
    }

    template <typename T>
    inline Shr<T>::Shr(Shr && other) :
        _ptr{std::exchange(other._ptr, nullptr)},
        _deleter{std::exchange(other._deleter, nullptr)}
    {}

    template <typename T>
    template <typename T_> requires (std::derived_from<T_, T>)
    inline Shr<T>::Shr(Shr<T_> && other) :
        _ptr{std::exchange(other._ptr, nullptr)},
        _deleter{std::exchange(other._deleter, nullptr)}
    {}

    template <typename T>
    inline Shr<T> & Shr<T>::operator=(const Shr & other)
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
    inline Shr<T> & Shr<T>::operator=(Shr && other)
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
    inline Shr<T>::~Shr()
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
    inline u32 & Shr<T>::_refCount() const
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
