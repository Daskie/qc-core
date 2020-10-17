#pragma once

#include <random>

#include <qc-core/core.hpp>

namespace qc {

    //
    // Transforms random engine `Engine` result into some type `T`
    //
    template <typename Engine, Numeric T> struct RandomEngineTransformer;

    //
    // Specialization for std::mt19937
    // std::mt19937 produces 32 bits
    // Supports any float
    //
    template <Floating T>
    struct RandomEngineTransformer<std::mt19937, T> {
        T operator()(const u32 result) const {
            return T(result) * T(0x1p-32L);
        }
    };

    //
    // Specialization for std::mt19937
    // std::mt19937 produces 32 bits
    // Supports any integral up to 4 bytes
    //
    template <Integral T> requires (sizeof(T) <= 4)
    struct RandomEngineTransformer<std::mt19937, T> {
        T operator()(const u32 result) const {
            if constexpr (sizeof(T) < 4u || std::is_signed_v<T>) {
                return T(result & std::numeric_limits<T>::max());
            }
            else {
                return T(result);
            }
        }
    };

    //
    // Specialization for std::mt19937_64
    // std::mt19937_64 produces 64 bits
    // Supports any float
    //
    template <Floating T>
    struct RandomEngineTransformer<std::mt19937_64, T> {
        T operator()(const u64 result) const {
            return T(result) * T(0x1p-64L);
        }
    };

    //
    // Specialization for std::mt19937_64
    // std::mt19937_64 produces 64 bits
    // Supports any integral up to 8 bytes
    //
    template <Integral T> requires (sizeof(T) <= 8)
    struct RandomEngineTransformer<std::mt19937_64, T> {
        T operator()(const u64 result) const {
            if constexpr (sizeof(T) < 8u || std::is_signed_v<T>) {
                return T(result & std::numeric_limits<T>::max());
            }
            else {
                return T(result);
            }
        }
    };

    //
    // Specialization for std::minstd_rand
    // std::minstd_rand produces 31 bits
    // Supports any float
    //
    template <Floating T>
    struct RandomEngineTransformer<std::minstd_rand, T> {
        T operator()(const u32 result) const {
            return T(result) * T(0x1p-31L);
        }
    };

    //
    // Specialization for std::minstd_rand
    // std::minstd_rand produces 31 bits
    // Supports any unsigned up to 2 bytes
    //
    template <UnsignedIntegral T> requires (sizeof(T) <= 2)
    struct RandomEngineTransformer<std::minstd_rand, T> {
        T operator()(const u32 result) const {
            return T(result & std::numeric_limits<T>::max());
        }
    };

    //
    // Specialization for std::minstd_rand
    // std::minstd_rand produces 31 bits
    // Supports any signed up to 4 bytes
    //
    template <SignedIntegral T> requires (sizeof(T) <= 4)
    struct RandomEngineTransformer<std::minstd_rand, T> {
        T operator()(const u32 result) const {
            if constexpr (sizeof(T) < 4u) {
                return T(result & std::numeric_limits<T>::max());
            }
            else {
                return T(result);
            }
        }
    };

    //
    // Random number generator using the given random engine `Engine`
    // The default engine, std::mt19937, is rather heavy (5 KB), but very fast, so construct once and use often
    // Engine must have the following:
    //   - type `result_type` that is unsigned and integral
    //   - a constexpr static `result_type` default_seed
    //   - a default constructor
    //   - a constructor that takes a `result_type` (seed)
    //   - a copy constructor
    //   - an assignment operator
    //   - an operator() that returns a `result_type` whose bits are fully saturated
    //   - a static method `max` that returns the maximum `result_type` that may be generated
    //
    template <typename Engine = std::conditional_t<sizeof(intptr_t) <= 4u, std::mt19937, std::mt19937_64>>
    class Random {

        public:

        using Value = typename Engine::result_type;

        Random(const Value seed = Engine::default_seed) noexcept :
            _seed(seed),
            _engine(_seed)
        {}

        Random(const Random<Engine> & other) noexcept :
            _seed(other._seed),
            _engine(other._engine)
        {}

        Random<Engine> & operator=(const Random<Engine> & other) noexcept {
            _seed = other._seed;
            _engine = other._engine;

            return *this;
        }

        //
        // Returns a random integer in [0, T_MAX] or a float in [0.0, 1.0).
        //
        template <Numeric T>
        T next() noexcept {
            return RandomEngineTransformer<Engine, T>()(_engine());
        }

        //
        // Returns next random value in [0, `max`).
        // `max` should be less than T_MAX by a few orders of magnitude for best results.
        //
        template <Numeric T>
        T next(const T max) noexcept {
            if constexpr (std::is_integral_v<T>) {
                return next<T>() % max;
            }
            else {
                return next<T>() * max;
            }
        }

        //
        // Returns next random value in [`min`, `max`).
        //
        template <Numeric T>
        T next(const T min, const T max) noexcept {
            return next<T>(max - min) + min;
        }

        //
        // Returns the seed.
        //
        Value seed() const noexcept { return _seed; }

        private:

        Value _seed;
        Engine _engine;

    };

} // namespace qc
