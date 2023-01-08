#include <qc-core/random.hpp>

#include <gtest/gtest.h>

using namespace qc::types;

namespace
{
    constexpr unat n{1000u};

    template <typename T, typename G>
    void testUnsigned(qc::Random<G> & random)
    {
        random.template next<T>();

        {
            const T v{random.template next<T>(0u)};
            ASSERT_EQ(v, 0u);
        }

        {
            const T v{random.template next<T>(1u)};
            ASSERT_EQ(v, 0u);
        }

        u32 bits{};

        for (unat i{0u}; i < n; ++i)
        {
            {
                const T v{random.template next<T>(2u)};
                ASSERT_LT(v, 2u);
            }

            {
                const T v{random.template next<T>(3u)};
                ASSERT_LT(v, 3u);
            }

            {
                const T v{random.template next<T>(4u)};
                ASSERT_LT(v, 4u);
            }

            {
                const T v{random.template next<T>(5u)};
                ASSERT_LT(v, 5u);
            }

            {
                const T v{random.template next<T>(3u, 7u)};
                ASSERT_GE(v, 3u);
                ASSERT_LT(v, 7u);
            }

            bits |= 1u << random.template next<T>(32u);
        }

        ASSERT_EQ(bits, ~u32{});
    }

    template <typename T, typename G>
    void testSigned(qc::Random<G> & random)
    {
        for (unat i{0u}; i < n; ++i)
        {
            {
                #pragma warning(suppress: 4189)
                const T v{random.template next<T>()};
            }

            {
                const T v{random.template next<T>(0)};
                ASSERT_EQ(v, 0);
            }

            {
                const T v{random.template next<T>(1)};
                ASSERT_EQ(v, 0);
            }

            {
                const T v{random.template next<T>(2)};
                ASSERT_GE(v, 0);
                ASSERT_LT(v, 2);
            }

            {
                const T v{random.template next<T>(3)};
                ASSERT_GE(v, 0);
                ASSERT_LT(v, 3);
            }

            {
                const T v{random.template next<T>(4)};
                ASSERT_GE(v, 0);
                ASSERT_LT(v, 4);
            }

            {
                const T v{random.template next<T>(5)};
                ASSERT_GE(v, 0);
                ASSERT_LT(v, 5);
            }

            {
                const T v{random.template next<T>(3u, 7u)};
                ASSERT_GE(v, 3u);
                ASSERT_LT(v, 7u);
            }
        }
    }

    template <typename T, typename G>
    void testFloating(qc::Random<G> & random)
    {
        for (unat i{0u}; i < n; ++i)
        {
            {
                const T v{random.template next<T>()};
                ASSERT_GE(v, T(0.0));
                ASSERT_LT(v, T(1.0));
            }

            {
                const T v{random.template next<T>(T(3.25))};
                ASSERT_GE(v, T(0.0));
                ASSERT_LT(v, T(3.25));
            }

            {
                const T v{random.template next<T>(T(-3.25))};
                ASSERT_LE(v, T(0.0));
                ASSERT_GT(v, T(-3.25));
            }

            {
                const T v{random.template next<T>(T(3.25), T(7.75))};
                ASSERT_GE(v, T(3.25));
                ASSERT_LT(v, T(7.75));
            }

            {
                const T v{random.template next<T>(T(-3.25), T(-7.75))};
                ASSERT_LE(v, T(-3.25));
                ASSERT_GT(v, T(-7.75));
            }

            {
                const T v{random.template next<T>(T(-3.25), T(7.75))};
                ASSERT_GE(v, T(-3.25));
                ASSERT_LT(v, T(7.75));
            }

            {
                const T v{random.template next<T>(T(3.25), T(-7.75))};
                ASSERT_GE(v, T(-7.75));
                ASSERT_LT(v, T(3.25));
            }
        }
    }

    template <typename G>
    void testGeneratorType()
    {
        qc::Random<G> random{};

        random.template next<bool>();

        random.next();
        random.next(10u);
        random.next(10u, 20u);

        testUnsigned<u8>(random);
        testUnsigned<u16>(random);
        testUnsigned<u32>(random);
        testUnsigned<u64>(random);

        testSigned<s8>(random);
        testSigned<s16>(random);
        testSigned<s32>(random);
        testSigned<s64>(random);

        testFloating<f32>(random);
        testFloating<f64>(random);
    }
}

TEST(Random, types)
{
    testGeneratorType<u8>();
    testGeneratorType<u16>();
    testGeneratorType<u32>();
    testGeneratorType<u64>();
}

TEST(Random, seed)
{
    qc::Random r1{0u};
    ASSERT_EQ(r1.seed(), 0u);

    qc::Random r2{17u};
    ASSERT_EQ(r2.seed(), 17u);

    ASSERT_NE(r1.next(), r2.next());

    qc::Random r3{};
    qc::Random r4{};

    ASSERT_NE(r3.seed(), r4.seed());
}
