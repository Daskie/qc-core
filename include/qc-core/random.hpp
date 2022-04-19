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
        explicit Random(const size_t seed = std::chrono::high_resolution_clock::now().time_since_epoch().count()) noexcept :
            _seed{seed},
            _engine{_seed}
        {}

        Random(const Random & other) noexcept = default;

        Random & operator=(const Random & other) noexcept = default;

        ~Random() noexcept = default;

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
        size_t seed() const noexcept { return _seed; }

        ///
        /// @return the engine
        ///
        Engine & engine() noexcept { return _engine; }
        const Engine & engine() const noexcept { return _engine; }

      private:

        size_t _seed{};
        Engine _engine{};
    };
}

////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <NumericOrBoolean T>
    T Random::next() noexcept
    {
        const size_t raw{_engine()};

        if constexpr (Integral<T>)
        {
            static_assert(sizeof(T) <= sizeof(size_t));

            if constexpr (std::is_signed_v<T>)
            {
                // Separated out for better debug performance
                static constexpr size_t mask{size_t(std::numeric_limits<T>::max())};
                return T(std::make_unsigned_t<T>(raw & mask));
            }
            else
            {
                return T(raw);
            }
        }
        else if constexpr (Floating<T>)
        {
            // Separated out for better debug performance
            static constexpr T scaleFactor{T(1.0) / T(Engine::max())};
            return T(raw) * scaleFactor;
        }
        else if (std::is_same_v<T, bool>)
        {
            return raw & 1u;
        }
    }

    template <Numeric T>
    T Random::next(const T max) noexcept
    {
        if constexpr (Integral<T>)
        {
            return next<T>() % max;
        }
        else
        {
            return next<T>() * max;
        }
    }

    template <Numeric T>
    T Random::next(const T min, const T max) noexcept
    {
        return next<T>(max - min) + min;
    }
}
