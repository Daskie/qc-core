#pragma once



#include <random>

#include "Core.hpp"



namespace qc {



// Same as std::mt19937 except the result is always 32 bits
using mt19937 = std::mersenne_twister_engine<
    u32, // <--- As opposed to uint_fast32_t
    std::mt19937::word_size,
    std::mt19937::state_size,
    std::mt19937::shift_size,
    std::mt19937::mask_bits,
    std::mt19937::xor_mask,
    std::mt19937::tempering_u,
    std::mt19937::tempering_d,
    std::mt19937::tempering_s,
    std::mt19937::tempering_b,
    std::mt19937::tempering_t,
    std::mt19937::tempering_c,
    std::mt19937::tempering_l,
    std::mt19937::initialization_multiplier>;

// Same as std::mt19937_64 except the result is always 64 bits
using mt19937_64 = std::mersenne_twister_engine<
    u64, // <--- As opposed to uint_fast64_t
    std::mt19937_64::word_size,
    std::mt19937_64::state_size,
    std::mt19937_64::shift_size,
    std::mt19937_64::mask_bits,
    std::mt19937_64::xor_mask,
    std::mt19937_64::tempering_u,
    std::mt19937_64::tempering_d,
    std::mt19937_64::tempering_s,
    std::mt19937_64::tempering_b,
    std::mt19937_64::tempering_t,
    std::mt19937_64::tempering_c,
    std::mt19937_64::tempering_l,
    std::mt19937_64::initialization_multiplier>;

// By default rather heavy (5 KB), but very fast, so construct once and use often
// Engine must have the following:
//   - type `result_type` that is unsigned and integral
//   - a constexpr static `result_type` default_seed
//   - a default constructor
//   - a constructor that takes a `result_type` (seed)
//   - a copy constructor
//   - an assignment operator
//   - an operator() that returns a `result_type` whose bits are fully saturated
template <typename Engine = std::conditional_t<sizeof(nat) <= 4, mt19937, mt19937_64>>
class Random {

    public:

    using Value = Engine::result_type;

    Random(Value seed = Engine::default_seed) noexcept :
        m_seed(seed),
        m_engine(m_seed)
    {}

    Random(const Random<Engine> & other) noexcept :
        m_seed(other.m_seed),
        m_engine(other.m_engine)
    {}

    Random<Engine> & operator=(const Random<Engine> & other) noexcept {
        m_seed = other.m_seed;
        m_engine = other.m_engine;

        return *this;
    }

    // Returns next random integer in [0, MAX_VALUE] or float in [0.0, 1.0)
    template <typename T>
    T operator()() {
        if constexpr (std::is_integral_v<T>) {
            static_assert(sizeof(T) <= sizeof(Value), "`T` is too large for the engine");

            if constexpr (sizeof(T) < sizeof(Value) || std::is_signed_v<T>) {
                return T(m_engine() & Value(std::numeric_limits<T>::max()));
            }
            else {
                return T(m_engine());
            }
        }
        else if constexpr (std::is_same_v<T, float>) {
            return T(m_engine()) * 0x1p-32f;
        }
        else if constexpr (std::is_same_v<T, double>) {
            return T(m_engine()) * 0x1p-64;
        }
        else {
            static_assert(false, "`T` is an unsupported type");
        }
    }

    // Returns next random value in [0, `max`)
    template <typename T>
    T operator()(T max) {
        if constexpr (std::is_integral_v<T>) {
            return operator()() % max;
        }
        else if constexpr (std::is_floating_point_v<T>) {
            return operator()() * max;
        }
        else {
            static_assert(false, "`T` is an unsupported type");
        }
    }

    // Returns next random value in [`min`, `max`)
    template <typename T>
    T operator()(T min, T max) {
        return operator()(max - min) + min;
    }

    Value seed() const { return m_seed;  }

    private:

    Value m_seed;
    Engine m_engine;

};



//generates n random values between min and 1, the sum of which equals 1
//if min * n > 1, min will be scaled down so that min * n == 1
/*inline void randomDistribution(unat n, float * dest, float min) {
    if (min * n > 1.0f) {
        min = 1.0f / n;
    }
    float total = 0.0f;
    float excess = max(1.0f - n * min, 0.0f);
    for (unat i(0); i < n; ++i) {
        dest[i] = rand(0.0f, 1.0f);
        total += dest[i];
    }
    for (unat i(0); i < n; ++i) {
        dest[i] = dest[i] / total * excess + min;
    }
}*/



}