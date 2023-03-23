#pragma once
#pragma once

#include <iostream>

#include <qc-core/span.hpp>
#include <qc-core/vector-ext.hpp>

namespace qc
{
    //
    // ...
    //
    template <Numeric R, Numeric T, u32 n> nodisc span<R, n> round(const span<T, n> & s);

    //
    // ...
    //
    template <NumericOrPointer T, u32 n> std::ostream & operator<<(std::ostream & os, const span<T, n> & s);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <Numeric R, Numeric T, u32 n>
    forceinline span<R, n> round(const span<T, n> & s)
    {
        if constexpr (Integral<T>)
        {
            if constexpr (Same<T, R>)
            {
                return s;
            }
            else
            {
                return span<R, n>(s);
            }
        }
        else
        {
            return {round<R>(s.min), round<R>(s.max)};
        }
    }

    template <NumericOrPointer T, u32 n>
    inline std::ostream & operator<<(std::ostream & os, const span<T, n> & s)
    {
        os << "[";
        if constexpr (n == 1) os << "[";
        os << s.min;
        if constexpr (n == 1) os << "][";
        os << s.max;
        if constexpr (n == 1) os << "]";
        os << "]";
        return os;
    }
}
