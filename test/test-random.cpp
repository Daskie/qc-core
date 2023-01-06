#include <qc-core/random.hpp>

#include <gtest/gtest.h>

using namespace qc::types;

namespace
{
    constexpr unat n{1000u};

    template <typename T>
    void testUnsigned(qc::Random & random)
    {
        for (unat i{0u}; i < n; ++i)
        {
            {
                #pragma warning(suppress: 4189)
                const T v{random.next<T>()};
            }

            {
                const T v{random.next<T>(0u)};
                ASSERT_EQ(v, 0u);
            }

            {
                const T v{random.next<T>(1u)};
                ASSERT_EQ(v, 0u);
            }

            {
                const T v{random.next<T>(2u)};
                ASSERT_LT(v, 2u);
            }

            {
                const T v{random.next<T>(3u)};
                ASSERT_LT(v, 3u);
            }

            {
                const T v{random.next<T>(4u)};
                ASSERT_LT(v, 4u);
            }

            {
                const T v{random.next<T>(5u)};
                ASSERT_LT(v, 5u);
            }

            {
                const T v{random.next<T>(3u, 7u)};
                ASSERT_GE(v, 3u);
                ASSERT_LT(v, 7u);
            }
        }
    }

    template <typename T>
    void testSigned(qc::Random & random)
    {
        for (unat i{0u}; i < n; ++i)
        {
            {
                #pragma warning(suppress: 4189)
                const T v{random.next<T>()};
            }

            {
                const T v{random.next<T>(0)};
                ASSERT_EQ(v, 0);
            }

            {
                const T v{random.next<T>(1)};
                ASSERT_EQ(v, 0);
            }

            {
                const T v{random.next<T>(2)};
                ASSERT_GE(v, 0);
                ASSERT_LT(v, 2);
            }

            {
                const T v{random.next<T>(3)};
                ASSERT_GE(v, 0);
                ASSERT_LT(v, 3);
            }

            {
                const T v{random.next<T>(4)};
                ASSERT_GE(v, 0);
                ASSERT_LT(v, 4);
            }

            {
                const T v{random.next<T>(5)};
                ASSERT_GE(v, 0);
                ASSERT_LT(v, 5);
            }

            {
                const T v{random.next<T>(3u, 7u)};
                ASSERT_GE(v, 3u);
                ASSERT_LT(v, 7u);
            }
        }
    }

    template <typename T>
    void testFloating(qc::Random & random)
    {
        for (unat i{0u}; i < n; ++i)
        {
            {
                const T v{random.next<T>()};
                ASSERT_GE(v, T(0.0));
                ASSERT_LT(v, T(1.0));
            }

            {
                const T v{random.next<T>(T(3.25))};
                ASSERT_GE(v, T(0.0));
                ASSERT_LT(v, T(3.25));
            }

            {
                const T v{random.next<T>(T(-3.25))};
                ASSERT_LE(v, T(0.0));
                ASSERT_GT(v, T(-3.25));
            }

            {
                const T v{random.next<T>(T(3.25), T(7.75))};
                ASSERT_GE(v, T(3.25));
                ASSERT_LT(v, T(7.75));
            }

            {
                const T v{random.next<T>(T(-3.25), T(-7.75))};
                ASSERT_LE(v, T(-3.25));
                ASSERT_GT(v, T(-7.75));
            }

            {
                const T v{random.next<T>(T(-3.25), T(7.75))};
                ASSERT_GE(v, T(-3.25));
                ASSERT_LT(v, T(7.75));
            }

            {
                const T v{random.next<T>(T(3.25), T(-7.75))};
                ASSERT_GE(v, T(-7.75));
                ASSERT_LT(v, T(3.25));
            }
        }
    }
}

TEST(Random, types)
{
    qc::Random random{};

    random.next<bool>();

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
