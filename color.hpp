#pragma once

#include "vector.hpp"

namespace qc::core {

    namespace color {

        template <typename T, typename From> constexpr vec3<T> custom(const vec3<From> & color) { return transnorm<T>(color); }
        template <typename T, typename From> constexpr vec3<T> custom(From r, From g, From b) { return custom<T>(vec3<From>(r, g, b)); }

        template <typename T> constexpr vec3<T>     black = custom<T>(0.00, 0.00, 0.00);
        template <typename T> constexpr vec3<T>  darkGray = custom<T>(0.25, 0.25, 0.25);
        template <typename T> constexpr vec3<T>      gray = custom<T>(0.50, 0.50, 0.50);
        template <typename T> constexpr vec3<T> lightGray = custom<T>(0.75, 0.75, 0.75);
        template <typename T> constexpr vec3<T>     white = custom<T>(1.00, 1.00, 1.00);

        template <typename T> constexpr vec3<T>       red = custom<T>(1.00, 0.00, 0.00);
        template <typename T> constexpr vec3<T>    yellow = custom<T>(1.00, 1.00, 0.00);
        template <typename T> constexpr vec3<T>     green = custom<T>(0.00, 1.00, 0.00);
        template <typename T> constexpr vec3<T>      cyan = custom<T>(0.00, 1.00, 1.00);
        template <typename T> constexpr vec3<T>      blue = custom<T>(0.00, 0.00, 1.00);
        template <typename T> constexpr vec3<T>   magenta = custom<T>(1.00, 0.00, 1.00);

    }

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
        const mat3 k_m = mat3( // XYZ -> sRGB conversion matrix
             3.2404542f, -0.9692660f,  0.0556434f,
            -1.5371385f,  1.8760108f, -0.2040259f,
            -0.4985314f,  0.0415560f,  1.0572252f
         );
        const vec2 k_uv0 = vec2(0.197833037f, 0.468330474f); // coords for D65 white point
        vec2 uv = k_uv0 + luv.yz / (13.0f * luv.x);
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
        return k_m * xyz;
    }
    // l: luminance [0, 1]
    // c: chroma (similar to saturation) [0, 1]
    // h: hue [0, 1]
    vec3 lch2luv(vec3 lch) {
        lch.z *= 2.0f * k_pi;
        return luv2rgb(vec3(lch.x, lch.y * cos(lch.z), lch.y * sin(lch.z)));
    }*/

    template <Floater T>
    inline vec3<T> rgb2hsl(const vec3<T> & rgb) {
        vec3<T> hsl(0, 0, 0);

        int minI(rgb.r <= rgb.g ? 0 : 1);
        if (rgb.b < rgb[minI]) minI = 2;
        int maxI(rgb.r >= rgb.g ? 0 : 1);
        if (rgb.b > rgb[maxI]) maxI = 2;

        // lightness
        hsl.z = (rgb[minI] + rgb[maxI]) * T(0.5);

        if (hsl.z > 0 && hsl.z < T(1.0)) {
            // saturation
            if (hsl.z > T(0.5)) {
                hsl.y = (rgb[maxI] - rgb[minI]) / (T(2.0) - (hsl.z * T(2.0)));
            }
            else {
                hsl.y = (rgb[maxI] - rgb[minI]) / (hsl.z * T(2.0));
            }

            if (hsl.y > 0) {
                // hue
                hsl.x = maxI * T(1.0 / 3.0);
                hsl.x += (rgb[(maxI + 1) % 3] - rgb[((maxI + 2) % 3)]) / (rgb[maxI] - rgb[minI]) * T(1.0 / 6.0);
                hsl.x += T(1.0);
                hsl.x -= std::floor(hsl.x);
            }
        }

        return hsl;
    }

    template <Floater T>
    inline vec3<T> hsl2rgb(const vec3<T> & hsl) {
        if (hsl.y == 0) {
            return {hsl.z, hsl.z, hsl.z};
        }

        vec3<T> rgb(0, 0, 0);
        T temp;

        // hue
        temp = std::round(hsl.x * T(3.0));
        int maxI(int(temp) % 3);
        rgb[maxI] = T(1.0);
        T secondaryWeight((hsl.x * T(3.0) - temp) * T(2.0));
        int midI((maxI + int(secondaryWeight > 0 ? std::ceil(secondaryWeight) : std::floor(secondaryWeight)) + 3) % 3);
        rgb[midI] = abs(secondaryWeight);

        // saturation
        temp = T(1.0) - hsl.y;
        rgb.r += (T(0.5) - rgb.r) * temp;
        rgb.g += (T(0.5) - rgb.g) * temp;
        rgb.b += (T(0.5) - rgb.b) * temp;

        // lightness
        temp = (hsl.z - T(0.5)) * T(2.0);
        if (hsl.z > T(0.5)) {
            rgb.r += (T(1.0) - rgb.r) * temp;
            rgb.g += (T(1.0) - rgb.g) * temp;
            rgb.b += (T(1.0) - rgb.b) * temp;
        }
        else {
            rgb.r += rgb.r * temp;
            rgb.g += rgb.g * temp;
            rgb.b += rgb.b * temp;
        }

        return rgb;
    }

}
