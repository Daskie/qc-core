#pragma once

#include <chrono>
#include <random>

#include <qc-core/core.hpp>

namespace qc
{
    ///
    /// Random number generator which uses std::mt19937/std::mt19937_64
    ///
    /// This is a rather large object (~ 5 KB), but each call to `next` is very fast, so construct once and use a bunch
    ///
    class Random
    {
      public:

        using Engine = std::conditional_t<sizeof(void *) <= 4u, std::mt19937, std::mt19937_64>;

        ///
        /// Constructs a new random generater seeded with the given seed
        ///
        /// @param seed the seed to initialize the engine with, defaults to the current time
        ///
        explicit Random(const unat seed = std::chrono::high_resolution_clock::now().time_since_epoch().count()) noexcept :
            _seed{seed},
            _engine{_seed}
        {}

        Random(const Random & other) noexcept = default;

        Random & operator=(const Random & other) noexcept = default;

        ~Random() noexcept = default;

        ///
        /// @return the next random unsigned integer in [0, `UINT_MAX`]
        ///
        unat next() noexcept;

        ///
        /// @return the next random integer in [0, `UINT_MAX`], floater in [0.0, 1.0], or boolean
        ///
        template <NumericOrBoolean T> T next() noexcept;

        ///
        /// If `T` is integral, `max` should be less than `UINT_MAX` by a few orders of magnitude for best results
        ///
        /// @return the next random integer in [0, `max`) or floater in [0, `max`]
        ///
        template <Numeric T> T next(const T max) noexcept;

        ///
        /// If `T` is integral, `max - min` should be less than `UINT_MAX` by a few orders of magnitude for best results
        ///
        /// @return the next random integer in [`min`, `max`) or floater in [`min`, `max`]
        ///
        template <Numeric T> T next(const T min, const T max) noexcept;

        ///
        /// @return the seed
        ///
        unat seed() const noexcept { return _seed; }

        ///
        /// @return the engine
        ///
        Engine & engine() noexcept { return _engine; }
        const Engine & engine() const noexcept { return _engine; }

      private:

        unat _seed{};
        Engine _engine{};
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    inline unat Random::next() noexcept
    {
        return _engine();
    }

    template <NumericOrBoolean T>
    inline T Random::next() noexcept
    {
        if constexpr (Integral<T>)
        {
            if constexpr (sizeof(T) == sizeof(unat))
            {
                return T(next());
            }
            else if constexpr (sizeof(T) < sizeof(unat))
            {
                return T(std::make_unsigned_t<T>(next() >> (std::numeric_limits<unat>::digits - std::numeric_limits<T>::digits)));
            }
            else
            {
                using U = std::make_unsigned_t<T>;
                using H = typename sized<sizeof(U) / 2u>::utype;
                const H h1{next<H>()};
                const H h2{next<H>()};
                return T(U(h1) | (U(h2) << std::numeric_limits<H>::digits));
            }
        }
        else if constexpr (Floating<T>)
        {
            if constexpr (sizeof(T) == 4u)
            {
                return T(float(next<u32>() >> 8) * 0x1.0p-24f);
            }
            else if constexpr (sizeof(T) == 8u)
            {
                return T(double(next<u64>() >> 11) * 0x1.0p-53);
            }
            else
            {
                static_assert(!sizeof(T));
            }
        }
        else
        {
            return next() >> (std::numeric_limits<unat>::digits - 1);
        }
    }

    template <Numeric T>
    inline T Random::next(const T max) noexcept
    {
        if constexpr (Integral<T>)
        {
            if (max <= T(1))
            {
                return T(0);
            }

            using U = std::make_unsigned_t<T>;

            const U umax{U(max)};
            const int shift{std::countl_zero(U(umax - 1u))};

            // Sampling nearest larger power of two to avoid bias, retry if too large
            U v;
            do
            {
                v = U(next<U>() >> shift);
            }
            while (v >= umax);

            return T(v);
        }
        else
        {
            return next<T>() * max;
        }
    }

    template <Numeric T>
    inline T Random::next(const T min, const T max) noexcept
    {
        return T(next<T>(T(max - min)) + min);
    }
}
