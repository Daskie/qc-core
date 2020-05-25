#pragma once

#include <random>

#include "core.hpp"

namespace qc::core {

    //
    // Transforms random engine `Engine` result into some type `T`
    //
    template <typename Engine, typename T>
    struct RandomEngineTransformer {
        T operator()(typename Engine::result_type result) const;
    };

    //
    // Specialization for std::mt19937
    // std::mt19937 produces 32 bits
    // Supports
    //   - any float
    //   - integral up to 4 bytes
    //
    template <typename T>
    struct RandomEngineTransformer<std::mt19937, T> {
        T operator()(u32 result) const {
            if constexpr (is_floating_point_v<T>) {
                return T(result) * T(0x1p-32L);
            }
            else if constexpr (is_integral_v<T>) {
                static_assert(sizeof(T) <= 4u);

                if constexpr (sizeof(T) < 4u || is_signed_v<T>) {
                    return T(result & std::numeric_limits<T>::max());
                }
                else {
                    return T(result);
                }
            }
            else {
                static_assert(false);
            }
        }
    };

    //
    // Specialization for std::mt19937_64
    // std::mt19937_64 produces 64 bits
    // Supports
    //   - any float
    //   - integral up to 8 bytes
    //
    template <typename T>
    struct RandomEngineTransformer<std::mt19937_64, T> {
        T operator()(u64 result) const {
            if constexpr (std::is_floating_point_v<T>) {
                return T(result) * T(0x1p-64L);
            }
            else if constexpr (std::is_integral_v<T>) {
                static_assert(sizeof(T) <= 8u);

                if constexpr (sizeof(T) < 8u || std::is_signed_v<T>) {
                    return T(result & std::numeric_limits<T>::max());
                }
                else {
                    return T(result);
                }
            }
            else {
                static_assert(false);
            }
        }
    };

    //
    // Specialization for std::minstd_rand
    // std::minstd_rand produces 31 bits
    // Supports
    //   - any float
    //   - unsigned up to 2 bytes
    //   - signed up to 4 bytes
    //
    template <typename T>
    struct RandomEngineTransformer<std::minstd_rand, T> {
        T operator()(u32 result) const {
            if constexpr (std::is_floating_point_v<T>) {
                return T(result) * T(0x1p-31L);
            }
            else if constexpr (std::is_integral_v<T>) {
                if constexpr (sizeof(T) < 4u) {
                    return T(result & std::numeric_limits<T>::max());
                }
                else if constexpr (sizeof(T) == 4u && std::is_signed_v<T>) {
                    return T(result);
                }
                else {
                    static_assert(false);
                }
            }
            else {
                static_assert(false);
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

        Random(Value seed = Engine::default_seed) noexcept :
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
        // Returns a random `T`
        // If `T` is arithmetic, returns an integer in [0, T_MAX] or a float in [0.0, 1.0)
        //
        template <typename T>
        T next() {
            return RandomEngineTransformer<Engine, T>()(_engine());
        }

        //
        // Returns next random value in [0, `max`)
        // `T` must be arithmetic
        //
        template <typename T>
        T next(T max) {
            if constexpr (is_integral_v<T>) {
                return operator()() % max;
            }
            else if constexpr (is_floating_point_v<T>) {
                return operator()() * max;
            }
            else {
                static_assert(false, "`T` is an unsupported type");
            }
        }

        //
        // Returns next random value in [`min`, `max`)
        // `T` must be arithmetic
        //
        template <typename T>
        T next(T min, T max) {
            return operator()(max - min) + min;
        }

        //
        // Returns the seed
        //
        Value seed() const { return _seed;  }

        private:

        Value _seed;
        Engine _engine;

    };

    //
    // Generates n random values between `min` and `1`, the sum of which equals `1`.
    // If `min * n > 1`, `min` will be scaled down so that `min * n == 1`.
    //
    //inline void randomDistribution(uint n, float * dest, float min) {
    //    if (min * n > 1.0f) {
    //        min = 1.0f / n;
    //    }
    //    float total = 0.0f;
    //    float excess = max(1.0f - n * min, 0.0f);
    //    for (uint i(0); i < n; ++i) {
    //        dest[i] = rand(0.0f, 1.0f);
    //        total += dest[i];
    //    }
    //    for (uint i(0); i < n; ++i) {
    //        dest[i] = dest[i] / total * excess + min;
    //    }
    //}

}
