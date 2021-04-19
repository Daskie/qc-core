#pragma once

#include <qc-core/vector-ext.hpp>

namespace qc {

    namespace color {

        template <typename T> inline const vec3<T> black    {transnorm<vec3<T>>(dvec3{0.00, 0.00, 0.00})};
        template <typename T> inline const vec3<T> darkGray {transnorm<vec3<T>>(dvec3{0.25, 0.25, 0.25})};
        template <typename T> inline const vec3<T> gray     {transnorm<vec3<T>>(dvec3{0.50, 0.50, 0.50})};
        template <typename T> inline const vec3<T> lightGray{transnorm<vec3<T>>(dvec3{0.75, 0.75, 0.75})};
        template <typename T> inline const vec3<T> white    {transnorm<vec3<T>>(dvec3{1.00, 1.00, 1.00})};

        template <typename T> inline const vec3<T> red      {transnorm<vec3<T>>(dvec3{1.00, 0.00, 0.00})};
        template <typename T> inline const vec3<T> yellow   {transnorm<vec3<T>>(dvec3{1.00, 1.00, 0.00})};
        template <typename T> inline const vec3<T> green    {transnorm<vec3<T>>(dvec3{0.00, 1.00, 0.00})};
        template <typename T> inline const vec3<T> cyan     {transnorm<vec3<T>>(dvec3{0.00, 1.00, 1.00})};
        template <typename T> inline const vec3<T> blue     {transnorm<vec3<T>>(dvec3{0.00, 0.00, 1.00})};
        template <typename T> inline const vec3<T> magenta  {transnorm<vec3<T>>(dvec3{1.00, 0.00, 1.00})};

    }

    template <Floating T>
    inline vec3<T> srgbToHsl(const vec3<T> & srgb) {
        vec3<T> hsl{};

        int maxI{srgb.y > srgb.x};
        int minI{1 - maxI};
        if (srgb.z > srgb[maxI]) maxI = 2;
        else if (srgb.z < srgb[minI]) minI = 2;
        const T maxComp{srgb[maxI]};
        const T minComp{srgb[minI]};

        // Lightness
        hsl.z = (minComp + maxComp) * T(0.5);

        if (hsl.z > T(0.0) && hsl.z < T(1.0)) {
            const T compRange{maxComp - minComp};

            // Saturation
            if (hsl.z > T(0.5)) {
                hsl.y = compRange / (T(2.0) - (hsl.z * T(2.0)));
            }
            else {
                hsl.y = compRange / (hsl.z * T(2.0));
            }

            if (hsl.y > T(0.0)) {
                // Hue
                // TODO: Test if this is acually faster than the two `% 3`s
                const T overflowRgb[5]{srgb.x, srgb.y, srgb.z, srgb.x, srgb.y};
                hsl.x = T(maxI * 2 + 6);
                hsl.x += (overflowRgb[maxI + 1] - overflowRgb[maxI + 2]) / compRange;
                hsl.x = fract(hsl.x * T(1.0 / 6.0));
            }
        }

        return hsl;
    }

    template <Floating T>
    inline vec3<T> _hueToSrgb(const T hue, const T minComp, const T maxComp) {
        const auto [fraction, whole]{fract_i(hue * T(6.0))};
        const T midOffset{(maxComp - minComp) * fraction};
        switch (whole) {
            default: return {maxComp, minComp + midOffset, minComp};
            case  1: return {maxComp - midOffset, maxComp, minComp};
            case  2: return {minComp, maxComp, minComp + midOffset};
            case  3: return {minComp, maxComp - midOffset, maxComp};
            case  4: return {minComp + midOffset, minComp, maxComp};
            case  5: return {maxComp, minComp, maxComp - midOffset};
        }
    }

    template <Floating T>
    inline vec3<T> hueToSrgb(const T hue) {
        return _hueToSrgb(hue, T(0.0), T(1.0));
    }

    //
    // There is a desmos graph for this
    //
    template <Floating T>
    inline vec3<T> hslToSrgb(const vec3<T> & hsl) {
        const T maxSpread{T(0.5) - qc::abs(hsl.z - T(0.5))};
        const T spread{maxSpread * hsl.y};
        const T minComp{hsl.z - spread};
        const T maxComp{hsl.z + spread};
        return _hueToSrgb(hsl.x, minComp, maxComp);
    }

    //
    //
    //
    template <Floating T>
    inline vec3<T> thermalToSrgb(const T thermal) {
        T r1{T(1.09) * (thermal - T(1.0))};
        r1 *= r1;
        constexpr T b0{T(0.885)};
        constexpr T b1{b0 * b0 * b0 * b0};
        T b2{T(3.7) * thermal - b0};
        b2 *= b2;

        return {
            T(1.0) - r1 * r1,
            T(1.6) * thermal - T(0.5),
            thermal < T(0.5) ? b1 - b2 * b2 : T(6.5) * thermal - T(5.5)
        };
    }

    // GPU (saved for later)
    /*vec3 hsv2rgb(vec3 c) {
        vec4 K = vec4(1.0f, 2.0f / 3.0f, 1.0f / 3.0f, 3.0f);
        vec3 p = abs(fract(c.xxx + K.xyz) * 6.0f - K.www);
        return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
    }
    vec3 hue2rgb(float h) {
        vec3 p = abs(fract(h + vec3(1.0f, 2.0f / 3.0f, 1.0f / 3.0f)) * 6.0f - 3.0f);
        return clamp(p - 1.0f, 0.0, 1.0);
    }
    vec3 hue2rgb_flat(float h) {
        vec3 rgb = hue2rgb(h);
        vec3 temp = rgb * vec3(0.546808925f, 0.766159252f, 0.337638860f);
        float pb = sqrt(dot(temp, temp));
        return rgb * (0.337638860f / pb);
    }
    // l: luminance [0, 1]
    // uv: point in color space [-1, 1]
    vec3 luv2rgb(vec3 luv) {
        const mat3 m = mat3( // XYZ -> sRGB conversion matrix
             3.2404542f, -0.9692660f,  0.0556434f,
            -1.5371385f,  1.8760108f, -0.2040259f,
            -0.4985314f,  0.0415560f,  1.0572252f
         );
        const vec2 uv0 = vec2(0.197833037f, 0.468330474f); // coords for D65 white point
        vec2 uv = uv0 + luv.yz / (13.0f * luv.x);
        vec3 xyz;
        if (luv.x > 0.08f) {
            xyz.y = 0.862068966f * luv.x + 0.137931034f;
            xyz.y *= xyz.y * xyz.y;
        }
        else {
            xyz.y = 0.110705646f * luv.x;
        }
        xyz.x = 2.25f * xyz.y * uv.x / uv.y;
        xyz.z = (3.0f / uv.y - 5.0f) * xyz.y - (1.0f / 3.0f) * xyz.x;
        return m * xyz;
    }
    // l: luminance [0, 1]
    // c: chroma (similar to saturation) [0, 1]
    // h: hue [0, 1]
    vec3 lch2luv(vec3 lch) {
        lch.z *= 2.0f * pi;
        return luv2rgb(vec3(lch.x, lch.y * cos(lch.z), lch.y * sin(lch.z)));
    }*/

} // namespace qc
