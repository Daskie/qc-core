#pragma once

#include <qc-core/core-ext.hpp>

namespace qc
{
    template <NumericOrBoolean T, int n> struct vec;

    inline namespace primitives
    {
        using qc::vec;

        template <typename T> using vec2 = vec<T, 2>;
        template <typename T> using vec3 = vec<T, 3>;
        template <typename T> using vec4 = vec<T, 4>;

        template <int n> using  fvec = vec< f32, n>;
        template <int n> using  dvec = vec< f64, n>;
        template <int n> using  cvec = vec<  s8, n>;
        template <int n> using ucvec = vec<  u8, n>;
        template <int n> using  svec = vec< s16, n>;
        template <int n> using usvec = vec< u16, n>;
        template <int n> using  ivec = vec< s32, n>;
        template <int n> using uivec = vec< u32, n>;
        template <int n> using  lvec = vec< s64, n>;
        template <int n> using ulvec = vec< u64, n>;
        template <int n> using  bvec = vec<bool, n>;

        using  fvec2 = vec< f32, 2>;
        using  fvec3 = vec< f32, 3>;
        using  fvec4 = vec< f32, 4>;
        using  dvec2 = vec< f64, 2>;
        using  dvec3 = vec< f64, 3>;
        using  dvec4 = vec< f64, 4>;
        using  cvec2 = vec<  s8, 2>;
        using  cvec3 = vec<  s8, 3>;
        using  cvec4 = vec<  s8, 4>;
        using ucvec2 = vec<  u8, 2>;
        using ucvec3 = vec<  u8, 3>;
        using ucvec4 = vec<  u8, 4>;
        using  svec2 = vec< s16, 2>;
        using  svec3 = vec< s16, 3>;
        using  svec4 = vec< s16, 4>;
        using usvec2 = vec< u16, 2>;
        using usvec3 = vec< u16, 3>;
        using usvec4 = vec< u16, 4>;
        using  ivec2 = vec< s32, 2>;
        using  ivec3 = vec< s32, 3>;
        using  ivec4 = vec< s32, 4>;
        using uivec2 = vec< u32, 2>;
        using uivec3 = vec< u32, 3>;
        using uivec4 = vec< u32, 4>;
        using  lvec2 = vec< s64, 2>;
        using  lvec3 = vec< s64, 3>;
        using  lvec4 = vec< s64, 4>;
        using ulvec2 = vec< u64, 2>;
        using ulvec3 = vec< u64, 3>;
        using ulvec4 = vec< u64, 4>;
        using  bvec2 = vec<bool, 2>;
        using  bvec3 = vec<bool, 3>;
        using  bvec4 = vec<bool, 4>;

        template <typename T> concept Vector = Same<T, vec<typename T::Type, T::n>>;

        template <typename T> concept NumericVector = Vector<T> && Numeric<typename T::Type>;
        template <typename T> concept FloatingVector = Vector<T> && Floating<typename T::Type>;
        template <typename T> concept IntegralVector = Vector<T> && Integral<typename T::Type>;
        template <typename T> concept SignedIntegralVector = Vector<T> && SignedIntegral<typename T::Type>;
        template <typename T> concept UnsignedIntegralVector = Vector<T> && UnsignedIntegral<typename T::Type>;
        template <typename T> concept BooleanVector = Vector<T> && Boolean<typename T::Type>;

        template <typename T> concept Vector2 = Vector<T> && T::n == 2;
        template <typename T> concept Vector3 = Vector<T> && T::n == 3;
        template <typename T> concept Vector4 = Vector<T> && T::n == 4;
    }

    template <NumericOrBoolean T>
    struct vec<T, 2>
    {
        using Type = T;
        static constexpr int n{2};

        TRIVIALLY_SERIALIZABLE;

        T x;
        T y;

        constexpr vec() = default;
        constexpr vec(T v);
        template <NumericOrBoolean U> constexpr explicit vec(vec2<U> v);
        template <NumericOrBoolean U> constexpr explicit vec(vec3<U> v);
        template <NumericOrBoolean U> constexpr explicit vec(vec4<U> v);
        constexpr vec(T v1, T v2);

        constexpr vec(const vec & v) = default;
        constexpr vec(vec && v) = default;

        vec & operator=(const vec & v) = default;
        vec & operator=(vec && v) = default;

        template <SubOf<T> U> vec & operator=(U v);
        template <SubOf<T> U> vec & operator=(const vec2<U> & v);

        ~vec() = default;

        nodisc constexpr explicit operator bool() const;

        template <int i> nodisc T & at();
        template <int i> nodisc constexpr T at() const;

        nodisc T & operator[](int i);
        nodisc T operator[](int i) const;

        nodisc constexpr bool operator==(const vec &) const = default;
    };

    template <NumericOrBoolean T>
    struct vec<T, 3>
    {
        using Type = T;
        static constexpr int n{3};

        TRIVIALLY_SERIALIZABLE;

        T x;
        T y;
        T z;

        constexpr vec() = default;
        constexpr vec(T v);
        template <NumericOrBoolean U> constexpr explicit vec(vec2<U> v);
        template <NumericOrBoolean U> constexpr explicit vec(vec3<U> v);
        template <NumericOrBoolean U> constexpr explicit vec(vec4<U> v);
        constexpr vec(T v1, T v2, T v3);
        constexpr vec(vec2<T> v1, T v2);
        constexpr vec(T v1, vec2<T> v2);

        constexpr vec(const vec & v) = default;
        constexpr vec(vec && v) = default;

        vec & operator=(const vec & v) = default;
        vec & operator=(vec && v) = default;

        template <SubOf<T> U> vec & operator=(U v);
        template <SubOf<T> U> vec & operator=(const vec2<U> & v);
        template <SubOf<T> U> vec & operator=(const vec3<U> & v);

        ~vec() = default;

        nodisc constexpr explicit operator bool() const;

        template <int i> nodisc T & at();
        template <int i> nodisc constexpr T at() const;

        nodisc T & operator[](int i);
        nodisc T operator[](int i) const;

        nodisc vec2<T> & xy();
        nodisc constexpr vec2<T> xy() const;

        nodisc vec2<T> & yz();
        nodisc constexpr vec2<T> yz() const;

        nodisc constexpr bool operator==(const vec &) const = default;
    };

    template <NumericOrBoolean T>
    struct vec<T, 4>
    {
        using Type = T;
        static constexpr int n{4};

        TRIVIALLY_SERIALIZABLE;

        T x;
        T y;
        T z;
        T w;

        constexpr vec() = default;
        constexpr vec(T v);
        template <NumericOrBoolean U> constexpr explicit vec(vec2<U> v);
        template <NumericOrBoolean U> constexpr explicit vec(vec3<U> v);
        template <NumericOrBoolean U> constexpr explicit vec(vec4<U> v);
        constexpr vec(T v1, T v2, T v3, T v4);
        constexpr vec(vec2<T> v1, T v2, T v3);
        constexpr vec(T v1, vec2<T> v2, T v3);
        constexpr vec(T v1, T v2, vec2<T> v3);
        constexpr vec(vec2<T> v1, vec2<T> v2);
        constexpr vec(vec3<T> v1, T v2);
        constexpr vec(T v1, vec3<T> v2);

        constexpr vec(const vec & v) = default;
        constexpr vec(vec && v) = default;

        vec & operator=(const vec & v) = default;
        vec & operator=(vec && v) = default;

        template <SubOf<T> U> vec & operator=(U v);
        template <SubOf<T> U> vec & operator=(const vec2<U> & v);
        template <SubOf<T> U> vec & operator=(const vec3<U> & v);
        template <SubOf<T> U> vec & operator=(const vec4<U> & v);

        ~vec() = default;

        nodisc constexpr explicit operator bool() const;

        template <int i> nodisc T & at();
        template <int i> nodisc constexpr T at() const;

        nodisc T & operator[](int i);
        nodisc T operator[](int i) const;

        nodisc vec2<T> & xy();
        nodisc constexpr vec2<T> xy() const;

        nodisc vec2<T> & yz();
        nodisc constexpr vec2<T> yz() const;

        nodisc vec2<T> & zw();
        nodisc constexpr vec2<T> zw() const;

        nodisc vec3<T> & xyz();
        nodisc constexpr vec3<T> xyz() const;

        nodisc vec3<T> & yzw();
        nodisc constexpr vec3<T> yzw() const;

        nodisc constexpr bool operator==(const vec &) const = default;
    };

    //
    // ...
    //
    template <typename T, int n> constexpr vec<T, n> px{};
    template <typename T, int n> constexpr vec<T, n> nx{};
    template <typename T, int n> constexpr vec<T, n> py{};
    template <typename T, int n> constexpr vec<T, n> ny{};
    template <typename T, int n> constexpr vec<T, n> pz{};
    template <typename T, int n> constexpr vec<T, n> nz{};
    template <typename T, int n> constexpr vec<T, n> pw{};
    template <typename T, int n> constexpr vec<T, n> nw{};
    template <typename T> constexpr vec2<T> px<T, 2>{T( 1), T( 0)};
    template <typename T> constexpr vec2<T> nx<T, 2>{T(-1), T( 0)};
    template <typename T> constexpr vec3<T> px<T, 3>{T( 1), T( 0), T( 0)};
    template <typename T> constexpr vec3<T> nx<T, 3>{T(-1), T( 0), T( 0)};
    template <typename T> constexpr vec4<T> px<T, 4>{T( 1), T( 0), T( 0), T( 0)};
    template <typename T> constexpr vec4<T> nx<T, 4>{T(-1), T( 0), T( 0), T( 0)};
    template <typename T> constexpr vec2<T> py<T, 2>{T( 0), T( 1)};
    template <typename T> constexpr vec2<T> ny<T, 2>{T( 0), T(-1)};
    template <typename T> constexpr vec3<T> py<T, 3>{T( 0), T( 1), T( 0)};
    template <typename T> constexpr vec3<T> ny<T, 3>{T( 0), T(-1), T( 0)};
    template <typename T> constexpr vec4<T> py<T, 4>{T( 0), T( 1), T( 0), T( 0)};
    template <typename T> constexpr vec4<T> ny<T, 4>{T( 0), T(-1), T( 0), T( 0)};
    template <typename T> constexpr vec3<T> pz<T, 3>{T( 0), T( 0), T( 1)};
    template <typename T> constexpr vec3<T> nz<T, 3>{T( 0), T( 0), T(-1)};
    template <typename T> constexpr vec4<T> pz<T, 4>{T( 0), T( 0), T( 1), T( 0)};
    template <typename T> constexpr vec4<T> nz<T, 4>{T( 0), T( 0), T(-1), T( 0)};
    template <typename T> constexpr vec4<T> pw<T, 4>{T( 0), T( 0), T( 0), T( 1)};
    template <typename T> constexpr vec4<T> nw<T, 4>{T( 0), T( 0), T( 0), T(-1)};
    template <typename T> constexpr vec2<T> px2 = px<T, 2>;
    template <typename T> constexpr vec2<T> nx2 = nx<T, 2>;
    template <typename T> constexpr vec3<T> px3 = px<T, 3>;
    template <typename T> constexpr vec3<T> nx3 = nx<T, 3>;
    template <typename T> constexpr vec4<T> px4 = px<T, 4>;
    template <typename T> constexpr vec4<T> nx4 = nx<T, 4>;
    template <typename T> constexpr vec2<T> py2 = py<T, 2>;
    template <typename T> constexpr vec2<T> ny2 = ny<T, 2>;
    template <typename T> constexpr vec3<T> py3 = py<T, 3>;
    template <typename T> constexpr vec3<T> ny3 = ny<T, 3>;
    template <typename T> constexpr vec4<T> py4 = py<T, 4>;
    template <typename T> constexpr vec4<T> ny4 = ny<T, 4>;
    template <typename T> constexpr vec3<T> pz3 = pz<T, 3>;
    template <typename T> constexpr vec3<T> nz3 = nz<T, 3>;
    template <typename T> constexpr vec4<T> pz4 = pz<T, 4>;
    template <typename T> constexpr vec4<T> nz4 = nz<T, 4>;
    template <typename T> constexpr vec4<T> pw4 = pw<T, 4>;
    template <typename T> constexpr vec4<T> nw4 = nw<T, 4>;

    template <Numeric T, int n> vec<T, n> & operator++(vec<T, n> & v);
    template <Numeric T, int n> vec<T, n>   operator++(vec<T, n> & v, int);

    template <Numeric T, int n> vec<T, n> & operator--(vec<T, n> & v);
    template <Numeric T, int n> vec<T, n>   operator--(vec<T, n> & v, int);

    template <Numeric T1, SubOf<T1> T2, int n> vec<T1, n> & operator+=(vec<T1, n> & v1, const vec<T2, n> & v2);
    template <Numeric T1, SubOf<T1> T2, int n> vec<T1, n> & operator+=(vec<T1, n> & v1, T2 v2);

    template <Numeric T1, SubOf<T1> T2, int n> vec<T1, n> & operator-=(vec<T1, n> & v1, const vec<T2, n> & v2);
    template <Numeric T1, SubOf<T1> T2, int n> vec<T1, n> & operator-=(vec<T1, n> & v1, T2 v2);

    template <Numeric T1, SubOf<T1> T2, int n> vec<T1, n> & operator*=(vec<T1, n> & v1, const vec<T2, n> & v2);
    template <Numeric T1, SubOf<T1> T2, int n> vec<T1, n> & operator*=(vec<T1, n> & v1, T2 v2);

    template <Numeric T1, SubOf<T1> T2, int n> vec<T1, n> & operator/=(vec<T1, n> & v1, const vec<T2, n> & v2);
    template <Numeric T1, SubOf<T1> T2, int n> vec<T1, n> & operator/=(vec<T1, n> & v1, T2 v2);

    template <Numeric T1, SubOf<T1> T2, int n> vec<T1, n> & operator%=(vec<T1, n> & v1, const vec<T2, n> & v2);
    template <Numeric T1, SubOf<T1> T2, int n> vec<T1, n> & operator%=(vec<T1, n> & v1, T2 v2);

    template <UnsignedIntegral T1, UnsignedSubOf<T1> T2, int n> vec<T1, n> & operator&=(vec<T1, n> & v1, const vec<T2, n> & v2);
    template <UnsignedIntegral T1, UnsignedSubOf<T1> T2, int n> vec<T1, n> & operator&=(vec<T1, n> & v1, T2 v2);

    template <UnsignedIntegral T1, UnsignedSubOf<T1> T2, int n> vec<T1, n> & operator|=(vec<T1, n> & v1, const vec<T2, n> & v2);
    template <UnsignedIntegral T1, UnsignedSubOf<T1> T2, int n> vec<T1, n> & operator|=(vec<T1, n> & v1, T2 v2);

    template <UnsignedIntegral T1, UnsignedSubOf<T1> T2, int n> vec<T1, n> & operator^=(vec<T1, n> & v1, const vec<T2, n> & v2);
    template <UnsignedIntegral T1, UnsignedSubOf<T1> T2, int n> vec<T1, n> & operator^=(vec<T1, n> & v1, T2 v2);

    template <UnsignedIntegral T, int n> vec<T, n> & operator<<=(vec<T, n> & v1, int v2);

    template <UnsignedIntegral T, int n> vec<T, n> & operator>>=(vec<T, n> & v1, int v2);

    template <Numeric T, int n> nodisc constexpr vec<T, n> operator+(const vec<T, n> & v);

    template <Numeric T, int n> nodisc constexpr vec<T, n> operator-(const vec<T, n> & v);

    template <UnsignedIntegral T, int n> nodisc constexpr vec<T, n> operator~(const vec<T, n> & v);

    template <Numeric T1, Numeric T2, int n> nodisc constexpr vec<Common<T1, T2>, n> operator+(const vec<T1, n> & v1, const vec<T2, n> & v2);
    template <Numeric T1, Numeric T2, int n> nodisc constexpr vec<Common<T1, T2>, n> operator+(const vec<T1, n> & v1, T2 v2);
    template <Numeric T1, Numeric T2, int n> nodisc constexpr vec<Common<T1, T2>, n> operator+(T1 v1, const vec<T2, n> & v2);

    template <Numeric T1, Numeric T2, int n> nodisc constexpr vec<Common<T1, T2>, n> operator-(const vec<T1, n> & v1, const vec<T2, n> & v2);
    template <Numeric T1, Numeric T2, int n> nodisc constexpr vec<Common<T1, T2>, n> operator-(const vec<T1, n> & v1, T2 v2);
    template <Numeric T1, Numeric T2, int n> nodisc constexpr vec<Common<T1, T2>, n> operator-(T1 v1, const vec<T2, n> & v2);

    template <Numeric T1, Numeric T2, int n> nodisc constexpr vec<Common<T1, T2>, n> operator*(const vec<T1, n> & v1, const vec<T2, n> & v2);
    template <Numeric T1, Numeric T2, int n> nodisc constexpr vec<Common<T1, T2>, n> operator*(const vec<T1, n> & v1, T2 v2);
    template <Numeric T1, Numeric T2, int n> nodisc constexpr vec<Common<T1, T2>, n> operator*(T1 v1, const vec<T2, n> & v2);

    template <Numeric T1, Numeric T2, int n> nodisc constexpr vec<Common<T1, T2>, n> operator/(const vec<T1, n> & v1, const vec<T2, n> & v2);
    template <Numeric T1, Numeric T2, int n> nodisc constexpr vec<Common<T1, T2>, n> operator/(const vec<T1, n> & v1, T2 v2);
    template <Numeric T1, Numeric T2, int n> nodisc constexpr vec<Common<T1, T2>, n> operator/(T1 v1, const vec<T2, n> & v2);

    template <Numeric T1, Numeric T2, int n> nodisc constexpr vec<Common<T1, T2>, n> operator%(const vec<T1, n> & v1, const vec<T2, n> & v2);
    template <Numeric T1, Numeric T2, int n> nodisc constexpr vec<Common<T1, T2>, n> operator%(const vec<T1, n> & v1, T2 v2);
    template <Numeric T1, Numeric T2, int n> nodisc constexpr vec<Common<T1, T2>, n> operator%(T1 v1, const vec<T2, n> & v2);

    template <UnsignedIntegral T1, UnsignedIntegral T2, int n> nodisc constexpr vec<LargerOf<T1, T2>, n> operator&(const vec<T1, n> & v1, const vec<T2, n> & v2);
    template <UnsignedIntegral T1, UnsignedIntegral T2, int n> nodisc constexpr vec<LargerOf<T1, T2>, n> operator&(const vec<T1, n> & v1, T2 v2);
    template <UnsignedIntegral T1, UnsignedIntegral T2, int n> nodisc constexpr vec<LargerOf<T1, T2>, n> operator&(T1 v1, const vec<T2, n> & v2);

    template <UnsignedIntegral T1, UnsignedIntegral T2, int n> nodisc constexpr vec<LargerOf<T1, T2>, n> operator|(const vec<T1, n> & v1, const vec<T2, n> & v2);
    template <UnsignedIntegral T1, UnsignedIntegral T2, int n> nodisc constexpr vec<LargerOf<T1, T2>, n> operator|(const vec<T1, n> & v1, T2 v2);
    template <UnsignedIntegral T1, UnsignedIntegral T2, int n> nodisc constexpr vec<LargerOf<T1, T2>, n> operator|(T1 v1, const vec<T2, n> & v2);

    template <UnsignedIntegral T1, UnsignedIntegral T2, int n> nodisc constexpr vec<LargerOf<T1, T2>, n> operator^(const vec<T1, n> & v1, const vec<T2, n> & v2);
    template <UnsignedIntegral T1, UnsignedIntegral T2, int n> nodisc constexpr vec<LargerOf<T1, T2>, n> operator^(const vec<T1, n> & v1, T2 v2);
    template <UnsignedIntegral T1, UnsignedIntegral T2, int n> nodisc constexpr vec<LargerOf<T1, T2>, n> operator^(T1 v1, const vec<T2, n> & v2);

    template <UnsignedIntegral T, int n> nodisc constexpr vec<T, n> operator<<(const vec<T, n> & v1, int v2);

    template <UnsignedIntegral T, int n> nodisc constexpr vec<T, n> operator>>(const vec<T, n> & v1, int v2);

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2> nodisc constexpr bvec<n> operator==(const vec<T1, n> & v1, T2 v2);
    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2> nodisc constexpr bvec<n> operator==(T1 v1, const vec<T2, n> & v2);
    template <int n> nodisc constexpr bvec<n> operator==(const bvec<n> & v1, bool v2);
    template <int n> nodisc constexpr bvec<n> operator==(bool v1, const bvec<n> & v2);

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2> nodisc constexpr bvec<n> operator!=(const vec<T1, n> & v1, T2 v2);
    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2> nodisc constexpr bvec<n> operator!=(T1 v1, const vec<T2, n> & v2);
    template <int n> nodisc constexpr bvec<n> operator!=(const bvec<n> & v1, bool v2);
    template <int n> nodisc constexpr bvec<n> operator!=(bool v1, const bvec<n> & v2);

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2> nodisc constexpr bvec<n> operator<(const vec<T1, n> & v1, const vec<T2, n> & v2);
    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2> nodisc constexpr bvec<n> operator<(const vec<T1, n> & v1, T2 v2);
    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2> nodisc constexpr bvec<n> operator<(T1 v1, const vec<T2, n> & v2);

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2> nodisc constexpr bvec<n> operator>(const vec<T1, n> & v1, const vec<T2, n> & v2);
    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2> nodisc constexpr bvec<n> operator>(const vec<T1, n> & v1, T2 v2);
    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2> nodisc constexpr bvec<n> operator>(T1 v1, const vec<T2, n> & v2);

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2> nodisc constexpr bvec<n> operator<=(const vec<T1, n> & v1, const vec<T2, n> & v2);
    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2> nodisc constexpr bvec<n> operator<=(const vec<T1, n> & v1, T2 v2);
    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2> nodisc constexpr bvec<n> operator<=(T1 v1, const vec<T2, n> & v2);

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2> nodisc constexpr bvec<n> operator>=(const vec<T1, n> & v1, const vec<T2, n> & v2);
    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2> nodisc constexpr bvec<n> operator>=(const vec<T1, n> & v1, T2 v2);
    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2> nodisc constexpr bvec<n> operator>=(T1 v1, const vec<T2, n> & v2);

    template <int n> nodisc constexpr bvec<n> operator&&(bvec<n> v1, bvec<n> v2);

    template <int n> nodisc constexpr bvec<n> operator||(bvec<n> v1, bvec<n> v2);

    template <int n> nodisc constexpr bvec<n> operator!(bvec<n> v1);

    template <Numeric T, int n> nodisc constexpr T min(const vec<T, n> & v);
    template <Numeric T1, Numeric T2, int n, typename... Extra> nodisc constexpr auto min(const vec<T1, n> & v1, const vec<T2, n> & v2, Extra &&... extra);
    template <Numeric T1, Numeric T2, int n, typename... Extra> nodisc constexpr auto min(const vec<T1, n> & v1, T2 v2, Extra &&... extra);
    template <Numeric T1, Numeric T2, int n, typename... Extra> nodisc constexpr auto min(T1 v1, const vec<T2, n> & v2, Extra &&... extra);

    template <Numeric T, int n> nodisc constexpr T max(const vec<T, n> & v);
    template <Numeric T1, Numeric T2, int n, typename... Extra> nodisc constexpr auto max(const vec<T1, n> & v1, const vec<T2, n> & v2, Extra &&... extra);
    template <Numeric T1, Numeric T2, int n, typename... Extra> nodisc constexpr auto max(const vec<T1, n> & v1, T2 v2, Extra &&... extra);
    template <Numeric T1, Numeric T2, int n, typename... Extra> nodisc constexpr auto max(T1 v1, const vec<T2, n> & v2, Extra &&... extra);

    template <Numeric T1, SubOf<T1> T2, int n, typename... Extra> vec<T1, n> & minify(vec<T1, n> & v1, const vec<T2, n> & v2, Extra &&... extra);
    template <Numeric T1, SubOf<T1> T2, int n, typename... Extra> vec<T1, n> & minify(vec<T1, n> & v1, T2 v2, Extra &&... extra);

    template <Numeric T1, SubOf<T1> T2, int n, typename... Extra> vec<T1, n> & maxify(vec<T1, n> & v1, const vec<T2, n> & v2, Extra &&... extra);
    template <Numeric T1, SubOf<T1> T2, int n, typename... Extra> vec<T1, n> & maxify(vec<T1, n> & v1, T2 v2, Extra &&... extra);

    template <Numeric T> nodisc constexpr T median(vec3<T> v);

    template <Numeric T, int n> nodisc constexpr vec<T, n> clamp(const vec<T, n> & v, T min, T max);
    template <Numeric T, int n> nodisc constexpr vec<T, n> clamp(const vec<T, n> & v, const vec<T, n> & min, const vec<T, n> & max);

    template <Numeric T, int n> vec<T, n> & clampify(vec<T, n> & v, T min, T max);
    template <Numeric T, int n> vec<T, n> & clampify(vec<T, n> & v, const vec<T, n> & min, const vec<T, n> & max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <NumericOrBoolean T>
    forceinline constexpr vec<T, 2>::vec(const T v) :
        x{v},
        y{v}
    {}

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    forceinline constexpr vec<T, 2>::vec(const vec2<U> v) :
        x{T(v.x)},
        y{T(v.y)}
    {}

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    forceinline constexpr vec<T, 2>::vec(const vec3<U> v) :
        x{T(v.x)},
        y{T(v.y)}
    {}

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    forceinline constexpr vec<T, 2>::vec(const vec4<U> v) :
        x{T(v.x)},
        y{T(v.y)}
    {}

    template <NumericOrBoolean T>
    forceinline constexpr vec<T, 2>::vec(const T v1, const T v2) :
        x{v1},
        y{v2}
    {}

    template <NumericOrBoolean T>
    template <SubOf<T> U>
    forceinline vec2<T> & vec<T, 2>::operator=(const U v)
    {
        x = v;
        y = v;

        return *this;
    }

    template <NumericOrBoolean T>
    template <SubOf<T> U>
    forceinline vec2<T> & vec<T, 2>::operator=(const vec2<U> & v)
    {
        x = v.x;
        y = v.y;

        return *this;
    }

    template <NumericOrBoolean T>
    forceinline constexpr vec<T, 2>::operator bool() const
    {
        return x || y;
    }

    template <NumericOrBoolean T>
    template <int i>
    forceinline T & vec<T, 2>::at()
    {
        static_assert(i >= 0 && i <= 1, "Index out of bounds");
        if constexpr (i == 0) return x;
        if constexpr (i == 1) return y;
    }

    template <NumericOrBoolean T>
    template <int i>
    forceinline constexpr T vec<T, 2>::at() const
    {
        static_assert(i >= 0 && i <= 1, "Index out of bounds");
        if constexpr (i == 0) return x;
        if constexpr (i == 1) return y;
    }

    template <NumericOrBoolean T>
    forceinline T & vec<T, 2>::operator[](const int i)
    {
        return *(&x + i);
    }

    template <NumericOrBoolean T>
    forceinline T vec<T, 2>::operator[](const int i) const
    {
        return *(&x + i);
    }

    template <NumericOrBoolean T>
    forceinline constexpr vec<T, 3>::vec(const T v) :
        x{v},
        y{v},
        z{v}
    {}

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    forceinline constexpr vec<T, 3>::vec(const vec2<U> v) :
        x{T(v.x)},
        y{T(v.y)},
        z{}
    {}

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    forceinline constexpr vec<T, 3>::vec(const vec3<U> v) :
        x{T(v.x)},
        y{T(v.y)},
        z{T(v.z)}
    {}

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    forceinline constexpr vec<T, 3>::vec(const vec4<U> v) :
        x{T(v.x)},
        y{T(v.y)},
        z{T(v.z)}
    {}

    template <NumericOrBoolean T>
    forceinline constexpr vec<T, 3>::vec(const T v1, const T v2, const T v3) :
        x{v1},
        y{v2},
        z{v3}
    {}

    template <NumericOrBoolean T>
    forceinline constexpr vec<T, 3>::vec(const vec2<T> v1, const T v2) :
        x{v1.x},
        y{v1.y},
        z{v2}
    {}

    template <NumericOrBoolean T>
    forceinline constexpr vec<T, 3>::vec(const T v1, const vec2<T> v2) :
        x{v1},
        y{v2.x},
        z{v2.y}
    {}

    template <NumericOrBoolean T>
    template <SubOf<T> U>
    forceinline vec3<T> & vec<T, 3>::operator=(const U v)
    {
        x = v;
        y = v;
        z = v;

        return *this;
    }

    template <NumericOrBoolean T>
    template <SubOf<T> U>
    forceinline vec3<T> & vec<T, 3>::operator=(const vec2<U> & v)
    {
        x = v.x;
        y = v.y;
        z = T(0);

        return *this;
    }

    template <NumericOrBoolean T>
    template <SubOf<T> U>
    forceinline vec3<T> & vec<T, 3>::operator=(const vec3<U> & v)
    {
        x = v.x;
        y = v.y;
        z = v.z;

        return *this;
    }

    template <NumericOrBoolean T>
    forceinline constexpr vec<T, 3>::operator bool() const
    {
        return x || y || z;
    }

    template <NumericOrBoolean T>
    template <int i>
    forceinline T & vec<T, 3>::at()
    {
        static_assert(i >= 0 && i <= 2, "Index out of bounds");
        if constexpr (i == 0) return x;
        if constexpr (i == 1) return y;
        if constexpr (i == 2) return z;
    }

    template <NumericOrBoolean T>
    template <int i>
    forceinline constexpr T vec<T, 3>::at() const
    {
        static_assert(i >= 0 && i <= 2, "Index out of bounds");
        if constexpr (i == 0) return x;
        if constexpr (i == 1) return y;
        if constexpr (i == 2) return z;
    }

    template <NumericOrBoolean T>
    forceinline T & vec<T, 3>::operator[](const int i)
    {
        return *(&x + i);
    }

    template <NumericOrBoolean T>
    forceinline T vec<T, 3>::operator[](const int i) const
    {
        return *(&x + i);
    }

    template <NumericOrBoolean T>
    forceinline vec2<T> & vec<T, 3>::xy()
    {
        return reinterpret_cast<vec2<T> &>(x);
    }

    template <NumericOrBoolean T>
    forceinline constexpr vec2<T> vec<T, 3>::xy() const
    {
        return reinterpret_cast<const vec2<T> &>(x);
    }

    template <NumericOrBoolean T>
    forceinline vec2<T> & vec<T, 3>::yz()
    {
        return reinterpret_cast<vec2<T> &>(y);
    }

    template <NumericOrBoolean T>
    forceinline constexpr vec2<T> vec<T, 3>::yz() const
    {
        return reinterpret_cast<const vec2<T> &>(y);
    }

    template <NumericOrBoolean T>
    forceinline constexpr vec<T, 4>::vec(const T v) :
        x{v},
        y{v},
        z{v},
        w{v}
    {}

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    forceinline constexpr vec<T, 4>::vec(const vec2<U> v) :
        x{T(v.x)},
        y{T(v.y)},
        z{},
        w{}
    {}

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    forceinline constexpr vec<T, 4>::vec(const vec3<U> v) :
        x{T(v.x)},
        y{T(v.y)},
        z{T(v.z)},
        w{}
    {}

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    forceinline constexpr vec<T, 4>::vec(const vec4<U> v) :
        x{T(v.x)},
        y{T(v.y)},
        z{T(v.z)},
        w{T(v.w)}
    {}

    template <NumericOrBoolean T>
    forceinline constexpr vec<T, 4>::vec(const T v1, const T v2, const T v3, const T v4) :
        x{v1},
        y{v2},
        z{v3},
        w{v4}
    {}

    template <NumericOrBoolean T>
    forceinline constexpr vec<T, 4>::vec(const vec2<T> v1, const T v2, const T v3) :
        x{v1.x},
        y{v1.y},
        z{v2},
        w{v3}
    {}

    template <NumericOrBoolean T>
    forceinline constexpr vec<T, 4>::vec(const T v1, const vec2<T> v2, const T v3) :
        x{v1},
        y{v2.x},
        z{v2.y},
        w{v3}
    {}

    template <NumericOrBoolean T>
    forceinline constexpr vec<T, 4>::vec(const T v1, const T v2, const vec2<T> v3) :
        x{v1},
        y{v2},
        z{v3.x},
        w{v3.y}
    {}

    template <NumericOrBoolean T>
    forceinline constexpr vec<T, 4>::vec(const vec2<T> v1, const vec2<T> v2) :
        x{v1.x},
        y{v1.y},
        z{v2.x},
        w{v2.y}
    {}

    template <NumericOrBoolean T>
    forceinline constexpr vec<T, 4>::vec(const vec3<T> v1, const T v2) :
        x{v1.x},
        y{v1.y},
        z{v1.z},
        w{v2}
    {}

    template <NumericOrBoolean T>
    forceinline constexpr vec<T, 4>::vec(const T v1, const vec3<T> v2) :
        x{v1},
        y{v2.x},
        z{v2.y},
        w{v2.z}
    {}

    template <NumericOrBoolean T>
    template <SubOf<T> U>
    forceinline vec4<T> & vec<T, 4>::operator=(const U v)
    {
        x = v;
        y = v;
        z = v;
        w = v;

        return *this;
    }

    template <NumericOrBoolean T>
    template <SubOf<T> U>
    forceinline vec4<T> & vec<T, 4>::operator=(const vec2<U> & v)
    {
        x = v.x;
        y = v.y;
        z = T(0);
        w = T(0);

        return *this;
    }

    template <NumericOrBoolean T>
    template <SubOf<T> U>
    forceinline vec4<T> & vec<T, 4>::operator=(const vec3<U> & v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = T(0);

        return *this;
    }

    template <NumericOrBoolean T>
    template <SubOf<T> U>
    forceinline vec4<T> & vec<T, 4>::operator=(const vec4<U> & v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;

        return *this;
    }

    template <NumericOrBoolean T>
    forceinline constexpr vec<T, 4>::operator bool() const
    {
        return x || y || z || w;
    }

    template <NumericOrBoolean T>
    template <int i>
    forceinline T & vec<T, 4>::at()
    {
        static_assert(i >= 0 && i <= 3, "Index out of bounds");
        if constexpr (i == 0) return x;
        if constexpr (i == 1) return y;
        if constexpr (i == 2) return z;
        if constexpr (i == 3) return w;
    }

    template <NumericOrBoolean T>
    template <int i>
    forceinline constexpr T vec<T, 4>::at() const
    {
        static_assert(i >= 0 && i <= 3, "Index out of bounds");
        if constexpr (i == 0) return x;
        if constexpr (i == 1) return y;
        if constexpr (i == 2) return z;
        if constexpr (i == 3) return w;
    }

    template <NumericOrBoolean T>
    forceinline T & vec<T, 4>::operator[](const int i)
    {
        return *(&x + i);
    }

    template <NumericOrBoolean T>
    forceinline T vec<T, 4>::operator[](const int i) const
    {
        return *(&x + i);
    }

    template <NumericOrBoolean T>
    forceinline vec2<T> & vec<T, 4>::xy()
    {
        return reinterpret_cast<vec2<T> &>(x);
    }

    template <NumericOrBoolean T>
    forceinline constexpr vec2<T> vec<T, 4>::xy() const
    {
        return reinterpret_cast<const vec2<T> &>(x);
    }

    template <NumericOrBoolean T>
    forceinline vec2<T> & vec<T, 4>::yz()
    {
        return reinterpret_cast<vec2<T> &>(y);
    }

    template <NumericOrBoolean T>
    forceinline constexpr vec2<T> vec<T, 4>::yz() const
    {
        return reinterpret_cast<const vec2<T> &>(y);
    }

    template <NumericOrBoolean T>
    forceinline vec2<T> & vec<T, 4>::zw()
    {
        return reinterpret_cast<vec2<T> &>(z);
    }

    template <NumericOrBoolean T>
    forceinline constexpr vec2<T> vec<T, 4>::zw() const
    {
        return reinterpret_cast<const vec2<T> &>(z);
    }

    template <NumericOrBoolean T>
    forceinline vec3<T> & vec<T, 4>::xyz()
    {
        return reinterpret_cast<vec3<T> &>(x);
    }

    template <NumericOrBoolean T>
    forceinline constexpr vec3<T> vec<T, 4>::xyz() const
    {
        return reinterpret_cast<const vec3<T> &>(x);
    }

    template <NumericOrBoolean T>
    forceinline vec3<T> & vec<T, 4>::yzw()
    {
        return reinterpret_cast<vec3<T> &>(y);
    }

    template <NumericOrBoolean T>
    forceinline constexpr vec3<T> vec<T, 4>::yzw() const
    {
        return reinterpret_cast<const vec3<T> &>(y);
    }

    template <Numeric T, int n>
    forceinline vec<T, n> & operator++(vec<T, n> & v)
    {
        if constexpr (n >= 1) ++v.x;
        if constexpr (n >= 2) ++v.y;
        if constexpr (n >= 3) ++v.z;
        if constexpr (n >= 4) ++v.w;
        return v;
    }

    template <Numeric T, int n>
    forceinline vec<T, n> operator++(vec<T, n> & v, int)
    {
        vec<T, n> temp(v);
        ++v;
        return temp;
    }

    template <Numeric T, int n>
    forceinline vec<T, n> & operator--(vec<T, n> & v)
    {
        if constexpr (n >= 1) --v.x;
        if constexpr (n >= 2) --v.y;
        if constexpr (n >= 3) --v.z;
        if constexpr (n >= 4) --v.w;
        return v;
    }

    template <Numeric T, int n>
    forceinline vec<T, n> operator--(vec<T, n> & v, int)
    {
        vec<T, n> temp(v);
        --v;
        return temp;
    }

    template <Numeric T1, SubOf<T1> T2, int n>
    forceinline vec<T1, n> & operator+=(vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        if constexpr (n >= 1) v1.x += v2.x;
        if constexpr (n >= 2) v1.y += v2.y;
        if constexpr (n >= 3) v1.z += v2.z;
        if constexpr (n >= 4) v1.w += v2.w;
        return v1;
    }

    template <Numeric T1, SubOf<T1> T2, int n>
    forceinline vec<T1, n> & operator+=(vec<T1, n> & v1, const T2 v2)
    {
        if constexpr (n >= 1) v1.x += v2;
        if constexpr (n >= 2) v1.y += v2;
        if constexpr (n >= 3) v1.z += v2;
        if constexpr (n >= 4) v1.w += v2;
        return v1;
    }

    template <Numeric T1, SubOf<T1> T2, int n>
    forceinline vec<T1, n> & operator-=(vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        if constexpr (n >= 1) v1.x -= v2.x;
        if constexpr (n >= 2) v1.y -= v2.y;
        if constexpr (n >= 3) v1.z -= v2.z;
        if constexpr (n >= 4) v1.w -= v2.w;
        return v1;
    }

    template <Numeric T1, SubOf<T1> T2, int n>
    forceinline vec<T1, n> & operator-=(vec<T1, n> & v1, const T2 v2)
    {
        if constexpr (n >= 1) v1.x -= v2;
        if constexpr (n >= 2) v1.y -= v2;
        if constexpr (n >= 3) v1.z -= v2;
        if constexpr (n >= 4) v1.w -= v2;
        return v1;
    }

    template <Numeric T1, SubOf<T1> T2, int n>
    forceinline vec<T1, n> & operator*=(vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        if constexpr (n >= 1) v1.x *= v2.x;
        if constexpr (n >= 2) v1.y *= v2.y;
        if constexpr (n >= 3) v1.z *= v2.z;
        if constexpr (n >= 4) v1.w *= v2.w;
        return v1;
    }

    template <Numeric T1, SubOf<T1> T2, int n>
    forceinline vec<T1, n> & operator*=(vec<T1, n> & v1, const T2 v2)
    {
        if constexpr (n >= 1) v1.x *= v2;
        if constexpr (n >= 2) v1.y *= v2;
        if constexpr (n >= 3) v1.z *= v2;
        if constexpr (n >= 4) v1.w *= v2;
        return v1;
    }

    template <Numeric T1, SubOf<T1> T2, int n>
    forceinline vec<T1, n> & operator/=(vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        if constexpr (n >= 1) v1.x /= v2.x;
        if constexpr (n >= 2) v1.y /= v2.y;
        if constexpr (n >= 3) v1.z /= v2.z;
        if constexpr (n >= 4) v1.w /= v2.w;
        return v1;
    }

    template <Numeric T1, SubOf<T1> T2, int n>
    forceinline vec<T1, n> & operator/=(vec<T1, n> & v1, const T2 v2)
    {
        if constexpr (Floating<T1>)
        {
            return v1 *= T2(1.0) / v2;
        }
        else
        {
            if constexpr (n >= 1) v1.x /= v2;
            if constexpr (n >= 2) v1.y /= v2;
            if constexpr (n >= 3) v1.z /= v2;
            if constexpr (n >= 4) v1.w /= v2;
            return v1;
        }
    }

    template <Numeric T1, SubOf<T1> T2, int n>
    forceinline vec<T1, n> & operator%=(vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        if constexpr (n >= 1) v1.x = mod(v1.x, T1(v2.x));
        if constexpr (n >= 2) v1.y = mod(v1.y, T1(v2.y));
        if constexpr (n >= 3) v1.z = mod(v1.z, T1(v2.z));
        if constexpr (n >= 4) v1.w = mod(v1.w, T1(v2.w));
        return v1;
    }

    template <Numeric T1, SubOf<T1> T2, int n>
    forceinline vec<T1, n> & operator%=(vec<T1, n> & v1, const T2 v2)
    {
        if constexpr (n >= 1) v1.x = mod(v1.x, T1(v2));
        if constexpr (n >= 2) v1.y = mod(v1.y, T1(v2));
        if constexpr (n >= 3) v1.z = mod(v1.z, T1(v2));
        if constexpr (n >= 4) v1.w = mod(v1.w, T1(v2));
        return v1;
    }

    template <UnsignedIntegral T1, UnsignedSubOf<T1> T2, int n>
    forceinline vec<T1, n> & operator&=(vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        if constexpr (n >= 1) v1.x &= v2.x;
        if constexpr (n >= 2) v1.y &= v2.y;
        if constexpr (n >= 3) v1.z &= v2.z;
        if constexpr (n >= 4) v1.w &= v2.w;
        return v1;
    }

    template <UnsignedIntegral T1, UnsignedSubOf<T1> T2, int n>
    forceinline vec<T1, n> & operator&=(vec<T1, n> & v1, const T2 v2)
    {
        if constexpr (n >= 1) v1.x &= v2;
        if constexpr (n >= 2) v1.y &= v2;
        if constexpr (n >= 3) v1.z &= v2;
        if constexpr (n >= 4) v1.w &= v2;
        return v1;
    }

    template <UnsignedIntegral T1, UnsignedSubOf<T1> T2, int n>
    forceinline vec<T1, n> & operator|=(vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        if constexpr (n >= 1) v1.x |= v2.x;
        if constexpr (n >= 2) v1.y |= v2.y;
        if constexpr (n >= 3) v1.z |= v2.z;
        if constexpr (n >= 4) v1.w |= v2.w;
        return v1;
    }

    template <UnsignedIntegral T1, UnsignedSubOf<T1> T2, int n>
    forceinline vec<T1, n> & operator|=(vec<T1, n> & v1, const T2 v2)
    {
        if constexpr (n >= 1) v1.x |= v2;
        if constexpr (n >= 2) v1.y |= v2;
        if constexpr (n >= 3) v1.z |= v2;
        if constexpr (n >= 4) v1.w |= v2;
        return v1;
    }

    template <UnsignedIntegral T1, UnsignedSubOf<T1> T2, int n>
    forceinline vec<T1, n> & operator^=(vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        if constexpr (n >= 1) v1.x ^= v2.x;
        if constexpr (n >= 2) v1.y ^= v2.y;
        if constexpr (n >= 3) v1.z ^= v2.z;
        if constexpr (n >= 4) v1.w ^= v2.w;
        return v1;
    }

    template <UnsignedIntegral T1, UnsignedSubOf<T1> T2, int n>
    forceinline vec<T1, n> & operator^=(vec<T1, n> & v1, const T2 v2)
    {
        if constexpr (n >= 1) v1.x ^= v2;
        if constexpr (n >= 2) v1.y ^= v2;
        if constexpr (n >= 3) v1.z ^= v2;
        if constexpr (n >= 4) v1.w ^= v2;
        return v1;
    }

    template <UnsignedIntegral T, int n>
    forceinline vec<T, n> & operator<<=(vec<T, n> & v1, const int v2)
    {
        if constexpr (n >= 1) v1.x <<= v2;
        if constexpr (n >= 2) v1.y <<= v2;
        if constexpr (n >= 3) v1.z <<= v2;
        if constexpr (n >= 4) v1.w <<= v2;
        return v1;
    }

    template <UnsignedIntegral T, int n>
    forceinline vec<T, n> & operator>>=(vec<T, n> & v1, const int v2)
    {
        if constexpr (n >= 1) v1.x >>= v2;
        if constexpr (n >= 2) v1.y >>= v2;
        if constexpr (n >= 3) v1.z >>= v2;
        if constexpr (n >= 4) v1.w >>= v2;
        return v1;
    }

    template <Numeric T, int n>
    forceinline constexpr vec<T, n> operator+(const vec<T, n> & v)
    {
        return v;
    }

    template <Numeric T, int n>
    forceinline constexpr vec<T, n> operator-(const vec<T, n> & v)
    {
        if constexpr (UnsignedIntegral<T>)
        {
            return v;
        }
        else
        {
            if constexpr (n == 2) return {T(-v.x), T(-v.y)};
            if constexpr (n == 3) return {T(-v.x), T(-v.y), T(-v.z)};
            if constexpr (n == 4) return {T(-v.x), T(-v.y), T(-v.z), T(-v.w)};
        }
    }

    template <UnsignedIntegral T, int n>
    forceinline constexpr vec<T, n> operator~(const vec<T, n> & v)
    {
        if constexpr (n == 2) return {T(~v.x), T(~v.y)};
        if constexpr (n == 3) return {T(~v.x), T(~v.y), T(~v.z)};
        if constexpr (n == 4) return {T(~v.x), T(~v.y), T(~v.z), T(~v.w)};
    }

    template <Numeric T1, Numeric T2, int n>
    forceinline constexpr vec<Common<T1, T2>, n> operator+(const vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        using T = Common<T1, T2>;
        if constexpr (n == 2) return {T(v1.x + v2.x), T(v1.y + v2.y)};
        if constexpr (n == 3) return {T(v1.x + v2.x), T(v1.y + v2.y), T(v1.z + v2.z)};
        if constexpr (n == 4) return {T(v1.x + v2.x), T(v1.y + v2.y), T(v1.z + v2.z), T(v1.w + v2.w)};
    }

    template <Numeric T1, Numeric T2, int n>
    forceinline constexpr vec<Common<T1, T2>, n> operator+(const vec<T1, n> & v1, const T2 v2)
    {
        using T = Common<T1, T2>;
        if constexpr (n == 2) return {T(v1.x + v2), T(v1.y + v2)};
        if constexpr (n == 3) return {T(v1.x + v2), T(v1.y + v2), T(v1.z + v2)};
        if constexpr (n == 4) return {T(v1.x + v2), T(v1.y + v2), T(v1.z + v2), T(v1.w + v2)};
    }

    template <Numeric T1, Numeric T2, int n>
    forceinline constexpr vec<Common<T1, T2>, n> operator+(const T1 v1, const vec<T2, n> & v2)
    {
        return v2 + v1;
    }

    template <Numeric T1, Numeric T2, int n>
    forceinline constexpr vec<Common<T1, T2>, n> operator-(const vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        using T = Common<T1, T2>;
        if constexpr (n == 2) return {T(v1.x - v2.x), T(v1.y - v2.y)};
        if constexpr (n == 3) return {T(v1.x - v2.x), T(v1.y - v2.y), T(v1.z - v2.z)};
        if constexpr (n == 4) return {T(v1.x - v2.x), T(v1.y - v2.y), T(v1.z - v2.z), T(v1.w - v2.w)};
    }

    template <Numeric T1, Numeric T2, int n>
    forceinline constexpr vec<Common<T1, T2>, n> operator-(const vec<T1, n> & v1, const T2 v2)
    {
        using T = Common<T1, T2>;
        if constexpr (n == 2) return {T(v1.x - v2), T(v1.y - v2)};
        if constexpr (n == 3) return {T(v1.x - v2), T(v1.y - v2), T(v1.z - v2)};
        if constexpr (n == 4) return {T(v1.x - v2), T(v1.y - v2), T(v1.z - v2), T(v1.w - v2)};
    }

    template <Numeric T1, Numeric T2, int n>
    forceinline constexpr vec<Common<T1, T2>, n> operator-(const T1 v1, const vec<T2, n> & v2)
    {
        using T = Common<T1, T2>;
        if constexpr (n == 2) return {T(v1 - v2.x), T(v1 - v2.y)};
        if constexpr (n == 3) return {T(v1 - v2.x), T(v1 - v2.y), T(v1 - v2.z)};
        if constexpr (n == 4) return {T(v1 - v2.x), T(v1 - v2.y), T(v1 - v2.z), T(v1 - v2.w)};
    }

    template <Numeric T1, Numeric T2, int n>
    forceinline constexpr vec<Common<T1, T2>, n> operator*(const vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        using T = Common<T1, T2>;
        if constexpr (n == 2) return {T(v1.x * v2.x), T(v1.y * v2.y)};
        if constexpr (n == 3) return {T(v1.x * v2.x), T(v1.y * v2.y), T(v1.z * v2.z)};
        if constexpr (n == 4) return {T(v1.x * v2.x), T(v1.y * v2.y), T(v1.z * v2.z), T(v1.w * v2.w)};
    }

    template <Numeric T1, Numeric T2, int n>
    forceinline constexpr vec<Common<T1, T2>, n> operator*(const vec<T1, n> & v1, const T2 v2)
    {
        using T = Common<T1, T2>;
        if constexpr (n == 2) return {T(v1.x * v2), T(v1.y * v2)};
        if constexpr (n == 3) return {T(v1.x * v2), T(v1.y * v2), T(v1.z * v2)};
        if constexpr (n == 4) return {T(v1.x * v2), T(v1.y * v2), T(v1.z * v2), T(v1.w * v2)};
    }

    template <Numeric T1, Numeric T2, int n>
    forceinline constexpr vec<Common<T1, T2>, n> operator*(const T1 v1, const vec<T2, n> & v2)
    {
        using T = Common<T1, T2>;
        if constexpr (n == 2) return {T(v1 * v2.x), T(v1 * v2.y)};
        if constexpr (n == 3) return {T(v1 * v2.x), T(v1 * v2.y), T(v1 * v2.z)};
        if constexpr (n == 4) return {T(v1 * v2.x), T(v1 * v2.y), T(v1 * v2.z), T(v1 * v2.w)};
    }

    template <Numeric T1, Numeric T2, int n>
    forceinline constexpr vec<Common<T1, T2>, n> operator/(const vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        using T = Common<T1, T2>;
        if constexpr (n == 2) return {T(v1.x / v2.x), T(v1.y / v2.y)};
        if constexpr (n == 3) return {T(v1.x / v2.x), T(v1.y / v2.y), T(v1.z / v2.z)};
        if constexpr (n == 4) return {T(v1.x / v2.x), T(v1.y / v2.y), T(v1.z / v2.z), T(v1.w / v2.w)};
    }

    template <Numeric T1, Numeric T2, int n>
    forceinline constexpr vec<Common<T1, T2>, n> operator/(const vec<T1, n> & v1, const T2 v2)
    {
        using T = Common<T1, T2>;
        if constexpr (Floating<T>)
        {
            return v1 * (T(1.0) / v2);
        }
        else
        {
            if constexpr (n == 2) return {T(v1.x / v2), T(v1.y / v2)};
            if constexpr (n == 3) return {T(v1.x / v2), T(v1.y / v2), T(v1.z / v2)};
            if constexpr (n == 4) return {T(v1.x / v2), T(v1.y / v2), T(v1.z / v2), T(v1.w / v2)};
        }
    }

    template <Numeric T1, Numeric T2, int n>
    forceinline constexpr vec<Common<T1, T2>, n> operator/(const T1 v1, const vec<T2, n> & v2)
    {
        using T = Common<T1, T2>;
        if constexpr (n == 2) return {T(v1 / v2.x), T(v1 / v2.y)};
        if constexpr (n == 3) return {T(v1 / v2.x), T(v1 / v2.y), T(v1 / v2.z)};
        if constexpr (n == 4) return {T(v1 / v2.x), T(v1 / v2.y), T(v1 / v2.z), T(v1 / v2.w)};
    }

    template <Numeric T1, Numeric T2, int n>
    forceinline constexpr vec<Common<T1, T2>, n> operator%(const vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        using T = Common<T1, T2>;
        if constexpr (n == 2) return {mod(T(v1.x), T(v2.x)), mod(T(v1.y), T(v2.y))};
        if constexpr (n == 3) return {mod(T(v1.x), T(v2.x)), mod(T(v1.y), T(v2.y)), mod(T(v1.z), T(v2.z))};
        if constexpr (n == 4) return {mod(T(v1.x), T(v2.x)), mod(T(v1.y), T(v2.y)), mod(T(v1.z), T(v2.z)), mod(T(v1.w), T(v2.w))};
    }

    template <Numeric T1, Numeric T2, int n>
    forceinline constexpr vec<Common<T1, T2>, n> operator%(const vec<T1, n> & v1, const T2 v2)
    {
        using T = Common<T1, T2>;
        if constexpr (n == 2) return {mod(T(v1.x), T(v2)), mod(T(v1.y), T(v2))};
        if constexpr (n == 3) return {mod(T(v1.x), T(v2)), mod(T(v1.y), T(v2)), mod(T(v1.z), T(v2))};
        if constexpr (n == 4) return {mod(T(v1.x), T(v2)), mod(T(v1.y), T(v2)), mod(T(v1.z), T(v2)), mod(T(v1.w), T(v2))};
    }

    template <Numeric T1, Numeric T2, int n>
    forceinline constexpr vec<Common<T1, T2>, n> operator%(const T1 v1, const vec<T2, n> & v2)
    {
        using T = Common<T1, T2>;
        if constexpr (n == 2) return {mod(T(v1), T(v2.x)), mod(T(v1), T(v2.y))};
        if constexpr (n == 3) return {mod(T(v1), T(v2.x)), mod(T(v1), T(v2.y)), mod(T(v1), T(v2.z))};
        if constexpr (n == 4) return {mod(T(v1), T(v2.x)), mod(T(v1), T(v2.y)), mod(T(v1), T(v2.z)), mod(T(v1), T(v2.w))};
    }

    template <UnsignedIntegral T1, UnsignedIntegral T2, int n>
    forceinline constexpr vec<LargerOf<T1, T2>, n> operator&(const vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        using T = LargerOf<T1, T2>;
        if constexpr (n == 2) return {T(v1.x & v2.x), T(v1.y & v2.y)};
        if constexpr (n == 3) return {T(v1.x & v2.x), T(v1.y & v2.y), T(v1.z & v2.z)};
        if constexpr (n == 4) return {T(v1.x & v2.x), T(v1.y & v2.y), T(v1.z & v2.z), T(v1.w & v2.w)};
    }

    template <UnsignedIntegral T1, UnsignedIntegral T2, int n>
    forceinline constexpr vec<LargerOf<T1, T2>, n> operator&(const vec<T1, n> & v1, const T2 v2)
    {
        using T = LargerOf<T1, T2>;
        if constexpr (n == 2) return {T(v1.x & v2), T(v1.y & v2)};
        if constexpr (n == 3) return {T(v1.x & v2), T(v1.y & v2), T(v1.z & v2)};
        if constexpr (n == 4) return {T(v1.x & v2), T(v1.y & v2), T(v1.z & v2), T(v1.w & v2)};
    }

    template <UnsignedIntegral T1, UnsignedIntegral T2, int n>
    forceinline constexpr vec<LargerOf<T1, T2>, n> operator&(const T1 v1, const vec<T2, n> & v2)
    {
        using T = LargerOf<T1, T2>;
        if constexpr (n == 2) return {T(v1 & v2.x), T(v1 & v2.y)};
        if constexpr (n == 3) return {T(v1 & v2.x), T(v1 & v2.y), T(v1 & v2.z)};
        if constexpr (n == 4) return {T(v1 & v2.x), T(v1 & v2.y), T(v1 & v2.z), T(v1 & v2.w)};
    }

    template <UnsignedIntegral T1, UnsignedIntegral T2, int n>
    forceinline constexpr vec<LargerOf<T1, T2>, n> operator|(const vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        using T = LargerOf<T1, T2>;
        if constexpr (n == 2) return {T(v1.x | v2.x), T(v1.y | v2.y)};
        if constexpr (n == 3) return {T(v1.x | v2.x), T(v1.y | v2.y), T(v1.z | v2.z)};
        if constexpr (n == 4) return {T(v1.x | v2.x), T(v1.y | v2.y), T(v1.z | v2.z), T(v1.w | v2.w)};
    }

    template <UnsignedIntegral T1, UnsignedIntegral T2, int n>
    forceinline constexpr vec<LargerOf<T1, T2>, n> operator|(const vec<T1, n> & v1, const T2 v2)
    {
        using T = LargerOf<T1, T2>;
        if constexpr (n == 2) return {T(v1.x | v2), T(v1.y | v2)};
        if constexpr (n == 3) return {T(v1.x | v2), T(v1.y | v2), T(v1.z | v2)};
        if constexpr (n == 4) return {T(v1.x | v2), T(v1.y | v2), T(v1.z | v2), T(v1.w | v2)};
    }

    template <UnsignedIntegral T1, UnsignedIntegral T2, int n>
    forceinline constexpr vec<LargerOf<T1, T2>, n> operator|(const T1 v1, const vec<T2, n> & v2)
    {
        using T = LargerOf<T1, T2>;
        if constexpr (n == 2) return {T(v1 | v2.x), T(v1 | v2.y)};
        if constexpr (n == 3) return {T(v1 | v2.x), T(v1 | v2.y), T(v1 | v2.z)};
        if constexpr (n == 4) return {T(v1 | v2.x), T(v1 | v2.y), T(v1 | v2.z), T(v1 | v2.w)};
    }

    template <UnsignedIntegral T1, UnsignedIntegral T2, int n>
    forceinline constexpr vec<LargerOf<T1, T2>, n> operator^(const vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        using T = LargerOf<T1, T2>;
        if constexpr (n == 2) return {T(v1.x ^ v2.x), T(v1.y ^ v2.y)};
        if constexpr (n == 3) return {T(v1.x ^ v2.x), T(v1.y ^ v2.y), T(v1.z ^ v2.z)};
        if constexpr (n == 4) return {T(v1.x ^ v2.x), T(v1.y ^ v2.y), T(v1.z ^ v2.z), T(v1.w ^ v2.w)};
    }

    template <UnsignedIntegral T1, UnsignedIntegral T2, int n>
    forceinline constexpr vec<LargerOf<T1, T2>, n> operator^(const vec<T1, n> & v1, const T2 v2)
    {
        using T = LargerOf<T1, T2>;
        if constexpr (n == 2) return {T(v1.x ^ v2), T(v1.y ^ v2)};
        if constexpr (n == 3) return {T(v1.x ^ v2), T(v1.y ^ v2), T(v1.z ^ v2)};
        if constexpr (n == 4) return {T(v1.x ^ v2), T(v1.y ^ v2), T(v1.z ^ v2), T(v1.w ^ v2)};
    }

    template <UnsignedIntegral T1, UnsignedIntegral T2, int n>
    forceinline constexpr vec<LargerOf<T1, T2>, n> operator^(const T1 v1, const vec<T2, n> & v2)
    {
        using T = LargerOf<T1, T2>;
        if constexpr (n == 2) return {T(v1 ^ v2.x), T(v1 ^ v2.y)};
        if constexpr (n == 3) return {T(v1 ^ v2.x), T(v1 ^ v2.y), T(v1 ^ v2.z)};
        if constexpr (n == 4) return {T(v1 ^ v2.x), T(v1 ^ v2.y), T(v1 ^ v2.z), T(v1 ^ v2.w)};
    }

    template <UnsignedIntegral T, int n>
    forceinline constexpr vec<T, n> operator<<(const vec<T, n> & v1, const int v2)
    {
        if constexpr (n == 2) return {T(v1.x << v2), T(v1.y << v2)};
        if constexpr (n == 3) return {T(v1.x << v2), T(v1.y << v2), T(v1.z << v2)};
        if constexpr (n == 4) return {T(v1.x << v2), T(v1.y << v2), T(v1.z << v2), T(v1.w << v2)};
    }

    template <UnsignedIntegral T, int n>
    forceinline constexpr vec<T, n> operator>>(const vec<T, n> & v1, const int v2)
    {
        if constexpr (n == 2) return {T(v1.x >> v2), T(v1.y >> v2)};
        if constexpr (n == 3) return {T(v1.x >> v2), T(v1.y >> v2), T(v1.z >> v2)};
        if constexpr (n == 4) return {T(v1.x >> v2), T(v1.y >> v2), T(v1.z >> v2), T(v1.w >> v2)};
    }

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2>
    forceinline constexpr bvec<n> operator==(const vec<T1, n> & v1, const T2 v2)
    {
        if constexpr (n == 2) return {v1.x == v2, v1.y == v2};
        if constexpr (n == 3) return {v1.x == v2, v1.y == v2, v1.z == v2};
        if constexpr (n == 4) return {v1.x == v2, v1.y == v2, v1.z == v2, v1.w == v2};
    }

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2>
    forceinline constexpr bvec<n> operator==(const T1 v1, const vec<T2, n> & v2)
    {
        return v2 == v1;
    }

    template <int n>
    forceinline constexpr bvec<n> operator==(const bvec<n> & v1, const bool v2)
    {
        if constexpr (n == 2) return {v1.x == v2, v1.y == v2};
        if constexpr (n == 3) return {v1.x == v2, v1.y == v2, v1.z == v2};
        if constexpr (n == 4) return {v1.x == v2, v1.y == v2, v1.z == v2, v1.w == v2};
    }

    template <int n>
    forceinline constexpr bvec<n> operator==(const bool v1, const bvec<n> & v2)
    {
        return v2 == v1;
    }

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2>
    inline constexpr bvec<n> operator!=(const vec<T1, n> & v1, const T2 v2)
    {
        return !(v1 == v2);
    }

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2>
    inline constexpr bvec<n> operator!=(const T1 v1, const vec<T2, n> & v2)
    {
        return !(v1 == v2);
    }

    template <int n>
    inline constexpr bvec<n> operator!=(const bvec<n> & v1, const bool v2)
    {
        return !(v1 == v2);
    }

    template <int n>
    inline constexpr bvec<n> operator!=(const bool v1, const bvec<n> & v2)
    {
        return !(v1 == v2);
    }

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2>
    forceinline constexpr bvec<n> operator<(const vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        if constexpr (n == 2) return {v1.x < v2.x, v1.y < v2.y};
        if constexpr (n == 3) return {v1.x < v2.x, v1.y < v2.y, v1.z < v2.z};
        if constexpr (n == 4) return {v1.x < v2.x, v1.y < v2.y, v1.z < v2.z, v1.w < v2.w};
    }

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2>
    forceinline constexpr bvec<n> operator<(const vec<T1, n> & v1, const T2 v2)
    {
        if constexpr (n == 2) return {v1.x < v2, v1.y < v2};
        if constexpr (n == 3) return {v1.x < v2, v1.y < v2, v1.z < v2};
        if constexpr (n == 4) return {v1.x < v2, v1.y < v2, v1.z < v2, v1.w < v2};
    }

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2>
    forceinline constexpr bvec<n> operator<(const T1 v1, const vec<T2, n> & v2)
    {
        if constexpr (n == 2) return {v1 < v2.x, v1 < v2.y};
        if constexpr (n == 3) return {v1 < v2.x, v1 < v2.y, v1 < v2.z};
        if constexpr (n == 4) return {v1 < v2.x, v1 < v2.y, v1 < v2.z, v1 < v2.w};
    }

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2>
    forceinline constexpr bvec<n> operator>(const vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        if constexpr (n == 2) return {v1.x > v2.x, v1.y > v2.y};
        if constexpr (n == 3) return {v1.x > v2.x, v1.y > v2.y, v1.z > v2.z};
        if constexpr (n == 4) return {v1.x > v2.x, v1.y > v2.y, v1.z > v2.z, v1.w > v2.w};
    }

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2>
    forceinline constexpr bvec<n> operator>(const vec<T1, n> & v1, const T2 v2)
    {
        if constexpr (n == 2) return {v1.x > v2, v1.y > v2};
        if constexpr (n == 3) return {v1.x > v2, v1.y > v2, v1.z > v2};
        if constexpr (n == 4) return {v1.x > v2, v1.y > v2, v1.z > v2, v1.w > v2};
    }

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2>
    forceinline constexpr bvec<n> operator>(const T1 v1, const vec<T2, n> & v2)
    {
        if constexpr (n == 2) return {v1 > v2.x, v1 > v2.y};
        if constexpr (n == 3) return {v1 > v2.x, v1 > v2.y, v1 > v2.z};
        if constexpr (n == 4) return {v1 > v2.x, v1 > v2.y, v1 > v2.z, v1 > v2.w};
    }

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2>
    forceinline constexpr bvec<n> operator<=(const vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        if constexpr (n == 2) return {v1.x <= v2.x, v1.y <= v2.y};
        if constexpr (n == 3) return {v1.x <= v2.x, v1.y <= v2.y, v1.z <= v2.z};
        if constexpr (n == 4) return {v1.x <= v2.x, v1.y <= v2.y, v1.z <= v2.z, v1.w <= v2.w};
    }

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2>
    forceinline constexpr bvec<n> operator<=(const vec<T1, n> & v1, const T2 v2)
    {
        if constexpr (n == 2) return {v1.x <= v2, v1.y <= v2};
        if constexpr (n == 3) return {v1.x <= v2, v1.y <= v2, v1.z <= v2};
        if constexpr (n == 4) return {v1.x <= v2, v1.y <= v2, v1.z <= v2, v1.w <= v2};
    }

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2>
    forceinline constexpr bvec<n> operator<=(const T1 v1, const vec<T2, n> & v2)
    {
        if constexpr (n == 2) return {v1 <= v2.x, v1 <= v2.y};
        if constexpr (n == 3) return {v1 <= v2.x, v1 <= v2.y, v1 <= v2.z};
        if constexpr (n == 4) return {v1 <= v2.x, v1 <= v2.y, v1 <= v2.z, v1 <= v2.w};
    }

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2>
    forceinline constexpr bvec<n> operator>=(const vec<T1, n> & v1, const vec<T2, n> & v2)
    {
        if constexpr (n == 2) return {v1.x >= v2.x, v1.y >= v2.y};
        if constexpr (n == 3) return {v1.x >= v2.x, v1.y >= v2.y, v1.z >= v2.z};
        if constexpr (n == 4) return {v1.x >= v2.x, v1.y >= v2.y, v1.z >= v2.z, v1.w >= v2.w};
    }

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2>
    forceinline constexpr bvec<n> operator>=(const vec<T1, n> & v1, const T2 v2)
    {
        if constexpr (n == 2) return {v1.x >= v2, v1.y >= v2};
        if constexpr (n == 3) return {v1.x >= v2, v1.y >= v2, v1.z >= v2};
        if constexpr (n == 4) return {v1.x >= v2, v1.y >= v2, v1.z >= v2, v1.w >= v2};
    }

    template <Numeric T1, Numeric T2, int n> requires CommonExists<T1, T2>
    forceinline constexpr bvec<n> operator>=(const T1 v1, const vec<T2, n> & v2)
    {
        if constexpr (n == 2) return {v1 >= v2.x, v1 >= v2.y};
        if constexpr (n == 3) return {v1 >= v2.x, v1 >= v2.y, v1 >= v2.z};
        if constexpr (n == 4) return {v1 >= v2.x, v1 >= v2.y, v1 >= v2.z, v1 >= v2.w};
    }

    template <int n>
    forceinline constexpr bvec<n> operator&&(const bvec<n> v1, const bvec<n> v2)
    {
        if constexpr (n == 2) return {v1.x && v2.x, v1.y && v2.y};
        if constexpr (n == 3) return {v1.x && v2.x, v1.y && v2.y, v1.z && v2.z};
        if constexpr (n == 4) return {v1.x && v2.x, v1.y && v2.y, v1.z && v2.z, v1.w && v2.w};
    }

    template <int n>
    forceinline constexpr bvec<n> operator||(const bvec<n> v1, const bvec<n> v2)
    {
        if constexpr (n == 2) return {v1.x || v2.x, v1.y || v2.y};
        if constexpr (n == 3) return {v1.x || v2.x, v1.y || v2.y, v1.z || v2.z};
        if constexpr (n == 4) return {v1.x || v2.x, v1.y || v2.y, v1.z || v2.z, v1.w || v2.w};
    }

    template <int n>
    forceinline constexpr bvec<n> operator!(const bvec<n> v)
    {
        if constexpr (n == 2) return {!v.x, !v.y};
        if constexpr (n == 3) return {!v.x, !v.y, !v.z};
        if constexpr (n == 4) return {!v.x, !v.y, !v.z, !v.w};
    }

    template <Numeric T, int n>
    forceinline constexpr T min(const vec<T, n> & v)
    {
        if constexpr (n == 2) return min(v.x, v.y);
        if constexpr (n == 3) return min(v.x, v.y, v.z);
        if constexpr (n == 4) return min(v.x, v.y, v.z, v.w);
    }

    template <Numeric T1, Numeric T2, int n, typename... Extra>
    forceinline constexpr auto min(const vec<T1, n> & v1, const vec<T2, n> & v2, Extra &&... extras)
    {
        if constexpr (sizeof...(Extra))
        {
            return min(min(v1, v2), std::forward<Extra>(extras)...);
        }
        else
        {
            if constexpr (n == 2) return vec<Common<T1, T2>, n>{min(v1.x, v2.x), min(v1.y, v2.y)};
            if constexpr (n == 3) return vec<Common<T1, T2>, n>{min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z)};
            if constexpr (n == 4) return vec<Common<T1, T2>, n>{min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z), min(v1.w, v2.w)};
        }
    }

    template <Numeric T1, Numeric T2, int n, typename... Extra>
    forceinline constexpr auto min(const vec<T1, n> & v1, const T2 v2, Extra &&... extras)
    {
        if constexpr (sizeof...(Extra))
        {
            return min(min(v1, v2), std::forward<Extra>(extras)...);
        }
        else
        {
            if constexpr (n == 2) return vec<Common<T1, T2>, n>{min(v1.x, v2), min(v1.y, v2)};
            if constexpr (n == 3) return vec<Common<T1, T2>, n>{min(v1.x, v2), min(v1.y, v2), min(v1.z, v2)};
            if constexpr (n == 4) return vec<Common<T1, T2>, n>{min(v1.x, v2), min(v1.y, v2), min(v1.z, v2), min(v1.w, v2)};
        }
    }

    template <Numeric T1, Numeric T2, int n, typename... Extra>
    forceinline constexpr auto min(const T1 v1, const vec<T2, n> & v2, Extra &&... extras)
    {
        return min(v2, v1, std::forward<Extra>(extras)...);
    }

    template <Numeric T, int n>
    forceinline constexpr T max(const vec<T, n> & v)
    {
        if constexpr (n == 2) return max(v.x, v.y);
        if constexpr (n == 3) return max(v.x, v.y, v.z);
        if constexpr (n == 4) return max(v.x, v.y, v.z, v.w);
    }

    template <Numeric T1, Numeric T2, int n, typename... Extra>
    forceinline constexpr auto max(const vec<T1, n> & v1, const vec<T2, n> & v2, Extra &&... extras)
    {
        if constexpr (sizeof...(Extra))
        {
            return max(max(v1, v2), std::forward<Extra>(extras)...);
        }
        else
        {
            if constexpr (n == 2) return vec<Common<T1, T2>, n>{max(v1.x, v2.x), max(v1.y, v2.y)};
            if constexpr (n == 3) return vec<Common<T1, T2>, n>{max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z)};
            if constexpr (n == 4) return vec<Common<T1, T2>, n>{max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z), max(v1.w, v2.w)};
        }
    }

    template <Numeric T1, Numeric T2, int n, typename... Extra>
    forceinline constexpr auto max(const vec<T1, n> & v1, const T2 v2, Extra &&... extras)
    {
        if constexpr (sizeof...(Extra))
        {
            return max(max(v1, v2), std::forward<Extra>(extras)...);
        }
        else
        {
            if constexpr (n == 2) return vec<Common<T1, T2>, n>{max(v1.x, v2), max(v1.y, v2)};
            if constexpr (n == 3) return vec<Common<T1, T2>, n>{max(v1.x, v2), max(v1.y, v2), max(v1.z, v2)};
            if constexpr (n == 4) return vec<Common<T1, T2>, n>{max(v1.x, v2), max(v1.y, v2), max(v1.z, v2), max(v1.w, v2)};
        }
    }

    template <Numeric T1, Numeric T2, int n, typename... Extra>
    forceinline constexpr auto max(const T1 v1, const vec<T2, n> & v2, Extra &&... extras)
    {
        return max(v2, v1, std::forward<Extra>(extras)...);
    }

    template <Numeric T1, SubOf<T1> T2, int n, typename... Extra>
    forceinline vec<T1, n> & minify(vec<T1, n> & v1, const vec<T2, n> & v2, Extra &&... extras)
    {
        if constexpr (sizeof...(Extra))
        {
            return minify(minify(v1, v2), std::forward<Extra>(extras)...);
        }
        else
        {
            if constexpr (n >= 1) minify(v1.x, v2.x);
            if constexpr (n >= 2) minify(v1.y, v2.y);
            if constexpr (n >= 3) minify(v1.z, v2.z);
            if constexpr (n >= 4) minify(v1.w, v2.w);
            return v1;
        }
    }

    template <Numeric T1, SubOf<T1> T2, int n, typename... Extra>
    forceinline vec<T1, n> & minify(vec<T1, n> & v1, const T2 v2, Extra &&... extras)
    {
        if constexpr (sizeof...(Extra))
        {
            return minify(minify(v1, v2), std::forward<Extra>(extras)...);
        }
        else
        {
            if constexpr (n >= 1) minify(v1.x, v2);
            if constexpr (n >= 2) minify(v1.y, v2);
            if constexpr (n >= 3) minify(v1.z, v2);
            if constexpr (n >= 4) minify(v1.w, v2);
            return v1;
        }
    }

    template <Numeric T1, SubOf<T1> T2, int n, typename... Extra>
    forceinline vec<T1, n> & maxify(vec<T1, n> & v1, const vec<T2, n> & v2, Extra &&... extras)
    {
        if constexpr (sizeof...(Extra))
        {
            return maxify(maxify(v1, v2), std::forward<Extra>(extras)...);
        }
        else
        {
            if constexpr (n >= 1) maxify(v1.x, v2.x);
            if constexpr (n >= 2) maxify(v1.y, v2.y);
            if constexpr (n >= 3) maxify(v1.z, v2.z);
            if constexpr (n >= 4) maxify(v1.w, v2.w);
            return v1;
        }
    }

    template <Numeric T1, SubOf<T1> T2, int n, typename... Extra>
    forceinline vec<T1, n> & maxify(vec<T1, n> & v1, const T2 v2, Extra &&... extras)
    {
        if constexpr (sizeof...(Extra))
        {
            return maxify(maxify(v1, v2), std::forward<Extra>(extras)...);
        }
        else
        {
            if constexpr (n >= 1) maxify(v1.x, v2);
            if constexpr (n >= 2) maxify(v1.y, v2);
            if constexpr (n >= 3) maxify(v1.z, v2);
            if constexpr (n >= 4) maxify(v1.w, v2);
            return v1;
        }
    }

    template <Numeric T>
    forceinline constexpr T median(const vec3<T> v)
    {
        return median(v.x, v.y, v.z);
    }

    template <Numeric T, int n>
    forceinline constexpr vec<T, n> clamp(const vec<T, n> & v, const T min, const T max)
    {
        if constexpr (n == 2) return {clamp(v.x, min, max), clamp(v.y, min, max)};
        if constexpr (n == 3) return {clamp(v.x, min, max), clamp(v.y, min, max), clamp(v.z, min, max)};
        if constexpr (n == 4) return {clamp(v.x, min, max), clamp(v.y, min, max), clamp(v.z, min, max), clamp(v.w, min, max)};
    }

    template <Numeric T, int n>
    forceinline constexpr vec<T, n> clamp(const vec<T, n> & v, const vec<T, n> & min, const vec<T, n> & max)
    {
        if constexpr (n == 2) return {clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y)};
        if constexpr (n == 3) return {clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y), clamp(v.z, min.z, max.z)};
        if constexpr (n == 4) return {clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y), clamp(v.z, min.z, max.z), clamp(v.w, min.w, max.w)};
    }

    template <Numeric T, int n>
    forceinline vec<T, n> & clampify(vec<T, n> & v, const T min, const T max)
    {
        clampify(v.x, min, max);
        if constexpr (n == 2) clampify(v.y, min, max);
        if constexpr (n == 3) clampify(v.z, min, max);
        if constexpr (n == 4) clampify(v.w, min, max);
        return v;
    }

    template <Numeric T, int n>
    forceinline vec<T, n> & clampify(vec<T, n> & v, const vec<T, n> & min, const vec<T, n> & max)
    {
        clampify(v.x, min.x, max.x);
        if constexpr (n == 2) clampify(v.y, min.y, max.y);
        if constexpr (n == 3) clampify(v.z, min.z, max.z);
        if constexpr (n == 4) clampify(v.w, min.w, max.w);
        return v;
    }
}
