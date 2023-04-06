#pragma once

#include <algorithm>
#include <span>

#include <qc-core/core.hpp>
#include <qc-core/list.hpp>

namespace qc
{
    template <Numeric T>
    T median(const std::span<const T> vs)
    {
        static thread_local List<T> buffer{};

        assert(!vs.empty());

        buffer = vs;

        T * const mid{buffer.begin() + s64(buffer.size() / 2u)};
        std::nth_element(buffer.begin(), mid, buffer.end());

        if (buffer.size() % 2u)
        {
            return *mid;
        }
        else
        {
            const T v1{*std::max_element(buffer.begin(), mid)};
            const T v2{*mid};

            if constexpr (Floating<T>)
            {
                return (v1 + v2) * T(0.5);
            }
            else
            {
                return T(v1 + (v2 - v1) / T(2));
            }
        }
    }

    template <Numeric T>
    T medianOrdered(const std::span<const T> vs)
    {
        assert(!vs.empty());

        const T * mid{vs.data() + vs.size() / 2u};

        if (vs.size() % 2u)
        {
            return *mid;
        }
        else
        {
            const T v1{mid[-1]};
            const T v2{*mid};

            if constexpr (Floating<T>)
            {
                return (v1 + v2) * T(0.5);
            }
            else
            {
                return T(v1 + (v2 - v1) / T(2));
            }
        }
    }
}
