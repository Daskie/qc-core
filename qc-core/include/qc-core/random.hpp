#pragma once

#include <bit>
#include <chrono>

#include <qc-core/core.hpp>

namespace qc
{
    ///
    /// Uses the SFC pseudo-random number generator
    ///   - https://gist.github.com/imneme/f1f7821f07cf76504a97f6537c818083
    ///   - https://www.pcg-random.org/posts/some-prng-implementations.html
    ///   - https://pracrand.sourceforge.net/
    ///
    template <UnsignedIntegral G = u64>
    class Random
    {
      public:

        ///
        /// The underlying unsigned type
        /// Required to qualify as a standard UniformRandomBitGenerator
        ///
        using result_type = G;

        ///
        /// Required to qualify as a standard UniformRandomBitGenerator
        /// @return the minimum possible generated value
        ///
        static constexpr G min() { return std::numeric_limits<G>::min(); }

        ///
        /// Required to qualify as a standard UniformRandomBitGenerator
        /// @return the maximum possible generated value
        ///
        static constexpr G max() { return std::numeric_limits<G>::max(); }

        ///
        /// Constructs a new random generater seeded with the given seed
        /// @param seed the seed to initialize the engine with
        ///
        Random();
        explicit Random(const G seed);

        ///
        /// Required to qualify as a standard UniformRandomBitGenerator
        /// @return the next random `G`
        ///
        G operator()();

        ///
        /// @return the next random integer in [0, 2^T_bits), floater in [0.0, 1.0), or boolean
        ///
        template <NumericOrBoolean T = G> T next();

        ///
        /// @return the next random number in [0, `max`)
        ///
        template <Numeric T> T next(const T max);

        ///
        /// @return the next random number in [`min`, `max`)
        ///
        template <Numeric T> T next(const T min, const T max);

        ///
        /// @return the seed
        ///
        G seed() const { return _seed; }

      private:

        template <typename> struct _Constants;
        template <> struct _Constants< u8> { static constexpr int p{ 3}, q{ 2}, r{1}; };
        template <> struct _Constants<u16> { static constexpr int p{ 4}, q{ 3}, r{2}; };
        template <> struct _Constants<u32> { static constexpr int p{21}, q{ 9}, r{3}; };
        template <> struct _Constants<u64> { static constexpr int p{24}, q{11}, r{3}; };
        static constexpr _Constants<G> _constants{};

        inline static std::atomic<G> _globalSeed{G(std::chrono::high_resolution_clock::now().time_since_epoch().count())};

        G _seed{};
        struct { G a, b, c, d; } _state{};
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <UnsignedIntegral G>
    inline Random<G>::Random() :
        Random(_globalSeed++)
    {}

    template <UnsignedIntegral G>
    inline Random<G>::Random(const G seed) :
        _seed{seed},
        _state{.a = _seed, .b = _seed, .c = _seed, .d = 1}
    {
        // Warm up generator
        for (int i{0}; i < 12; ++i) (*this)();
    }

    template <UnsignedIntegral G>
    inline G Random<G>::operator()()
    {
        const G tmp{G(_state.a + _state.b + _state.d)};
        ++_state.d;
        _state.a = G(_state.b ^ G(_state.b >> _constants.q));
        _state.b = G(_state.c + G(_state.c << _constants.r));
        _state.c = G(std::rotl(_state.c, _constants.p) + tmp);
        return tmp;
    }

    template <UnsignedIntegral G>
    template <NumericOrBoolean T>
    inline T Random<G>::next()
    {
        if constexpr (Integral<T>)
        {
            if constexpr (sizeof(T) == sizeof(G))
            {
                return T((*this)());
            }
            else if constexpr (sizeof(T) < sizeof(G))
            {
                return T(std::make_unsigned_t<T>((*this)() >> (std::numeric_limits<G>::digits - std::numeric_limits<T>::digits)));
            }
            else if constexpr (sizeof(T) > sizeof(G))
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
        }
        else if constexpr (Boolean<T>)
        {
            return (*this)() >> (std::numeric_limits<G>::digits - 1);
        }
    }

    template <UnsignedIntegral G>
    template <Numeric T>
    inline T Random<G>::next(const T max)
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

    template <UnsignedIntegral G>
    template <Numeric T>
    inline T Random<G>::next(const T min, const T max)
    {
        return T(next<T>(T(max - min)) + min);
    }
}
