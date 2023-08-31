#include <qc-core/color.hpp>

#include <gtest/gtest.h>

using namespace qc::types;
using namespace qc::primitives;

static fvec3 _truncate(const fvec3 & val)
{
    return fvec3{ivec3{val * 1000.0f}} * 0.001f;
}

template <Numeric T>
static void _instantiateColors()
{
    constexpr vec3<T> black{qc::color::black<T>};
    constexpr vec3<T> darkGray{qc::color::darkGray<T>};
    constexpr vec3<T> gray{qc::color::gray<T>};
    constexpr vec3<T> lightGray{qc::color::lightGray<T>};

    constexpr vec3<T> red{qc::color::red<T>};
    constexpr vec3<T> yellow{qc::color::yellow<T>};
    constexpr vec3<T> green{qc::color::green<T>};
    constexpr vec3<T> cyan{qc::color::cyan<T>};
    constexpr vec3<T> blue{qc::color::blue<T>};
    constexpr vec3<T> magenta{qc::color::magenta<T>};
}

TEST(Color, colors)
{
    _instantiateColors<f32>();
    _instantiateColors<f64>();
    _instantiateColors<s8>();
    _instantiateColors<s16>();
    _instantiateColors<s32>();
    _instantiateColors<s64>();
    _instantiateColors<u8>();
    _instantiateColors<u16>();
    _instantiateColors<u32>();
    _instantiateColors<u64>();
}

TEST(Color, srgbToHsl)
{
    ASSERT_EQ(_truncate(fvec3{0.0f, 0.0f, 0.0f}), _truncate(qc::color::srgbToHsl(fvec3{0.0f, 0.0f, 0.0f})));
    for (f32 v{0.25f}; v <= 1.0f; v += 0.25f)
    {
        const f32 l{v * 0.5f};
        ASSERT_EQ(_truncate(fvec3{0.0f / 6.0f, 1.0f, l}), _truncate(qc::color::srgbToHsl(fvec3{v, 0.0f, 0.0f})));
        ASSERT_EQ(_truncate(fvec3{1.0f / 6.0f, 1.0f, l}), _truncate(qc::color::srgbToHsl(fvec3{v, v, 0.0f})));
        ASSERT_EQ(_truncate(fvec3{2.0f / 6.0f, 1.0f, l}), _truncate(qc::color::srgbToHsl(fvec3{0.0f, v, 0.0f})));
        ASSERT_EQ(_truncate(fvec3{3.0f / 6.0f, 1.0f, l}), _truncate(qc::color::srgbToHsl(fvec3{0.0f, v, v})));
        ASSERT_EQ(_truncate(fvec3{4.0f / 6.0f, 1.0f, l}), _truncate(qc::color::srgbToHsl(fvec3{0.0f, 0.0f, v})));
        ASSERT_EQ(_truncate(fvec3{5.0f / 6.0f, 1.0f, l}), _truncate(qc::color::srgbToHsl(fvec3{v, 0.0f, v})));
        ASSERT_EQ(_truncate(fvec3{0.0f, 0.0f, v}), _truncate(qc::color::srgbToHsl(fvec3{v, v, v})));
    }

    ASSERT_EQ(_truncate(fvec3{0.804f, 0.932f, 0.510f}), _truncate(qc::color::srgbToHsl(fvec3{0.811f, 0.053f, 0.967f})));
}

TEST(Color, hslToSrgb)
{
    ASSERT_EQ(_truncate(fvec3{0.0f, 0.0f, 0.0f}), _truncate(qc::color::hslToSrgb(fvec3{0.0f, 0.0f, 0.0f})));
    for (f32 v{0.25f}; v <= 1.0f; v += 0.25f)
    {
        const f32 l{v * 0.5f};
        ASSERT_EQ(_truncate(fvec3{v, 0.0f, 0.0f}), _truncate(qc::color::hslToSrgb(fvec3{0.0f / 6.0f, 1.0f, l})));
        ASSERT_EQ(_truncate(fvec3{v, v, 0.0f}), _truncate(qc::color::hslToSrgb(fvec3{1.0f / 6.0f, 1.0f, l})));
        ASSERT_EQ(_truncate(fvec3{0.0f, v, 0.0f}), _truncate(qc::color::hslToSrgb(fvec3{2.0f / 6.0f, 1.0f, l})));
        ASSERT_EQ(_truncate(fvec3{0.0f, v, v}), _truncate(qc::color::hslToSrgb(fvec3{3.0f / 6.0f, 1.0f, l})));
        ASSERT_EQ(_truncate(fvec3{0.0f, 0.0f, v}), _truncate(qc::color::hslToSrgb(fvec3{4.0f / 6.0f, 1.0f, l})));
        ASSERT_EQ(_truncate(fvec3{v, 0.0f, v}), _truncate(qc::color::hslToSrgb(fvec3{5.0f / 6.0f, 1.0f, l})));
        ASSERT_EQ(_truncate(fvec3{v, v, v}), _truncate(qc::color::hslToSrgb(fvec3{0.0f, 0.0f, v})));
    }

    ASSERT_EQ(_truncate(fvec3{0.805f, 0.053f, 0.966f}), _truncate(qc::color::hslToSrgb(fvec3{0.804f, 0.932f, 0.510f})));
}

TEST(Color, rgbToHslAndBack)
{
    for (ivec3 rgb{0, 0, 0}; rgb.z < 256; ++rgb.z)
    {
        for (rgb.y = 0; rgb.y < 256; ++rgb.y)
        {
            for (rgb.x = 0; rgb.x < 256; ++rgb.x)
            {
                const fvec3 hsl{qc::color::srgbToHsl(qc::transnorm<f32>(ucvec3{rgb}))};
                const ivec3 rgbNew{qc::transnorm<u8>(qc::color::hslToSrgb(hsl))};
                ASSERT_EQ(rgb, rgbNew);
            }
        }
    }
}
