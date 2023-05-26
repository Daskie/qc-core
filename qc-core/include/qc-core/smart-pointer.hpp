#pragma once

#include <qc-core/core.hpp>

namespace qc
{
    template <typename T, typename Deallocator>
    class Unq
    {
        template <typename T_, typename Deallocator_> friend class Unq;

      public:

        Unq() = default;
        Unq(IKnowWhatImDoing, T * ptr);

        Unq(const Unq &) = delete;
        Unq(Unq && other);
        template <typename T_> requires std::derived_from<T_, T> Unq(Unq<T_, Deallocator> && other);

        Unq & operator=(const Unq &) = delete;
        Unq & operator=(Unq && other);
        template <typename T_> requires std::derived_from<T_, T> Unq & operator=(Unq<T_, Deallocator> && other);

        ~Unq();

        void reset();

        nodisc forceinline explicit operator bool() const { return _ptr; }

        nodisc forceinline T & operator*() const { return *_ptr; }

        nodisc forceinline T * operator->() const { return _ptr; }

        nodisc forceinline T * get() const { return _ptr; }

        nodisc forceinline bool operator==(const Unq & other) const { return _ptr == other._ptr; }
        nodisc forceinline friend bool operator==(const Unq & a, const T * b) { return a._ptr == b; }
        nodisc forceinline friend bool operator==(const T * a, const Unq & b) { return a == b._ptr; }

      private:

        T * _ptr{};
    };

    template <typename T, typename Deallocator>
    class Shr
    {
        template <typename T_, typename Deallocator_> friend class Shr;

      public:

        Shr() = default;
        Shr(IKnowWhatImDoing, T * ptr);

        Shr(const Shr & other);
        template <typename T_> requires std::derived_from<T_, T> Shr(const Shr<T_, Deallocator> & other);
        Shr(Shr && other);
        template <typename T_> requires std::derived_from<T_, T> Shr(Shr<T_, Deallocator> && other);

        Shr & operator=(const Shr & other);
        template <typename T_> requires std::derived_from<T_, T> Shr & operator=(const Shr<T_, Deallocator> & other);
        Shr & operator=(Shr && other);
        template <typename T_> requires std::derived_from<T_, T> Shr & operator=(Shr<T_, Deallocator> && other);

        ~Shr();

        void reset();

        nodisc forceinline explicit operator bool() const { return _ptr; }

        nodisc forceinline T & operator*() const { return *_ptr; }

        nodisc forceinline T * operator->() const { return _ptr; }

        nodisc forceinline T * get() const { return _ptr; }

        nodisc forceinline bool operator==(const Shr & other) const { return _ptr == other._ptr; }
        nodisc forceinline friend bool operator==(const Shr & a, const T * b) { return a._ptr == b; }
        nodisc forceinline friend bool operator==(const T * a, const Shr & b) { return a == b._ptr; }

      private:

        T * _ptr{};

        nodisc u32 & _refN();
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T, typename Deallocator>
    forceinline Unq<T, Deallocator>::Unq(IKnowWhatImDoing, T * const ptr) :
        _ptr{ptr}
    {}

    template <typename T, typename Deallocator>
    forceinline Unq<T, Deallocator>::Unq(Unq && other) :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T, typename Deallocator>
    template <typename T_> requires std::derived_from<T_, T>
    forceinline Unq<T, Deallocator>::Unq(Unq<T_, Deallocator> && other) :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T, typename Deallocator>
    forceinline auto Unq<T, Deallocator>::operator=(Unq && other) -> Unq &
    {
        return this->operator=<T>(std::move(other));
    }

    template <typename T, typename Deallocator>
    template <typename T_> requires std::derived_from<T_, T>
    inline auto Unq<T, Deallocator>::operator=(Unq<T_, Deallocator> && other) -> Unq &
    {
        if (static_cast<void *>(&other) == this)
        {
            return *this;
        }

        reset();

        _ptr = std::exchange(other._ptr, nullptr);

        return *this;
    }

    template <typename T, typename Deallocator>
    forceinline Unq<T, Deallocator>::~Unq()
    {
        reset();
    }

    template <typename T, typename Deallocator>
    inline void Unq<T, Deallocator>::reset()
    {
        if (_ptr)
        {
            // Ensure this object's state is reset first in case of cyclical ownership
            T * const ptr{_ptr};
            _ptr = nullptr;

            ptr->~T();
            Deallocator{}(ptr);
        }
    }

    template <typename T, typename Deallocator>
    forceinline Shr<T, Deallocator>::Shr(IKnowWhatImDoing, T * const ptr) :
        _ptr{ptr}
    {
        ++_refN();
    }

    template <typename T, typename Deallocator>
    forceinline Shr<T, Deallocator>::Shr(const Shr & other) :
        _ptr{other._ptr}
    {
        ++_refN();
    }

    template <typename T, typename Deallocator>
    template <typename T_> requires std::derived_from<T_, T>
    forceinline Shr<T, Deallocator>::Shr(const Shr<T_, Deallocator> & other) :
        _ptr{other._ptr}
    {
        ++_refN();
    }

    template <typename T, typename Deallocator>
    forceinline Shr<T, Deallocator>::Shr(Shr && other) :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T, typename Deallocator>
    template <typename T_> requires std::derived_from<T_, T>
    forceinline Shr<T, Deallocator>::Shr(Shr<T_, Deallocator> && other) :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T, typename Deallocator>
    forceinline auto Shr<T, Deallocator>::operator=(const Shr & other) -> Shr &
    {
        return this->operator=<T>(other);
    }

    template <typename T, typename Deallocator>
    template <typename T_> requires std::derived_from<T_, T>
    inline auto Shr<T, Deallocator>::operator=(const Shr<T_, Deallocator> & other) -> Shr &
    {
        if (static_cast<const void *>(&other) == this)
        {
            return *this;
        }

        reset();

        _ptr = other._ptr;

        if (_ptr)
        {
            ++_refN();
        }

        return *this;
    }

    template <typename T, typename Deallocator>
    forceinline auto Shr<T, Deallocator>::operator=(Shr && other) -> Shr &
    {
        return this->operator=<T>(std::move(other));
    }

    template <typename T, typename Deallocator>
    template <typename T_> requires std::derived_from<T_, T>
    inline auto Shr<T, Deallocator>::operator=(Shr<T_, Deallocator> && other) -> Shr &
    {
        if (static_cast<void *>(&other) == this)
        {
            return *this;
        }

        reset();

        _ptr = std::exchange(other._ptr, nullptr);

        return *this;
    }

    template <typename T, typename Deallocator>
    forceinline Shr<T, Deallocator>::~Shr()
    {
        reset();
    }

    template <typename T, typename Deallocator>
    inline void Shr<T, Deallocator>::reset()
    {
        if (_ptr)
        {
            u32 & refN{_refN()};
            assert(refN >= 1u);

            // Ensure this object's state is reset first in case of cyclical ownership
            T * const ptr{_ptr};
            _ptr = nullptr;

            if (!--refN)
            {
                ptr->~T();
                Deallocator{}(ptr);
            }
        }
    }

    template <typename T, typename Deallocator>
    forceinline u32 & Shr<T, Deallocator>::_refN()
    {
        return reinterpret_cast<u32 *>(_ptr)[-1];
    }
}
