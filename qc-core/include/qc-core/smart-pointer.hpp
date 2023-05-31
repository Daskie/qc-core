#pragma once

#include <qc-core/core.hpp>

namespace qc
{
    template <typename T, typename Deallocator, bool allowInheritance>
    class Unq
    {
        template <typename, typename, bool> friend class Unq;

      public:

        Unq() = default;
        Unq(IKnowWhatImDoing, T * ptr);

        Unq(const Unq &) = delete;
        Unq(Unq && other);
        template <typename T_> requires (allowInheritance && std::is_base_of_v<T, T_>) Unq(Unq<T_, Deallocator, true> && other);

        Unq & operator=(const Unq &) = delete;
        Unq & operator=(Unq && other);
        template <typename T_> requires (allowInheritance && std::is_base_of_v<T, T_>) Unq & operator=(Unq<T_, Deallocator, true> && other);

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

        nodisc u32 & _refN();
    };

    template <typename T, typename Deallocator, bool allowInheritance>
    class Shr
    {
        template <typename, typename, bool> friend class Shr;

      public:

        Shr() = default;
        Shr(IKnowWhatImDoing, T * ptr);

        Shr(const Shr & other);
        template <typename T_> requires (allowInheritance && std::is_base_of_v<T, T_>) Shr(const Shr<T_, Deallocator, true> & other);
        Shr(Shr && other);
        template <typename T_> requires (allowInheritance && std::is_base_of_v<T, T_>) Shr(Shr<T_, Deallocator, true> && other);

        Shr & operator=(const Shr & other);
        template <typename T_> requires (allowInheritance && std::is_base_of_v<T, T_>) Shr & operator=(const Shr<T_, Deallocator, true> & other);
        Shr & operator=(Shr && other);
        template <typename T_> requires (allowInheritance && std::is_base_of_v<T, T_>) Shr & operator=(Shr<T_, Deallocator, true> && other);

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
    template <typename T, typename Deallocator, bool allowInheritance>
    forceinline Unq<T, Deallocator, allowInheritance>::Unq(IKnowWhatImDoing, T * const ptr) :
        _ptr{ptr}
    {
        u32 & refN{_refN()};
        assert(!refN);
        refN = ~u32{};
    }

    template <typename T, typename Deallocator, bool allowInheritance>
    forceinline Unq<T, Deallocator, allowInheritance>::Unq(Unq && other) :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T, typename Deallocator, bool allowInheritance>
    template <typename T_> requires (allowInheritance && std::is_base_of_v<T, T_>)
    forceinline Unq<T, Deallocator, allowInheritance>::Unq(Unq<T_, Deallocator, true> && other) :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T, typename Deallocator, bool allowInheritance>
    inline auto Unq<T, Deallocator, allowInheritance>::operator=(Unq && other) -> Unq &
    {
        if (&other == this)
        {
            return *this;
        }

        reset();

        _ptr = std::exchange(other._ptr, nullptr);

        return *this;
    }

    template <typename T, typename Deallocator, bool allowInheritance>
    template <typename T_> requires (allowInheritance && std::is_base_of_v<T, T_>)
    forceinline auto Unq<T, Deallocator, allowInheritance>::operator=(Unq<T_, Deallocator, true> && other) -> Unq &
    {
        return *this = reinterpret_cast<Unq &&>(other);
    }

    template <typename T, typename Deallocator, bool allowInheritance>
    forceinline Unq<T, Deallocator, allowInheritance>::~Unq()
    {
        reset();
    }

    template <typename T, typename Deallocator, bool allowInheritance>
    inline void Unq<T, Deallocator, allowInheritance>::reset()
    {
        if (_ptr)
        {
            u32 & refN{_refN()};
            assert(refN);
            refN = 0u;

            // Ensure this object's state is reset first in case of cyclical ownership
            T * const ptr{_ptr};
            _ptr = nullptr;

            ptr->~T();
            Deallocator{}(ptr);
        }
    }

    template <typename T, typename Deallocator, bool allowInheritance>
    forceinline u32 & Unq<T, Deallocator, allowInheritance>::_refN()
    {
        return reinterpret_cast<u32 *>(_ptr)[-1];
    }

    template <typename T, typename Deallocator, bool allowInheritance>
    forceinline Shr<T, Deallocator, allowInheritance>::Shr(IKnowWhatImDoing, T * const ptr) :
        _ptr{ptr}
    {
        u32 & refN{_refN()};
        assert(refN != ~u32{});
        ++_refN();
    }

    template <typename T, typename Deallocator, bool allowInheritance>
    forceinline Shr<T, Deallocator, allowInheritance>::Shr(const Shr & other) :
        _ptr{other._ptr}
    {
        ++_refN();
    }

    template <typename T, typename Deallocator, bool allowInheritance>
    template <typename T_> requires (allowInheritance && std::is_base_of_v<T, T_>)
    forceinline Shr<T, Deallocator, allowInheritance>::Shr(const Shr<T_, Deallocator, true> & other) :
        _ptr{other._ptr}
    {
        ++_refN();
    }

    template <typename T, typename Deallocator, bool allowInheritance>
    forceinline Shr<T, Deallocator, allowInheritance>::Shr(Shr && other) :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T, typename Deallocator, bool allowInheritance>
    template <typename T_> requires (allowInheritance && std::is_base_of_v<T, T_>)
    forceinline Shr<T, Deallocator, allowInheritance>::Shr(Shr<T_, Deallocator, true> && other) :
        _ptr{std::exchange(other._ptr, nullptr)}
    {}

    template <typename T, typename Deallocator, bool allowInheritance>
    inline auto Shr<T, Deallocator, allowInheritance>::operator=(const Shr & other) -> Shr &
    {
        if (&other == this)
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

    template <typename T, typename Deallocator, bool allowInheritance>
    template <typename T_> requires (allowInheritance && std::is_base_of_v<T, T_>)
    forceinline auto Shr<T, Deallocator, allowInheritance>::operator=(const Shr<T_, Deallocator, true> & other) -> Shr &
    {
        return *this = reinterpret_cast<const Shr &>(other);
    }

    template <typename T, typename Deallocator, bool allowInheritance>
    inline auto Shr<T, Deallocator, allowInheritance>::operator=(Shr && other) -> Shr &
    {
        if (&other == this)
        {
            return *this;
        }

        reset();

        _ptr = std::exchange(other._ptr, nullptr);

        return *this;
    }

    template <typename T, typename Deallocator, bool allowInheritance>
    template <typename T_> requires (allowInheritance && std::is_base_of_v<T, T_>)
    forceinline auto Shr<T, Deallocator, allowInheritance>::operator=(Shr<T_, Deallocator, true> && other) -> Shr &
    {
        return *this = reinterpret_cast<Shr &&>(other);
    }

    template <typename T, typename Deallocator, bool allowInheritance>
    forceinline Shr<T, Deallocator, allowInheritance>::~Shr()
    {
        reset();
    }

    template <typename T, typename Deallocator, bool allowInheritance>
    inline void Shr<T, Deallocator, allowInheritance>::reset()
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

    template <typename T, typename Deallocator, bool allowInheritance>
    forceinline u32 & Shr<T, Deallocator, allowInheritance>::_refN()
    {
        return reinterpret_cast<u32 *>(_ptr)[-1];
    }
}
