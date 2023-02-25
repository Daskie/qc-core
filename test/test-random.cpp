#include <qc-core/random.hpp>

#include <gtest/gtest.h>

using namespace qc::concepts;
using namespace qc::types;

namespace
{
    template <typename G, typename T>
    void compileNext()
    {
        qc::Random<G> r{};
        static_cast<void>(r.next<T>());
        static_cast<void>(r.next<T>(T{}));
        static_cast<void>(r.next<T>(T{}, T{}));
    }

    template <typename G>
    void compile()
    {
        static_assert(std::is_same_v<typename qc::Random<G>::result_type, G>);
        static_cast<void>(qc::Random<G>::min());
        static_cast<void>(qc::Random<G>::max());

        qc::Random<G> r1{};
        qc::Random<G> r2{G{}};
        qc::Random<G> r3{r2};
        r1 = r2;
        static_cast<void>(r1());
        static_cast<void>(r1.next());
        static_cast<void>(r1.seed());

        compileNext<G, u8>();
        compileNext<G, u16>();
        compileNext<G, u32>();
        compileNext<G, u64>();
        compileNext<G, s8>();
        compileNext<G, s16>();
        compileNext<G, s32>();
        compileNext<G, s64>();
        compileNext<G, f32>();
        compileNext<G, f64>();
    }

    constexpr u64 n{1000u};

    template <typename T, typename G>
    void testUnsigned(qc::Random<G> & random)
    {
        static_cast<void>(random.template next<T>());

        {
            const T v{random.template next<T>(0u)};
            ASSERT_EQ(v, 0u);
        }

        {
            const T v{random.template next<T>(1u)};
            ASSERT_EQ(v, 0u);
        }

        u32 bits{};

        for (u64 i{0u}; i < n; ++i)
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
        for (u64 i{0u}; i < n; ++i)
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
        for (u64 i{0u}; i < n; ++i)
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

        static_cast<void>(random.template next<bool>());

        static_cast<void>(random.next());
        static_cast<void>(random.next(10u));
        static_cast<void>(random.next(10u, 20u));

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

TEST(Random, compile)
{
    compile<u8>();
    compile<u16>();
    compile<u32>();
    compile<u64>();
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
