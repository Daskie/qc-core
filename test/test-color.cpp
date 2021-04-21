#include <gtest/gtest.h>

#include <qc-core/color.hpp>

using namespace qc::types;

static fvec3 _truncate(const fvec3 & val) {
    return fvec3{ivec3{val * 1000.0f}} * 0.001f;
}

TEST(color, srgbToHsl) {
    EXPECT_EQ(_truncate(fvec3{0.0f, 0.0f, 0.0f}), _truncate(qc::color::srgbToHsl(fvec3{0.0f, 0.0f, 0.0f})));
    for (float v{0.25f}; v <= 1.0f; v += 0.25f) {
        const float l{v * 0.5f};
        EXPECT_EQ(_truncate(fvec3{0.0f / 6.0f, 1.0f, l}), _truncate(qc::color::srgbToHsl(fvec3{v, 0.0f, 0.0f})));
        EXPECT_EQ(_truncate(fvec3{1.0f / 6.0f, 1.0f, l}), _truncate(qc::color::srgbToHsl(fvec3{v, v, 0.0f})));
        EXPECT_EQ(_truncate(fvec3{2.0f / 6.0f, 1.0f, l}), _truncate(qc::color::srgbToHsl(fvec3{0.0f, v, 0.0f})));
        EXPECT_EQ(_truncate(fvec3{3.0f / 6.0f, 1.0f, l}), _truncate(qc::color::srgbToHsl(fvec3{0.0f, v, v})));
        EXPECT_EQ(_truncate(fvec3{4.0f / 6.0f, 1.0f, l}), _truncate(qc::color::srgbToHsl(fvec3{0.0f, 0.0f, v})));
        EXPECT_EQ(_truncate(fvec3{5.0f / 6.0f, 1.0f, l}), _truncate(qc::color::srgbToHsl(fvec3{v, 0.0f, v})));
        EXPECT_EQ(_truncate(fvec3{0.0f, 0.0f, v}), _truncate(qc::color::srgbToHsl(fvec3{v, v, v})));
    }

    EXPECT_EQ(_truncate(fvec3{0.804f, 0.932f, 0.510f}), _truncate(qc::color::srgbToHsl(fvec3{0.811f, 0.053f, 0.967f})));
}

TEST(color, hslToSrgb) {
    EXPECT_EQ(_truncate(fvec3{0.0f, 0.0f, 0.0f}), _truncate(qc::color::hslToSrgb(fvec3{0.0f, 0.0f, 0.0f})));
    for (float v{0.25f}; v <= 1.0f; v += 0.25f) {
        const float l{v * 0.5f};
        EXPECT_EQ(_truncate(fvec3{   v, 0.0f, 0.0f}), _truncate(qc::color::hslToSrgb(fvec3{0.0f / 6.0f, 1.0f, l})));
        EXPECT_EQ(_truncate(fvec3{   v,    v, 0.0f}), _truncate(qc::color::hslToSrgb(fvec3{1.0f / 6.0f, 1.0f, l})));
        EXPECT_EQ(_truncate(fvec3{0.0f,    v, 0.0f}), _truncate(qc::color::hslToSrgb(fvec3{2.0f / 6.0f, 1.0f, l})));
        EXPECT_EQ(_truncate(fvec3{0.0f,    v,    v}), _truncate(qc::color::hslToSrgb(fvec3{3.0f / 6.0f, 1.0f, l})));
        EXPECT_EQ(_truncate(fvec3{0.0f, 0.0f,    v}), _truncate(qc::color::hslToSrgb(fvec3{4.0f / 6.0f, 1.0f, l})));
        EXPECT_EQ(_truncate(fvec3{   v, 0.0f,    v}), _truncate(qc::color::hslToSrgb(fvec3{5.0f / 6.0f, 1.0f, l})));
        EXPECT_EQ(_truncate(fvec3{v, v, v}), _truncate(qc::color::hslToSrgb(fvec3{0.0f, 0.0f, v})));
    }

    EXPECT_EQ(_truncate(fvec3{0.805f, 0.053f, 0.966f}), _truncate(qc::color::hslToSrgb(fvec3{0.804f, 0.932f, 0.510f})));
}

TEST(color, rgbToHslAndBack) {
    for (ivec3 rgb{0, 0, 0}; rgb.z < 256; ++rgb.z) {
        for (rgb.y = 0; rgb.y < 256; ++rgb.y) {
            for (rgb.x = 0; rgb.x < 256; ++rgb.x) {
                const fvec3 hsl{qc::color::srgbToHsl(qc::transnorm<fvec3>(ucvec3{rgb}))};
                const ivec3 rgbNew{qc::transnorm<ucvec3>(qc::color::hslToSrgb(hsl))};
                EXPECT_EQ(rgb, rgbNew);
            }
        }
    }
}
