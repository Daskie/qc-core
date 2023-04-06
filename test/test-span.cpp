#include <qc-core/span-ext.hpp>

#include <sstream>

#include <gtest/gtest.h>

using namespace qc::types;
using namespace qc::primitives;

template <typename T>
static void compileClassesT()
{
    T v{};
    vec2<T> v2{};
    vec3<T> v3{};
    vec4<T> v4{};
    span1<T> s1{};
    span2<T> s2{};
    span3<T> s3{};
    span4<T> s4{};
    span1<T> s1_{};
    span2<T> s2_{};
    span3<T> s3_{};
    span4<T> s4_{};

    //--------------------------------------------------------------------------
    // Span1

    // constructors
    span<T, 1> s1_1{};
    span<T, 1> s1_2{s1};
    span<T, 1> s1_3{std::move(s1)};
    span<T, 1> s1_4{v, v};

    // assignment operators
    s1 = s1_;
    s1 = std::move(s1);

    // other
    static_cast<void>(s1.size());
    static_cast<void>(s1.contains(v));

    //--------------------------------------------------------------------------
    // Span2

    // constructors
    span<T, 2> s2_1{};
    span<T, 2> s2_2{s2};
    span<T, 2> s2_3{std::move(s2)};
    span<T, 2> s2_4{v2, v2};
    span<T, 2> s2_5{v, v2};
    span<T, 2> s2_6{v2, v};
    span<T, 2> s2_7{v, v};
    span<T, 2> s2_8{s1, s1};

    // assignment operators
    s2 = s2_;
    s2 = std::move(s2);

    // other
    static_cast<void>(s2.size());
    static_cast<void>(s2.x());
    static_cast<void>(s2.y());

    //--------------------------------------------------------------------------
    // Span3

    // constructors
    span<T, 3> s3_1{};
    span<T, 3> s3_2{s3};
    span<T, 3> s3_3{std::move(s3)};
    span<T, 3> s3_4{v3, v3};
    span<T, 3> s3_5{v, v3};
    span<T, 3> s3_6{v3, v};
    span<T, 3> s3_7{v, v};
    span<T, 3> s3_8{s1, s1, s1};
    span<T, 3> s3_9{s2, s1};
    span<T, 3> s3_10{s1, s2};

    // assignment operators
    s3 = s3_;
    s3 = std::move(s3);

    // other
    static_cast<void>(s3.size());
    static_cast<void>(s3.contains(v3));
    static_cast<void>(s3.x());
    static_cast<void>(s3.y());
    static_cast<void>(s3.z());
    static_cast<void>(s3.xy());
    static_cast<void>(s3.yz());

    //--------------------------------------------------------------------------
    // Span4

    // constructors
    span<T, 4> s4_1{};
    span<T, 4> s4_2{s4};
    span<T, 4> s4_3{std::move(s4)};
    span<T, 4> s4_4{v4, v4};
    span<T, 4> s4_5{v, v4};
    span<T, 4> s4_6{v4, v};
    span<T, 4> s4_7{v, v};
    span<T, 4> s4_8{s1, s1, s1, s1};
    span<T, 4> s4_9{s2, s1, s1};
    span<T, 4> s4_0{s1, s2, s1};
    span<T, 4> s4_11{s1, s1, s2};
    span<T, 4> s4_12{s2, s2};
    span<T, 4> s4_13{s3, s1};
    span<T, 4> s4_14{s1, s3};

    // assignment operators
    s4 = s4_;
    s4 = std::move(s4);

    // other
    static_cast<void>(s4.size());
    static_cast<void>(s4.contains(v4));
    static_cast<void>(s4.x());
    static_cast<void>(s4.y());
    static_cast<void>(s4.z());
    static_cast<void>(s4.w());
    static_cast<void>(s4.xy());
    static_cast<void>(s4.yz());
    static_cast<void>(s4.xyz());
    static_cast<void>(s4.yzw());
}

template <typename T>
static void compileClassesPT()
{
    using P = T *;
    using CP = const T *;
    P p{};
    CP cp{};
    span1<P> s1{};
    span1<CP> cs1{};
    span1<P> s1_{};
    span1<CP> cs1_{};

    // constructors
    {
        span<P, 1> s1_1{};
        span<P, 1> s1_2{s1};
        span<P, 1> s1_3{std::move(s1)};
        span<P, 1> s1_4{p, p};
    }
    // const constructors
    {
        span<CP, 1> s1_1{};
        span<CP, 1> s1_2{cs1};
        span<CP, 1> s1_3{s1};
        span<CP, 1> s1_4{std::move(cs1)};
        span<CP, 1> s1_5{std::move(s1)};
        span<CP, 1> s1_6{cp, cp};
        span<CP, 1> s1_7{p, p};
    }

    // assignment operators
    {
        s1 = s1_;
        s1 = std::move(s1);
    }
    // const assignment operators
    {
        cs1 = cs1_;
        cs1 = s1;
        cs1 = std::move(cs1);
        cs1 = std::move(s1);
    }

    // other
    static_cast<void>(s1.size());
}

static void compileClasses()
{
    compileClassesT<f32>();
    compileClassesT<f64>();
    compileClassesT<s8>();
    compileClassesT<s16>();
    compileClassesT<s32>();
    compileClassesT<s64>();
    compileClassesT<u8>();
    compileClassesT<u16>();
    compileClassesT<u32>();
    compileClassesT<u64>();

    compileClassesPT<std::byte>();
}

template <typename T>
static void compileFunctionsT()
{
    T v{1};
    vec2<T> v2{T(1)};
    vec3<T> v3{T(1)};
    vec4<T> v4{T(1)};
    span1<T> s1{};
    span2<T> s2{};
    span3<T> s3{};
    span4<T> s4{};
    span1<T> s1_{};
    span2<T> s2_{};
    span3<T> s3_{};
    span4<T> s4_{};
    std::stringstream os;

    s1 += v;
    s2 += v;
    s3 += v;
    s4 += v;

    s2 += v2;
    s3 += v3;
    s4 += v4;

    s1 -= v;
    s2 -= v;
    s3 -= v;
    s4 -= v;

    s2 -= v2;
    s3 -= v3;
    s4 -= v4;

    s1 *= v;
    s2 *= v;
    s3 *= v;
    s4 *= v;

    s2 *= v2;
    s3 *= v3;
    s4 *= v4;

    s1 /= v;
    s2 /= v;
    s3 /= v;
    s4 /= v;

    s2 /= v2;
    s3 /= v3;
    s4 /= v4;

    s1 &= s1_;
    s2 &= s2_;
    s3 &= s3_;
    s4 &= s4_;

    s1 |= s1_;
    s2 |= s2_;
    s3 |= s3_;
    s4 |= s4_;

    static_cast<void>(s1 + v);
    static_cast<void>(s2 + v);
    static_cast<void>(s3 + v);
    static_cast<void>(s4 + v);

    static_cast<void>(s2 + v2);
    static_cast<void>(s3 + v3);
    static_cast<void>(s4 + v4);

    static_cast<void>(v + s1);
    static_cast<void>(v + s2);
    static_cast<void>(v + s3);
    static_cast<void>(v + s4);

    static_cast<void>(v2 + s2);
    static_cast<void>(v3 + s3);
    static_cast<void>(v4 + s4);

    static_cast<void>(s1 - v);
    static_cast<void>(s2 - v);
    static_cast<void>(s3 - v);
    static_cast<void>(s4 - v);

    static_cast<void>(s2 - v2);
    static_cast<void>(s3 - v3);
    static_cast<void>(s4 - v4);

    static_cast<void>(v - s1);
    static_cast<void>(v - s2);
    static_cast<void>(v - s3);
    static_cast<void>(v - s4);

    static_cast<void>(v2 - s2);
    static_cast<void>(v3 - s3);
    static_cast<void>(v4 - s4);

    static_cast<void>(s1 * v);
    static_cast<void>(s2 * v);
    static_cast<void>(s3 * v);
    static_cast<void>(s4 * v);

    static_cast<void>(s2 * v2);
    static_cast<void>(s3 * v3);
    static_cast<void>(s4 * v4);

    static_cast<void>(v * s1);
    static_cast<void>(v * s2);
    static_cast<void>(v * s3);
    static_cast<void>(v * s4);

    static_cast<void>(v2 * s2);
    static_cast<void>(v3 * s3);
    static_cast<void>(v4 * s4);

    static_cast<void>(s1 / v);
    static_cast<void>(s2 / v);
    static_cast<void>(s3 / v);
    static_cast<void>(s4 / v);

    static_cast<void>(s2 / v2);
    static_cast<void>(s3 / v3);
    static_cast<void>(s4 / v4);

    static_cast<void>(s1 == s1);
    static_cast<void>(s2 == s2);
    static_cast<void>(s3 == s3);
    static_cast<void>(s4 == s4);

    static_cast<void>(s1 != s1);
    static_cast<void>(s2 != s2);
    static_cast<void>(s3 != s3);
    static_cast<void>(s4 != s4);

    static_cast<void>(s1 & s1);
    static_cast<void>(s2 & s2);
    static_cast<void>(s3 & s3);
    static_cast<void>(s4 & s4);

    static_cast<void>(s1 | s1);
    static_cast<void>(s2 | s2);
    static_cast<void>(s3 | s3);
    static_cast<void>(s4 | s4);

    os << s1;
    os << s2;
    os << s3;
    os << s4;

    static_cast<void>(qc::min(s1, v));
    static_cast<void>(qc::min(s2, v));
    static_cast<void>(qc::min(s2, v2));
    static_cast<void>(qc::min(s3, v));
    static_cast<void>(qc::min(s3, v3));
    static_cast<void>(qc::min(s4, v));
    static_cast<void>(qc::min(s4, v4));

    static_cast<void>(qc::max(s1, v));
    static_cast<void>(qc::max(s2, v));
    static_cast<void>(qc::max(s2, v2));
    static_cast<void>(qc::max(s3, v));
    static_cast<void>(qc::max(s3, v3));
    static_cast<void>(qc::max(s4, v));
    static_cast<void>(qc::max(s4, v4));

    qc::minify(s1, v);
    qc::minify(s2, v);
    qc::minify(s2, v2);
    qc::minify(s3, v);
    qc::minify(s3, v3);
    qc::minify(s4, v);
    qc::minify(s4, v4);

    qc::maxify(s1, v);
    qc::maxify(s2, v);
    qc::maxify(s2, v2);
    qc::maxify(s3, v);
    qc::maxify(s3, v3);
    qc::maxify(s4, v);
    qc::maxify(s4, v4);

    static_cast<void>(qc::round<T>(s1));
    static_cast<void>(qc::round<T>(s2));
    static_cast<void>(qc::round<T>(s3));
    static_cast<void>(qc::round<T>(s4));

    static_cast<void>(qc::clamp(s1, v, v));
    static_cast<void>(qc::clamp(s2, v, v));
    static_cast<void>(qc::clamp(s3, v, v));
    static_cast<void>(qc::clamp(s4, v, v));
    static_cast<void>(qc::clamp(s2, v2, v2));
    static_cast<void>(qc::clamp(s3, v3, v3));
    static_cast<void>(qc::clamp(s4, v4, v4));
    static_cast<void>(qc::clamp(v, s1));
    static_cast<void>(qc::clamp(v2, s2));
    static_cast<void>(qc::clamp(v3, s3));
    static_cast<void>(qc::clamp(v4, s4));

    qc::clampify(s1, v, v);
    qc::clampify(s2, v, v);
    qc::clampify(s3, v, v);
    qc::clampify(s4, v, v);
    qc::clampify(s2, v2, v2);
    qc::clampify(s3, v3, v3);
    qc::clampify(s4, v4, v4);
    qc::clampify(v, s1);
    qc::clampify(v2, s2);
    qc::clampify(v3, s3);
    qc::clampify(v4, s4);
}

template <typename T>
static void compileFunctionsFT()
{
    span1<T> s1{};
    span2<T> s2{};
    span3<T> s3{};
    span4<T> s4{};

    static_cast<void>(qc::round<s8>(s1));
    static_cast<void>(qc::round<s16>(s1));
    static_cast<void>(qc::round<s32>(s1));
    static_cast<void>(qc::round<s64>(s1));
    static_cast<void>(qc::round<s8>(s2));
    static_cast<void>(qc::round<s16>(s2));
    static_cast<void>(qc::round<s32>(s2));
    static_cast<void>(qc::round<s64>(s2));
    static_cast<void>(qc::round<s8>(s3));
    static_cast<void>(qc::round<s16>(s3));
    static_cast<void>(qc::round<s32>(s3));
    static_cast<void>(qc::round<s64>(s3));
    static_cast<void>(qc::round<s8>(s4));
    static_cast<void>(qc::round<s16>(s4));
    static_cast<void>(qc::round<s32>(s4));
    static_cast<void>(qc::round<s64>(s4));
}

template <typename T>
static void compileFunctionsPT()
{
    using P = T *;
    P p{};
    s64 v{};
    span1<P> s{p, p};
    std::stringstream os{};

    s += v;
    s -= v;
    static_cast<void>(s + v);
    static_cast<void>(s - v);
    static_cast<void>(s == s);
    static_cast<void>(s != s);
    os << s;
    static_cast<void>(qc::min(s, p));
    static_cast<void>(qc::max(s, p));
    qc::minify(s, p);
    qc::maxify(s, p);
}

template <u32 n>
static void compileNonMatching()
{
    u8 _u8{};
    u32 _u32{};
    u64 _u64{};
    s8 _s8{};
    s64 _s64{};
    f32 _f32{};
    f64 _f64{};

    vec<u8, n> _vec_u8{};
    vec<u32, n> _vec_u32{};
    vec<u64, n> _vec_u64{};
    vec<s8, n> _vec_s8{};
    vec<s64, n> _vec_s64{};
    vec<f32, n> _vec_f32{};
    vec<f64, n> _vec_f64{};

    span<u8, n> _span_u8{};
    span<u32, n> _span_u32{};
    span<u64, n> _span_u64{};
    span<s8, n> _span_s8{};
    span<s64, n> _span_s64{};
    span<f32, n> _span_f32{};
    span<f64, n> _span_f64{};

    {
        [[maybe_unused]] span<u64, n> s1{_u8, _u8};
        [[maybe_unused]] span<u64, n> s2{_vec_u8, _u8};
        [[maybe_unused]] span<u64, n> s3{_u8, _vec_u8};
        [[maybe_unused]] span<u64, n> s4{_vec_u8, _vec_u8};
        [[maybe_unused]] span<u64, n> s5{_span_u8};
        [[maybe_unused]] span<s64, n> s6{_s8, _s8};
        [[maybe_unused]] span<s64, n> s7{_vec_s8, _s8};
        [[maybe_unused]] span<s64, n> s8{_s8, _vec_s8};
        [[maybe_unused]] span<s64, n> s9{_vec_s8, _vec_s8};
        [[maybe_unused]] span<s64, n> s10{_span_s8};
        [[maybe_unused]] span<f64, n> s11{_f32, _f32};
        [[maybe_unused]] span<f64, n> s12{_vec_f32, _f32};
        [[maybe_unused]] span<f64, n> s13{_f32, _vec_f32};
        [[maybe_unused]] span<f64, n> s14{_vec_f32, _vec_f32};
        [[maybe_unused]] span<f64, n> s15{_span_f32};
    }
    {
        [[maybe_unused]] span<u8, n> s1{_span_u64};
        [[maybe_unused]] span<s8, n> s2{_span_s64};
        [[maybe_unused]] span<f32, n> s3{_span_f64};
    }

    _span_u64 = _span_u8;
    _span_s64 = _span_s8;
    _span_f64 = _span_f32;

    _span_u64 += _u8;
    _span_s64 += _s8;
    _span_s64 += _u32;
    _span_f64 += _f32;
    _span_u64 += _vec_u8;
    _span_s64 += _vec_s8;
    _span_s64 += _vec_u32;
    _span_f64 += _vec_f32;

    _span_u64 -= _u8;
    _span_s64 -= _s8;
    _span_s64 -= _u32;
    _span_f64 -= _f32;
    _span_u64 -= _vec_u8;
    _span_s64 -= _vec_s8;
    _span_s64 -= _vec_u32;
    _span_f64 -= _vec_f32;

    _span_u64 *= _u8;
    _span_s64 *= _s8;
    _span_s64 *= _u32;
    _span_f64 *= _f32;
    _span_u64 *= _vec_u8;
    _span_s64 *= _vec_s8;
    _span_s64 *= _vec_u32;
    _span_f64 *= _vec_f32;

    _span_u64 /= u8{1u};
    _span_s64 /= s8{1};
    _span_s64 /= u32{1u};
    _span_f64 /= f32{1.0f};
    _span_u64 /= vec<u8, n>{u8(1u)};
    _span_s64 /= vec<s8, n>{s8(1)};
    _span_s64 /= vec<u32, n>{1u};
    _span_f64 /= vec<f32, n>{1.0f};

    _span_u64 &= _span_u8;
    _span_s64 &= _span_s8;
    _span_s64 &= _span_u32;
    _span_f64 &= _span_f32;

    _span_u64 |= _span_u8;
    _span_s64 |= _span_s8;
    _span_s64 |= _span_u32;
    _span_f64 |= _span_f32;

    static_cast<void>(_span_u8 + _u64);
    static_cast<void>(_span_u64 + _u8);
    static_cast<void>(_span_s8 + _s64);
    static_cast<void>(_span_s64 + _s8);
    static_cast<void>(_span_s8 + _u32);
    static_cast<void>(_span_s64 + _u32);
    static_cast<void>(_span_f32 + _f64);
    static_cast<void>(_span_f64 + _f32);
    static_cast<void>(_span_u8 + _vec_u64);
    static_cast<void>(_span_u64 + _vec_u8);
    static_cast<void>(_span_s8 + _vec_s64);
    static_cast<void>(_span_s64 + _vec_s8);
    static_cast<void>(_span_s8 + _vec_u32);
    static_cast<void>(_span_s64 + _vec_u32);
    static_cast<void>(_span_f32 + _vec_f64);
    static_cast<void>(_span_f64 + _vec_f32);

    static_cast<void>(_span_u8 - _u64);
    static_cast<void>(_span_u64 - _u8);
    static_cast<void>(_span_s8 - _s64);
    static_cast<void>(_span_s64 - _s8);
    static_cast<void>(_span_s8 - _u32);
    static_cast<void>(_span_s64 - _u32);
    static_cast<void>(_span_f32 - _f64);
    static_cast<void>(_span_f64 - _f32);
    static_cast<void>(_span_u8 - _vec_u64);
    static_cast<void>(_span_u64 - _vec_u8);
    static_cast<void>(_span_s8 - _vec_s64);
    static_cast<void>(_span_s64 - _vec_s8);
    static_cast<void>(_span_s8 - _vec_u32);
    static_cast<void>(_span_s64 - _vec_u32);
    static_cast<void>(_span_f32 - _vec_f64);
    static_cast<void>(_span_f64 - _vec_f32);

    static_cast<void>(_span_u8 * _u64);
    static_cast<void>(_span_u64 * _u8);
    static_cast<void>(_span_s8 * _s64);
    static_cast<void>(_span_s64 * _s8);
    static_cast<void>(_span_s8 * _u32);
    static_cast<void>(_span_s64 * _u32);
    static_cast<void>(_span_f32 * _f64);
    static_cast<void>(_span_f64 * _f32);
    static_cast<void>(_span_u8 * _vec_u64);
    static_cast<void>(_span_u64 * _vec_u8);
    static_cast<void>(_span_s8 * _vec_s64);
    static_cast<void>(_span_s64 * _vec_s8);
    static_cast<void>(_span_s8 * _vec_u32);
    static_cast<void>(_span_s64 * _vec_u32);
    static_cast<void>(_span_f32 * _vec_f64);
    static_cast<void>(_span_f64 * _vec_f32);

    static_cast<void>(_span_u8 / u64{1u});
    static_cast<void>(_span_u64 / u8{1u});
    static_cast<void>(_span_s8 / s64{1});
    static_cast<void>(_span_s64 / s8{1});
    static_cast<void>(_span_s8 / u32{1u});
    static_cast<void>(_span_s64 / u32{1u});
    static_cast<void>(_span_f32 / f64{1.0f});
    static_cast<void>(_span_f64 / f32{1.0f});
    static_cast<void>(_span_u8 / vec<u64, n>{1u});
    static_cast<void>(_span_u64 / vec<u8, n>{u8(1u)});
    static_cast<void>(_span_s8 / vec<s64, n>{1});
    static_cast<void>(_span_s64 / vec<s8, n>{s8(1)});
    static_cast<void>(_span_s8 / vec<u32, n>{1u});
    static_cast<void>(_span_s64 / vec<u32, n>{1u});
    static_cast<void>(_span_f32 / vec<f64, n>{1.0f});
    static_cast<void>(_span_f64 / vec<f32, n>{1.0f});

    static_cast<void>(_span_u8 & _span_u64);
    static_cast<void>(_span_u64 & _span_u8);
    static_cast<void>(_span_s8 & _span_s64);
    static_cast<void>(_span_s64 & _span_s8);
    static_cast<void>(_span_s8 & _span_u32);
    static_cast<void>(_span_s64 & _span_u32);
    static_cast<void>(_span_f32 & _span_f64);
    static_cast<void>(_span_f64 & _span_f32);

    static_cast<void>(_span_u8 | _span_u64);
    static_cast<void>(_span_u64 | _span_u8);
    static_cast<void>(_span_s8 | _span_s64);
    static_cast<void>(_span_s64 | _span_s8);
    static_cast<void>(_span_s8 | _span_u32);
    static_cast<void>(_span_s64 | _span_u32);
    static_cast<void>(_span_f32 | _span_f64);
    static_cast<void>(_span_f64 | _span_f32);

    static_cast<void>(qc::min(_span_u8, _u64));
    static_cast<void>(qc::min(_span_u8, _vec_u64));
    static_cast<void>(qc::min(_span_u64, _u8));
    static_cast<void>(qc::min(_span_u64, _vec_u8));
    static_cast<void>(qc::min(_span_s8, _s64));
    static_cast<void>(qc::min(_span_s8, _vec_s64));
    static_cast<void>(qc::min(_span_s64, _s8));
    static_cast<void>(qc::min(_span_s64, _vec_s8));
    static_cast<void>(qc::min(_span_s64, _u32));
    static_cast<void>(qc::min(_span_s64, _vec_u32));
    static_cast<void>(qc::min(_span_f32, _f64));
    static_cast<void>(qc::min(_span_f32, _vec_f64));
    static_cast<void>(qc::min(_span_f64, _f32));
    static_cast<void>(qc::min(_span_f64, _vec_f32));

    static_cast<void>(qc::max(_span_u8, _u64));
    static_cast<void>(qc::max(_span_u8, _vec_u64));
    static_cast<void>(qc::max(_span_u64, _u8));
    static_cast<void>(qc::max(_span_u64, _vec_u8));
    static_cast<void>(qc::max(_span_s8, _s64));
    static_cast<void>(qc::max(_span_s8, _vec_s64));
    static_cast<void>(qc::max(_span_s64, _s8));
    static_cast<void>(qc::max(_span_s64, _vec_s8));
    static_cast<void>(qc::max(_span_s64, _u32));
    static_cast<void>(qc::max(_span_s64, _vec_u32));
    static_cast<void>(qc::max(_span_f32, _f64));
    static_cast<void>(qc::max(_span_f32, _vec_f64));
    static_cast<void>(qc::max(_span_f64, _f32));
    static_cast<void>(qc::max(_span_f64, _vec_f32));

    static_cast<void>(qc::minify(_span_u64, _u8));
    static_cast<void>(qc::minify(_span_u64, _vec_u8));
    static_cast<void>(qc::minify(_span_s64, _s8));
    static_cast<void>(qc::minify(_span_s64, _vec_s8));
    static_cast<void>(qc::minify(_span_s64, _u32));
    static_cast<void>(qc::minify(_span_s64, _vec_u32));
    static_cast<void>(qc::minify(_span_f64, _f32));
    static_cast<void>(qc::minify(_span_f64, _vec_f32));
}

template <>
void compileNonMatching<1>()
{
    u8 _u8{};
    u32 _u32{};
    u64 _u64{};
    s8 _s8{};
    s64 _s64{};
    f32 _f32{};
    f64 _f64{};

    span1<u8> _span_u8{};
    span1<u32> _span_u32{};
    span1<u64> _span_u64{};
    span1<s8> _span_s8{};
    span1<s64> _span_s64{};
    span1<f32> _span_f32{};
    span1<f64> _span_f64{};

    {
        [[maybe_unused]] span1<u64> s1{_u8, _u8};
        [[maybe_unused]] span1<u64> s3{_span_u8};
        [[maybe_unused]] span1<s64> s4{_s8, _s8};
        [[maybe_unused]] span1<s64> s6{_span_s8};
        [[maybe_unused]] span1<f64> s7{_f32, _f32};
        [[maybe_unused]] span1<f64> s9{_span_f32};
    }
    {
        [[maybe_unused]] span1<u8> s1{_span_u64};
        [[maybe_unused]] span1<s8> s2{_span_s64};
        [[maybe_unused]] span1<f32> s3{_span_f64};
    }

    _span_u64 += _u8;
    _span_s64 += _s8;
    _span_s64 += _u32;
    _span_f64 += _f32;

    _span_u64 -= _u8;
    _span_s64 -= _s8;
    _span_s64 -= _u32;
    _span_f64 -= _f32;

    _span_u64 *= _u8;
    _span_s64 *= _s8;
    _span_s64 *= _u32;
    _span_f64 *= _f32;

    _span_u64 /= u8{1u};
    _span_s64 /= s8{1};
    _span_s64 /= u32{1u};
    _span_f64 /= f32{1.0f};

    _span_u64 &= _span_u8;
    _span_s64 &= _span_s8;
    _span_s64 &= _span_u32;
    _span_f64 &= _span_f32;

    _span_u64 |= _span_u8;
    _span_s64 |= _span_s8;
    _span_s64 |= _span_u32;
    _span_f64 |= _span_f32;

    static_cast<void>(_span_u8 + _u64);
    static_cast<void>(_span_u64 + _u8);
    static_cast<void>(_span_s8 + _s64);
    static_cast<void>(_span_s64 + _s8);
    static_cast<void>(_span_s8 + _u32);
    static_cast<void>(_span_s64 + _u32);
    static_cast<void>(_span_f32 + _f64);
    static_cast<void>(_span_f64 + _f32);

    static_cast<void>(_span_u8 - _u64);
    static_cast<void>(_span_u64 - _u8);
    static_cast<void>(_span_s8 - _s64);
    static_cast<void>(_span_s64 - _s8);
    static_cast<void>(_span_s8 - _u32);
    static_cast<void>(_span_s64 - _u32);
    static_cast<void>(_span_f32 - _f64);
    static_cast<void>(_span_f64 - _f32);

    static_cast<void>(_span_u8 * _u64);
    static_cast<void>(_span_u64 * _u8);
    static_cast<void>(_span_s8 * _s64);
    static_cast<void>(_span_s64 * _s8);
    static_cast<void>(_span_s8 * _u32);
    static_cast<void>(_span_s64 * _u32);
    static_cast<void>(_span_f32 * _f64);
    static_cast<void>(_span_f64 * _f32);

    static_cast<void>(_span_u8 / u64{1u});
    static_cast<void>(_span_u64 / u8{1u});
    static_cast<void>(_span_s8 / s64{1});
    static_cast<void>(_span_s64 / s8{1});
    static_cast<void>(_span_s8 / u32{1u});
    static_cast<void>(_span_s64 / u32{1u});
    static_cast<void>(_span_f32 / f64{1.0f});
    static_cast<void>(_span_f64 / f32{1.0f});

    static_cast<void>(_span_u8 & _span_u64);
    static_cast<void>(_span_u64 & _span_u8);
    static_cast<void>(_span_s8 & _span_s64);
    static_cast<void>(_span_s64 & _span_s8);
    static_cast<void>(_span_s8 & _span_u32);
    static_cast<void>(_span_s64 & _span_u32);
    static_cast<void>(_span_f32 & _span_f64);
    static_cast<void>(_span_f64 & _span_f32);

    static_cast<void>(_span_u8 | _span_u64);
    static_cast<void>(_span_u64 | _span_u8);
    static_cast<void>(_span_s8 | _span_s64);
    static_cast<void>(_span_s64 | _span_s8);
    static_cast<void>(_span_s8 | _span_u32);
    static_cast<void>(_span_s64 | _span_u32);
    static_cast<void>(_span_f32 | _span_f64);
    static_cast<void>(_span_f64 | _span_f32);

    static_cast<void>(qc::min(_span_u8, _u64));
    static_cast<void>(qc::min(_span_u64, _u8));
    static_cast<void>(qc::min(_span_s8, _s64));
    static_cast<void>(qc::min(_span_s64, _s8));
    static_cast<void>(qc::min(_span_s64, _u32));
    static_cast<void>(qc::min(_span_f32, _f64));
    static_cast<void>(qc::min(_span_f64, _f32));

    static_cast<void>(qc::max(_span_u8, _u64));
    static_cast<void>(qc::max(_span_u64, _u8));
    static_cast<void>(qc::max(_span_s8, _s64));
    static_cast<void>(qc::max(_span_s64, _s8));
    static_cast<void>(qc::max(_span_s64, _u32));
    static_cast<void>(qc::max(_span_f32, _f64));
    static_cast<void>(qc::max(_span_f64, _f32));

    static_cast<void>(qc::minify(_span_u64, _u8));
    static_cast<void>(qc::minify(_span_s64, _s8));
    static_cast<void>(qc::minify(_span_s64, _u32));
    static_cast<void>(qc::minify(_span_f64, _f32));
}

static void compileFunctions()
{
    compileFunctionsT<f32>();
    compileFunctionsT<f64>();
    compileFunctionsT<s8>();
    compileFunctionsT<s16>();
    compileFunctionsT<s32>();
    compileFunctionsT<s64>();
    compileFunctionsT<u8>();
    compileFunctionsT<u16>();
    compileFunctionsT<u32>();
    compileFunctionsT<u64>();

    compileFunctionsFT<f32>();
    compileFunctionsFT<f64>();

    compileFunctionsPT<s32>();

    compileNonMatching<1>();
    compileNonMatching<2>();
    compileNonMatching<3>();
    compileNonMatching<4>();
}

template <typename T, u32 n>
static void testPropertiesTN()
{
    static_assert(std::is_standard_layout_v<span<T, n>>);
    static_assert(std::is_trivially_default_constructible_v<span<T, n>>);
    static_assert(std::is_trivially_copyable_v<span<T, n>>);
    static_assert(std::is_trivially_copy_constructible_v<span<T, n>>);
    static_assert(std::is_trivially_move_constructible_v<span<T, n>>);
    static_assert(std::is_trivially_copy_assignable_v<span<T, n>>);
    static_assert(std::is_trivially_move_assignable_v<span<T, n>>);
    static_assert(std::is_trivially_destructible_v<span<T, n>>);
    static_assert(sizeof(span<T, n>) == 2 * n * sizeof(T));
    static_assert(sizeof(span<T, n>[4]) == 4 * 2 * n * sizeof(T));
    static_assert(alignof(span<T, n>) == alignof(T));
    static_assert(alignof(span<T, n>[4]) == alignof(T));
}

template <typename T>
static void testPropertiesT()
{
    testPropertiesTN<T, 1>();
    testPropertiesTN<T, 2>();
    testPropertiesTN<T, 3>();
    testPropertiesTN<T, 4>();
}

static void testProperties()
{
    testPropertiesT<f32>();
    testPropertiesT<f64>();
    testPropertiesT<s8>();
    testPropertiesT<s16>();
    testPropertiesT<s32>();
    testPropertiesT<s64>();
    testPropertiesT<u8>();
    testPropertiesT<u16>();
    testPropertiesT<u32>();
    testPropertiesT<u64>();
}

template <typename T1, typename T2>
static void compileCastsTT()
{
    span1<T1> s1{};
    span2<T1> s2{};
    span3<T1> s3{};
    span4<T1> s4{};

    static_cast<void>(static_cast<bool>(s1));
    static_cast<void>(static_cast<bool>(s2));
    static_cast<void>(static_cast<bool>(s3));
    static_cast<void>(static_cast<bool>(s4));
}

template <typename T>
static void compileCastsT()
{
    compileCastsTT<T, f32>();
    compileCastsTT<T, f64>();
    compileCastsTT<T, s8>();
    compileCastsTT<T, s16>();
    compileCastsTT<T, s32>();
    compileCastsTT<T, s64>();
    compileCastsTT<T, u8>();
    compileCastsTT<T, u16>();
    compileCastsTT<T, u32>();
    compileCastsTT<T, u64>();
}

static void compileCasts()
{
    compileCastsT<f32>();
    compileCastsT<f64>();
    compileCastsT<s8>();
    compileCastsT<s16>();
    compileCastsT<s32>();
    compileCastsT<s64>();
    compileCastsT<u8>();
    compileCastsT<u16>();
    compileCastsT<u32>();
    compileCastsT<u64>();
}

template <u32 n>
static void testCastExplicitnessN()
{
    static_assert(std::is_convertible_v<fspan<n>, dspan<n>>);
    static_assert(!std::is_convertible_v<dspan<n>, fspan<n>>);

    static_assert(std::is_convertible_v<ispan<n>, lspan<n>>);
    static_assert(std::is_convertible_v<uispan<n>, lspan<n>>);
    static_assert(std::is_convertible_v<uispan<n>, ulspan<n>>);
    static_assert(!std::is_convertible_v<ispan<n>, ulspan<n>>);

    static_assert(!std::is_convertible_v<cspan<n>, fspan<n>>);
    static_assert(!std::is_convertible_v<fspan<n>, lspan<n>>);
}

TEST(Span, castExplicitness)
{
    testCastExplicitnessN<1u>();
    testCastExplicitnessN<2u>();
    testCastExplicitnessN<3u>();
    testCastExplicitnessN<4u>();
}

template <typename T>
static void compileConstantsT()
{
    constexpr span1<T> is1{qc::fullSpan<T, 1>};
    constexpr span2<T> is2{qc::fullSpan<T, 2>};
    constexpr span3<T> is3{qc::fullSpan<T, 3>};
    constexpr span4<T> is4{qc::fullSpan<T, 4>};

    constexpr span1<T> nulls1{qc::nullSpan<T, 1>};
    constexpr span2<T> nulls2{qc::nullSpan<T, 2>};
    constexpr span3<T> nulls3{qc::nullSpan<T, 3>};
    constexpr span4<T> nulls4{qc::nullSpan<T, 4>};
}

static void compileConstants()
{
    compileConstantsT<f32>();
    compileConstantsT<f64>();
    compileConstantsT<s8>();
    compileConstantsT<s16>();
    compileConstantsT<s32>();
    compileConstantsT<s64>();
    compileConstantsT<u8>();
    compileConstantsT<u16>();
    compileConstantsT<u32>();
    compileConstantsT<u64>();
}

TEST(Span, compilation)
{
    compileClasses();
    compileFunctions();
    testProperties();
    compileCasts();
    compileConstants();
}

template <typename T>
void testSpanConceptT()
{
    static_assert(Span<span1<T>>);
    static_assert(Span<span2<T>>);
    static_assert(Span<span3<T>>);
    static_assert(Span<span4<T>>);

    static_assert(Span1<span1<T>>);
    static_assert(!Span1<span2<T>>);
    static_assert(!Span1<span3<T>>);
    static_assert(!Span1<span4<T>>);

    static_assert(Span2<span2<T>>);
    static_assert(!Span2<span1<T>>);
    static_assert(!Span2<span3<T>>);
    static_assert(!Span2<span4<T>>);

    static_assert(Span3<span3<T>>);
    static_assert(!Span3<span1<T>>);
    static_assert(!Span3<span2<T>>);
    static_assert(!Span3<span4<T>>);

    static_assert(Span4<span4<T>>);
    static_assert(!Span4<span1<T>>);
    static_assert(!Span4<span2<T>>);
    static_assert(!Span4<span3<T>>);
}

template <typename T>
void testFloaterSpanConceptT()
{
    static_assert(FloatingVector<vec2<T>>);
    static_assert(FloatingVector<vec3<T>>);
    static_assert(FloatingVector<vec4<T>>);
}

template <typename T>
void testIntegerSpanConceptT()
{
    static_assert(IntegralVector<vec2<T>>);
    static_assert(IntegralVector<vec3<T>>);
    static_assert(IntegralVector<vec4<T>>);
}

template <typename T>
void testSignedIntegerSpanConceptT()
{
    static_assert(SignedIntegralVector<vec2<T>>);
    static_assert(SignedIntegralVector<vec3<T>>);
    static_assert(SignedIntegralVector<vec4<T>>);
}

template <typename T>
void testUnsignedIntegerSpanConceptT()
{
    static_assert(UnsignedIntegralVector<vec2<T>>);
    static_assert(UnsignedIntegralVector<vec3<T>>);
    static_assert(UnsignedIntegralVector<vec4<T>>);
}

TEST(Span, types)
{
    testSpanConceptT<s8>();
    testSpanConceptT<u8>();
    testSpanConceptT<s16>();
    testSpanConceptT<u16>();
    testSpanConceptT<f32>();
    testSpanConceptT<s32>();
    testSpanConceptT<u32>();
    testSpanConceptT<f64>();
    testSpanConceptT<s64>();
    testSpanConceptT<u64>();
    static_assert(!Span<s32>);

    testFloaterSpanConceptT<f32>();
    testFloaterSpanConceptT<f64>();
    static_assert(!FloatingSpan<ivec2>);

    testIntegerSpanConceptT<s8>();
    testIntegerSpanConceptT<u8>();
    testIntegerSpanConceptT<s16>();
    testIntegerSpanConceptT<u16>();
    testIntegerSpanConceptT<s32>();
    testIntegerSpanConceptT<u32>();
    testIntegerSpanConceptT<s64>();
    testIntegerSpanConceptT<u64>();
    static_assert(!IntegralSpan<fvec2>);

    testSignedIntegerSpanConceptT<s8>();
    testSignedIntegerSpanConceptT<s16>();
    testSignedIntegerSpanConceptT<s32>();
    testSignedIntegerSpanConceptT<s64>();
    static_assert(!SignedIntegralSpan<uivec2>);

    testUnsignedIntegerSpanConceptT<u8>();
    testUnsignedIntegerSpanConceptT<u16>();
    testUnsignedIntegerSpanConceptT<u32>();
    testUnsignedIntegerSpanConceptT<u64>();
    static_assert(!UnsignedIntegralSpan<ivec2>);

    static_assert(PointerSpan<span1<s32 *>>);
    static_assert(PointerSpan<span1<const s32 *>>);
    static_assert(Span1<span1<s32 *>>);
    static_assert(Span1<span1<const s32 *>>);
    static_assert(!PointerSpan<ispan1>);
}
