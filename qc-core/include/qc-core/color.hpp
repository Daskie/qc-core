#pragma once

///
/// Colorspaces
///
/// sRGB (standard RGB):
///   - Non-linear
///   - Gamma 2.2
///   - Components:
///     - R (Red)   : [0, 1]
///     - G (Green) : [0, 1]
///     - B (Blue)  : [0, 1]
///
/// lRGB (linear RGB):
///   - Components:
///     -  R (red)   : [0, inf)
///     -  G (green) : [0, inf)
///     -  B (blue)  : [0, inf)
///
/// HSL:
///   - Components:
///     - H (Hue)        : [0, 1]
///     - S (Saturation) : [0, 1]
///     - L (Lightness)  : [0, 1]
///
/// CIE XYZ:
///   - "foundational" linear color space
///   - Components:
///     - X : (-inf, inf)
///     - Y : (-inf, inf)
///     - Z : (-inf, inf)
///
/// CIE xyY:
///   - CIE XYZ normalized to uniform brightness
///   - Components:
///     - x : (-inf, inf)
///     - y : (-inf, inf)
///     - Y : (-inf, inf)
///
/// CIE LAB:
///   - Good perceptual uniformity in print and physical media
///   - Components:
///     - L : [0, 1]
///     - a : (-inf, inf)
///     - b : (-inf, inf)
///
/// CIE LUV:
///   - Good perceptual uniformity for light and digital displays
///   - Components:
///     - L : [0, 1]
///     - u : (-inf, inf)
///     - v : (-inf, inf)
///
/// CIE LCH (UV):
///   - Hue-chroma form of CIE LUV
///   - Components:
///     - L: [0, 1]
///     - C: [0, inf)
///     - h: [0, 1]
///

#include <qc-core/vector-ext.hpp>
#include <qc-core/matrix.hpp>

namespace qc::color
{
    template <Numeric T> constexpr vec3<T> black    {transnorm<T>(dvec3{0.00, 0.00, 0.00})};
    template <Numeric T> constexpr vec3<T> darkGray {transnorm<T>(dvec3{0.25, 0.25, 0.25})};
    template <Numeric T> constexpr vec3<T> gray     {transnorm<T>(dvec3{0.50, 0.50, 0.50})};
    template <Numeric T> constexpr vec3<T> lightGray{transnorm<T>(dvec3{0.75, 0.75, 0.75})};
    template <Numeric T> constexpr vec3<T> white    {transnorm<T>(dvec3{1.00, 1.00, 1.00})};

    template <Numeric T> constexpr vec3<T> red      {transnorm<T>(dvec3{1.00, 0.00, 0.00})};
    template <Numeric T> constexpr vec3<T> yellow   {transnorm<T>(dvec3{1.00, 1.00, 0.00})};
    template <Numeric T> constexpr vec3<T> green    {transnorm<T>(dvec3{0.00, 1.00, 0.00})};
    template <Numeric T> constexpr vec3<T> cyan     {transnorm<T>(dvec3{0.00, 1.00, 1.00})};
    template <Numeric T> constexpr vec3<T> blue     {transnorm<T>(dvec3{0.00, 0.00, 1.00})};
    template <Numeric T> constexpr vec3<T> magenta  {transnorm<T>(dvec3{1.00, 0.00, 1.00})};

    ///
    /// Converts a color from sRGB to lRGB
    /// @param srgb color to convert
    /// @return converted color
    ///
    template <Floating T>
    nodisc inline vec3<T> srgbToLrgb(const vec3<T> & srgb)
    {
        return pow(srgb, T(2.2));
    }

    ///
    /// Converts a color from lRGB to sRGB
    /// @param lrgb color to convert, must be positive
    /// @return converted color
    ///
    template <Floating T>
    nodisc inline vec3<T> lrgbToSrgb(const vec3<T> & lrgb)
    {
        return pow(lrgb, T(1.0 / 2.2));
    }

    ///
    /// Converts from sRGB to HSL
    /// @param srgb sRGB value to convert
    /// @return converted HSL value
    ///
    template <Floating T>
    nodisc inline vec3<T> srgbToHsl(const vec3<T> & srgb)
    {
        vec3<T> hsl{};

        u32 maxI{srgb.y > srgb.x};
        u32 minI{1u - maxI};
        if (srgb.z > srgb[maxI]) maxI = 2u;
        else if (srgb.z < srgb[minI]) minI = 2u;
        const T maxComp{srgb[maxI]};
        const T minComp{srgb[minI]};

        // Lightness
        hsl.z = (minComp + maxComp) * T(0.5);

        if (hsl.z > T(0.0) && hsl.z < T(1.0))
        {
            const T compRange{maxComp - minComp};

            // Saturation
            if (hsl.z > T(0.5))
            {
                hsl.y = compRange / (T(2.0) - (hsl.z * T(2.0)));
            }
            else
            {
                hsl.y = compRange / (hsl.z * T(2.0));
            }

            if (hsl.y > T(0.0))
            {
                // Hue
                // TODO: Test if this is acually faster than the two `% 3`s
                const T overflowRgb[5]{srgb.x, srgb.y, srgb.z, srgb.x, srgb.y};
                hsl.x = T(maxI * 2u + 6u);
                hsl.x += (overflowRgb[maxI + 1] - overflowRgb[maxI + 2u]) / compRange;
                hsl.x = fract(hsl.x * T(1.0 / 6.0));
            }
        }

        return hsl;
    }

    namespace _minutia
    {
        template <Floating T>
        nodisc inline vec3<T> hueToSrgb(const T hue, const T minComp, const T maxComp)
        {
            const auto [fraction, whole]{fract_i<s64>(hue * T(6.0))};
            const T midOffset{(maxComp - minComp) * fraction};
            switch (whole)
            {
                default: return {maxComp, minComp + midOffset, minComp};
                case 1: return {maxComp - midOffset, maxComp, minComp};
                case 2: return {minComp, maxComp, minComp + midOffset};
                case 3: return {minComp, maxComp - midOffset, maxComp};
                case 4: return {minComp + midOffset, minComp, maxComp};
                case 5: return {maxComp, minComp, maxComp - midOffset};
            }
        }
    }

    ///
    /// Get the sRGB color for a given hue
    /// @param hue hue in range [0, 1]
    /// @return full value/saturated sRGB corresponding to `hue`
    ///
    template <Floating T>
    nodisc inline vec3<T> hueToSrgb(const T hue)
    {
        return _minutia::hueToSrgb(hue, T(0.0), T(1.0));
    }

    ///
    /// Converts a color from HSL to sRGB
    /// There is a desmos graph for this
    /// @param hsl color to convert
    /// @return converted color
    ///
    template <Floating T>
    nodisc inline vec3<T> hslToSrgb(const vec3<T> & hsl)
    {
        const T maxSpread{T(0.5) - qc::abs(hsl.z - T(0.5))};
        const T spread{maxSpread * hsl.y};
        const T minComp{hsl.z - spread};
        const T maxComp{hsl.z + spread};
        return _minutia::hueToSrgb(hsl.x, minComp, maxComp);
    }

    ///
    /// Return a sRGB color correpsonding to a "thermal" value, in range [0, 1]
    /// The spectrum goes roughly black -> blue -> purple -> magenta -> red -> orange -> yellow -> white
    /// Using interpolation of ironbow palette
    /// @param v input "temperature" in range [0, 1]
    /// @return gradient sRGB value
    ///
    template <Floating T>
    nodisc inline vec3<T> thermalToSrgb(const T v)
    {
        static constexpr vec3<T> palette[12u]{
            transnorm<T>(ucvec3{u8(  0u), u8(  0u), u8(  0u)}),
            transnorm<T>(ucvec3{u8( 33u), u8(  0u), u8(133u)}),
            transnorm<T>(ucvec3{u8(110u), u8(  0u), u8(156u)}),
            transnorm<T>(ucvec3{u8(175u), u8(  1u), u8(152u)}),
            transnorm<T>(ucvec3{u8(208u), u8( 26u), u8(121u)}),
            transnorm<T>(ucvec3{u8(231u), u8( 72u), u8( 20u)}),
            transnorm<T>(ucvec3{u8(243u), u8(113u), u8(  1u)}),
            transnorm<T>(ucvec3{u8(252u), u8(159u), u8(  0u)}),
            transnorm<T>(ucvec3{u8(254u), u8(205u), u8(  2u)}),
            transnorm<T>(ucvec3{u8(255u), u8(239u), u8(102u)}),
            transnorm<T>(ucvec3{u8(255u), u8(255u), u8(255u)}),
            transnorm<T>(ucvec3{u8(255u), u8(255u), u8(255u)})};

        const auto [t, i]{qc::fract_i<s32>(v * T(10.0))};
        return mix(palette[i], palette[i + 1], t);
    }

    ///
    /// D65, see: http://terathon.com/blog/rgb-xyz-conversion-matrix-accuracy/
    ///
    template <Floating T> inline constexpr mat3<T> lrgbToXyzMatrix{
        T(506752.0 / 1228815.0), T(87098.0 / 409605.0), T(7918.0 / 409605.0),
        T(87881.0 / 245763.0), T(175762.0 / 245763.0), T(87881.0 / 737289.0),
        T(12673.0 / 70218.0), T(12673.0 / 175545.0), T(1001167.0 / 1053270.0)};

    template <Floating T> inline constexpr mat3<T> xyzToLrgbMatrix{
        T(12831.0 / 3959.0), T(-851781.0 / 878810.0), T(705.0 / 12673.0),
        T(-329.0 / 214.0), T(1648619.0 / 878810.0), T(-2585.0 / 12673.0),
        T(-1974.0 / 3959.0), T(36519.0 / 878810.0), T(705.0 / 667.0)};

    ///
    /// The XYZ value of D65 white
    ///
    template <Floating T> inline constexpr vec3<T> xyzWhitePoint{lrgbToXyzMatrix<T> * vec3<T>{T(1.0)}};

    ///
    /// Converts a color from lRGB to XYZ
    /// @param lrgb color to convert
    /// @return converted color
    template <Floating T>
    nodisc inline vec3<T> lrgbToXyz(const vec3<T> & lrgb)
    {
        return lrgbToXyzMatrix<T> * lrgb;
    }

    ///
    /// Converts a color from XYZ to lRGB
    /// @param xyz color to convert
    /// @return converted color
    ///
    template <Floating T>
    nodisc inline vec3<T> xyzToLrgb(const vec3<T> & xyz)
    {
        return xyzToLrgbMatrix<T> * xyz;
    }

    ///
    /// Converts a color from XYZ to xyY
    /// @param xyz color to convert
    /// @return converted color
    ///
    template <Floating T>
    nodisc inline vec3<T> xyzToXyy(const vec3<T> & xyz)
    {
        const T temp{sum(xyz)};
        if (temp)
        {
            return {xyz.xy() / temp, xyz.y};
        }
        else
        {
            return {T(1.0 / 3.0), T(1.0 / 3.0), 0.0f};
        }
    }

    ///
    /// Converts a color from xyY to XYZ
    /// @param xyy color to convert
    /// @return converted color
    ///
    template <Floating T>
    nodisc inline vec3<T> xyyToXyz(const vec3<T> & xyy)
    {
        const T temp{xyy.z / xyy.y};
        return {temp * xyy.x, xyy.z, temp * (T(1.0) - xyy.x - xyy.y)};
    }

    ///
    /// Converts a color from XYZ to LAB
    /// @param xyz color to convert
    /// @return converted color
    ///
    template <Floating T>
    nodisc inline vec3<T> xyzToLab(const vec3<T> & xyz)
    {
        static const vec3<T> invWhitePoint{T(1.0) / xyzWhitePoint<T>};

        // Not doing piecewise approximation
        const vec3<T> normalized{xyz * invWhitePoint};
        const T cbrtNY{std::cbrt(normalized.y)};
        return {
            cbrtNY,
            T(5.0) * (std::cbrt(normalized.x) - cbrtNY),
            T(2.0) * (cbrtNY - std::cbrt(normalized.z))};
    }

    ///
    /// Converts a color from LAB to XYZ
    /// @param lab color to convert
    /// @return converted color
    ///
    template <Floating T>
    nodisc inline vec3<T> labToXyz(const vec3<T> & lab)
    {
        // Not doing piecewise approximation
        const vec3<T> xyz{
            lab.x + lab.y * T(0.2),
            lab.x,
            lab.x - lab.z * T(0.5)};

        return xyz * xyz * xyz * xyzWhitePoint<T>;
    }

    ///
    /// Converts a color from XYZ to LUV
    /// @param xyz color to convert
    /// @return converted color
    ///
    template <Floating T>
    nodisc inline vec3<T> xyzToLuv(const vec3<T> & xyz)
    {
        static constexpr T u_v_nDivisor{xyzWhitePoint<T>.x + T(15.0) * xyzWhitePoint<T>.y + T(3.0) * xyzWhitePoint<T>.z};
        static constexpr T u_n{T(4.0) * xyzWhitePoint<T>.x / u_v_nDivisor};
        static constexpr T v_n{T(9.0) * xyzWhitePoint<T>.y / u_v_nDivisor};
        static constexpr T invYn{T(1.0) / xyzWhitePoint<T>.y};

        // Not doing piecewise approximation
        if (xyz)
        {
            const T l{std::cbrt(xyz.y * invYn)};
            const T _13l{T(13.0) * l};
            const T uvFactor{T(1.0) / (xyz.x + T(15.0) * xyz.y + T(3.0) * xyz.z)};
            const T u_{T(4.0) * xyz.x * uvFactor};
            const T v_{T(9.0) * xyz.y * uvFactor};
            const T u{_13l * (u_ - u_n)};
            const T v{_13l * (v_ - v_n)};
            return {l, u, v};
        }
        else
        {
            return {};
        }
    }

    ///
    /// Converts a color from LUV to XYZ
    /// @param luv color to convert
    /// @return converted color
    ///
    template <Floating T>
    nodisc inline vec3<T> luvToXyz(const vec3<T> & luv)
    {
        static constexpr T u_v_nDivisor{xyzWhitePoint<T>.x + T(15.0) * xyzWhitePoint<T>.y + T(3.0) * xyzWhitePoint<T>.z};
        static constexpr T u_n{T(4.0) * xyzWhitePoint<T>.x / u_v_nDivisor};
        static constexpr T v_n{T(9.0) * xyzWhitePoint<T>.y / u_v_nDivisor};

        // Not doing piecewise approximation
        if (luv.x)
        {
            const T inv13L{T(1.0) / (T(13.0) * luv.x)};
            const T u_{luv.y * inv13L + u_n};
            const T v_{luv.z * inv13L + v_n};
            const T y{xyzWhitePoint<T>.y * luv.x * luv.x * luv.x};
            const T inv4v_{T(1.0) / (T(4.0) * v_)};
            const T x{y * T(9.0) * u_ * inv4v_};
            const T z{y * (T(12.0) - T(3.0) * u_ - T(20.0) * v_) * inv4v_};
            return {x, y, z};
        }
        else
        {
            return {};
        }
    }

    ///
    /// Converts a color from LUV to LCH
    /// @param luv color to convert
    /// @return converted color
    ///
    template <Floating T>
    nodisc inline vec3<T> luvToLch(const vec3<T> & luv)
    {
        const T theta{std::atan2(luv.z, luv.y)};
        return {
            luv.x,
            magnitude(luv.yz()),
            theta * (T(1.0) / pi<T>) * T(0.5) + T(0.5)};
    }

    ///
    /// Converts a color from LCH to LUV
    /// @param lch color to convert
    /// @return converted color
    ///
    template <Floating T>
    nodisc inline vec3<T> lchToLuv(const vec3<T> & lch)
    {
        const T theta{(lch.z * T(2.0) - T(1.0)) * pi<T>};
        return {
            lch.x,
            std::cos(theta) * lch.y,
            std::sin(theta) * lch.y};
    }

    // GPU (saved for later)
    /*vec3 hsv2rgb(vec3 c)
    {
        vec4 K = vec4(1.0f, 2.0f / 3.0f, 1.0f / 3.0f, 3.0f);
        vec3 p = abs(fract(c.xxx + K.xyz) * 6.0f - K.www);
        return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
    }
    vec3 hue2rgb(float h)
    {
        vec3 p = abs(fract(h + vec3(1.0f, 2.0f / 3.0f, 1.0f / 3.0f)) * 6.0f - 3.0f);
        return clamp(p - 1.0f, 0.0, 1.0);
    }*/

}
