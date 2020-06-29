#pragma once

#include "core-ext.hpp"

namespace qc::core {

    template <NumericOrBoolean T, int n> struct vec;

    inline namespace types {

        using qc::core::vec;

        template <typename T> using vec2 = vec<T, 2>;
        template <typename T> using vec3 = vec<T, 3>;
        template <typename T> using vec4 = vec<T, 4>;

        template <int n> using  fvec = vec< f32, n>;
        template <int n> using  dvec = vec< f64, n>;
        template <int n> using  cvec = vec< s08, n>;
        template <int n> using ucvec = vec< u08, n>;
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
        using  cvec2 = vec< s08, 2>;
        using  cvec3 = vec< s08, 3>;
        using  cvec4 = vec< s08, 4>;
        using ucvec2 = vec< u08, 2>;
        using ucvec3 = vec< u08, 3>;
        using ucvec4 = vec< u08, 4>;
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

        template <typename T> concept Vector = std::is_same_v<T, vec<typename T::Type, T::n>>;

        template <typename T> concept NumericVector = Vector<T> && Numeric<typename T::Type>;
        template <typename T> concept FloatingVector = Vector<T> && Floating<typename T::Type>;
        template <typename T> concept IntegralVector = Vector<T> && Integral<typename T::Type>;
        template <typename T> concept SignedIntegralVector = Vector<T> && SignedIntegral<typename T::Type>;
        template <typename T> concept UnsignedIntegralVector = Vector<T> && UnsignedIntegral<typename T::Type>;
        template <typename T> concept BooleanVector = Vector<T> && std::is_same_v<typename T::Type, bool>;

        template <typename T> concept Vector2 = Vector<T> && T::n == 2;
        template <typename T> concept Vector3 = Vector<T> && T::n == 3;
        template <typename T> concept Vector4 = Vector<T> && T::n == 4;
    }

    template <NumericOrBoolean T> struct vec<T, 2> {

        using Type = T;
        static constexpr int n{2};

        T x{};
        T y{};

        constexpr vec() noexcept = default;
        template <NumericOrBoolean U> constexpr explicit vec(U v) noexcept;
        template <NumericOrBoolean U> constexpr explicit vec(vec2<U> v) noexcept;
        template <NumericOrBoolean U> constexpr explicit vec(vec3<U> v) noexcept;
        template <NumericOrBoolean U> constexpr explicit vec(vec4<U> v) noexcept;
        constexpr vec(T v1, T v2) noexcept;

        constexpr vec(const vec & v) noexcept = default;
        constexpr vec(vec && v) noexcept = default;

        vec & operator=(const vec & v) noexcept = default;
        vec & operator=(vec && v) noexcept = default;

        ~vec() noexcept = default;

        constexpr operator bool() const noexcept;

        template <int i> T & at() noexcept;
        template <int i> constexpr T at() const noexcept;

        T & operator[](int i);
        T operator[](int i) const;

    };

    template <NumericOrBoolean T> struct vec<T, 3> {

        using Type = T;
        static constexpr int n{3};

        T x{};
        T y{};
        T z{};

        constexpr vec() noexcept = default;
        template <NumericOrBoolean U> constexpr explicit vec(U v) noexcept;
        template <NumericOrBoolean U> constexpr explicit vec(vec2<U> v) noexcept;
        template <NumericOrBoolean U> constexpr explicit vec(vec3<U> v) noexcept;
        template <NumericOrBoolean U> constexpr explicit vec(vec4<U> v) noexcept;
        constexpr vec(T v1, T v2, T v3) noexcept;
        Q_CONSTEX vec(vec2<T> v1, T v2) noexcept;
        Q_CX_ABLE vec(T v1, vec2<T> v2) noexcept;

        constexpr vec(const vec & v) noexcept = default;
        constexpr vec(vec && v) noexcept = default;

        vec & operator=(const vec & v) noexcept = default;
        vec & operator=(vec && v) noexcept = default;

        ~vec() noexcept = default;

        constexpr operator bool() const noexcept;

        template <int i> T & at() noexcept;
        template <int i> constexpr T at() const noexcept;

        T & operator[](int i);
        T operator[](int i) const;

        vec2<T> & xy() noexcept;
        Q_CX_ABLE vec2<T> xy() const noexcept;

        vec2<T> & yz() noexcept;
        Q_CX_ABLE vec2<T> yz() const noexcept;

    };

    template <NumericOrBoolean T> struct vec<T, 4> {

        using Type = T;
        static constexpr int n{4};

        T x{};
        T y{};
        T z{};
        T w{};

        constexpr vec() noexcept = default;
        template <NumericOrBoolean U> constexpr explicit vec(U v) noexcept;
        template <NumericOrBoolean U> constexpr explicit vec(vec2<U> v) noexcept;
        template <NumericOrBoolean U> constexpr explicit vec(vec3<U> v) noexcept;
        template <NumericOrBoolean U> constexpr explicit vec(vec4<U> v) noexcept;
        constexpr vec(T v1, T v2, T v3, T v4) noexcept;
        Q_CONSTEX vec(vec2<T> v1, T v2, T v3) noexcept;
        Q_CX_ABLE vec(T v1, vec2<T> v2, T v3) noexcept;
        Q_CX_ABLE vec(T v1, T v2, vec2<T> v3) noexcept;
        Q_CONSTEX vec(vec2<T> v1, vec2<T> v2) noexcept;
        Q_CONSTEX vec(vec3<T> v1, T v2) noexcept;
        Q_CX_ABLE vec(T v1, vec3<T> v2) noexcept;

        constexpr vec(const vec & v) noexcept = default;
        constexpr vec(vec && v) noexcept = default;

        vec & operator=(const vec & v) noexcept = default;
        vec & operator=(vec && v) noexcept = default;

        ~vec() noexcept = default;

        constexpr operator bool() const noexcept;

        template <int i> T & at() noexcept;
        template <int i> constexpr T at() const noexcept;

        T & operator[](int i);
        T operator[](int i) const;

        vec2<T> & xy() noexcept;
        Q_CX_ABLE vec2<T> xy() const noexcept;

        vec2<T> & yz() noexcept;
        Q_CX_ABLE vec2<T> yz() const noexcept;

        vec2<T> & zw() noexcept;
        Q_CX_ABLE vec2<T> zw() const noexcept;

        vec3<T> & xyz() noexcept;
        Q_CX_ABLE vec3<T> xyz() const noexcept;

        vec3<T> & yzw() noexcept;
        Q_CX_ABLE vec3<T> yzw() const noexcept;

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
    template <typename T> constexpr vec2<T> px<T, 2> = vec2<T>(T( 1), T( 0));
    template <typename T> constexpr vec2<T> nx<T, 2> = vec2<T>(T(-1), T( 0));
    template <typename T> constexpr vec3<T> px<T, 3> = vec3<T>(T( 1), T( 0), T( 0));
    template <typename T> constexpr vec3<T> nx<T, 3> = vec3<T>(T(-1), T( 0), T( 0));
    template <typename T> constexpr vec4<T> px<T, 4> = vec4<T>(T( 1), T( 0), T( 0), T( 0));
    template <typename T> constexpr vec4<T> nx<T, 4> = vec4<T>(T(-1), T( 0), T( 0), T( 0));
    template <typename T> constexpr vec2<T> py<T, 2> = vec2<T>(T( 0), T( 1));
    template <typename T> constexpr vec2<T> ny<T, 2> = vec2<T>(T( 0), T(-1));
    template <typename T> constexpr vec3<T> py<T, 3> = vec3<T>(T( 0), T( 1), T( 0));
    template <typename T> constexpr vec3<T> ny<T, 3> = vec3<T>(T( 0), T(-1), T( 0));
    template <typename T> constexpr vec4<T> py<T, 4> = vec4<T>(T( 0), T( 1), T( 0), T( 0));
    template <typename T> constexpr vec4<T> ny<T, 4> = vec4<T>(T( 0), T(-1), T( 0), T( 0));
    template <typename T> constexpr vec3<T> pz<T, 3> = vec3<T>(T( 0), T( 0), T( 1));
    template <typename T> constexpr vec3<T> nz<T, 3> = vec3<T>(T( 0), T( 0), T(-1));
    template <typename T> constexpr vec4<T> pz<T, 4> = vec4<T>(T( 0), T( 0), T( 1), T( 0));
    template <typename T> constexpr vec4<T> nz<T, 4> = vec4<T>(T( 0), T( 0), T(-1), T( 0));
    template <typename T> constexpr vec4<T> pw<T, 4> = vec4<T>(T( 0), T( 0), T( 0), T( 1));
    template <typename T> constexpr vec4<T> nw<T, 4> = vec4<T>(T( 0), T( 0), T( 0), T(-1));
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

    template <Floating T, int n> constexpr vec<T, n> infvec = vec<T, n>(infinity<T>);
    template <Floating T, int n> constexpr vec<T, n> nanvec = vec<T, n>(     nan<T>);

    template <Numeric T, int n> vec<T, n> & operator++(vec<T, n> & v);
    template <Numeric T, int n> vec<T, n>   operator++(vec<T, n> & v, int);

    template <Numeric T, int n> vec<T, n> & operator--(vec<T, n> & v);
    template <Numeric T, int n> vec<T, n>   operator--(vec<T, n> & v, int);

    template <Numeric T, int n> vec<T, n> & operator+=(vec<T, n> & v1, const vec<T, n> & v2);
    template <Numeric T, int n> vec<T, n> & operator+=(vec<T, n> & v1, T v2);

    template <Numeric T, int n> vec<T, n> & operator-=(vec<T, n> & v1, const vec<T, n> & v2);
    template <Numeric T, int n> vec<T, n> & operator-=(vec<T, n> & v1, T v2);

    template <Numeric T, int n> vec<T, n> & operator*=(vec<T, n> & v1, const vec<T, n> & v2);
    template <Numeric T, int n> vec<T, n> & operator*=(vec<T, n> & v1, T v2);

    template <Numeric T, int n> vec<T, n> & operator/=(vec<T, n> & v1, const vec<T, n> & v2);
    template <Numeric T, int n> vec<T, n> & operator/=(vec<T, n> & v1, T v2);

    template <Numeric T, int n> vec<T, n> & operator%=(vec<T, n> & v1, const vec<T, n> & v2);
    template <Numeric T, int n> vec<T, n> & operator%=(vec<T, n> & v1, T v2);

    template <Numeric T, int n> Q_CX_ABLE vec<T, n> operator+(const vec<T, n> & v);

    template <Numeric T, int n> Q_CX_ABLE vec<T, n> operator-(const vec<T, n> & v);

    template <Numeric T, int n> Q_CX_ABLE  vec<T, n> operator+(const vec<T, n> & v1, const vec<T, n> & v2);
    template <Numeric T, int n> Q_CX_ABLE  vec<T, n> operator+(const vec<T, n> & v1, T v2);
    template <Numeric T, int n> Q_CX_ABLE  vec<T, n> operator+(T v1, const vec<T, n> & v2);

    template <Numeric T, int n> Q_CX_ABLE  vec<T, n> operator-(const vec<T, n> & v1, const vec<T, n> & v2);
    template <Numeric T, int n> Q_CX_ABLE  vec<T, n> operator-(const vec<T, n> & v1, T v2);
    template <Numeric T, int n> Q_CX_ABLE  vec<T, n> operator-(T v1, const vec<T, n> & v2);

    template <Numeric T, int n> Q_CX_ABLE  vec<T, n> operator*(const vec<T, n> & v1, const vec<T, n> & v2);
    template <Numeric T, int n> Q_CX_ABLE  vec<T, n> operator*(const vec<T, n> & v1, T v2);
    template <Numeric T, int n> Q_CX_ABLE  vec<T, n> operator*(T v1, const vec<T, n> & v2);

    template <Numeric T, int n> Q_CX_ABLE  vec<T, n> operator/(const vec<T, n> & v1, const vec<T, n> & v2);
    template <Numeric T, int n> Q_CX_ABLE  vec<T, n> operator/(const vec<T, n> & v1, T v2);
    template <Numeric T, int n> Q_CX_ABLE  vec<T, n> operator/(T v1, const vec<T, n> & v2);

    template <Numeric T, int n> Q_CX_ABLE vec<T, n> operator%(const vec<T, n> & v1, const vec<T, n> & v2);
    template <Numeric T, int n> Q_CX_ABLE vec<T, n> operator%(const vec<T, n> & v1, T v2);
    template <Numeric T, int n> Q_CX_ABLE vec<T, n> operator%(T v1, const vec<T, n> & v2);

    template <typename T, int n> Q_CX_ABLE      bool operator==(const vec<T, n> & v1, const vec<T, n> & v2);
    template <typename T, int n> Q_CX_ABLE bvec<n> operator==(const vec<T, n> & v1, T v2);
    template <typename T, int n> Q_CX_ABLE bvec<n> operator==(T v1, const vec<T, n> & v2);

    template <typename T, int n> Q_CX_ABLE      bool operator!=(const vec<T, n> & v1, const vec<T, n> & v2);
    template <typename T, int n> Q_CX_ABLE bvec<n> operator!=(const vec<T, n> & v1, T v2);
    template <typename T, int n> Q_CX_ABLE bvec<n> operator!=(T v1, const vec<T, n> & v2);

    template <Numeric T, int n> Q_CX_ABLE bvec<n> operator<(const vec<T, n> & v1, const vec<T, n> & v2);
    template <Numeric T, int n> Q_CX_ABLE bvec<n> operator<(const vec<T, n> & v1, T v2);
    template <Numeric T, int n> Q_CX_ABLE bvec<n> operator<(T v1, const vec<T, n> & v2);

    template <Numeric T, int n> Q_CX_ABLE bvec<n> operator>(const vec<T, n> & v1, const vec<T, n> & v2);
    template <Numeric T, int n> Q_CX_ABLE bvec<n> operator>(const vec<T, n> & v1, T v2);
    template <Numeric T, int n> Q_CX_ABLE bvec<n> operator>(T v1, const vec<T, n> & v2);

    template <Numeric T, int n> Q_CX_ABLE bvec<n> operator<=(const vec<T, n> & v1, const vec<T, n> & v2);
    template <Numeric T, int n> Q_CX_ABLE bvec<n> operator<=(const vec<T, n> & v1, T v2);
    template <Numeric T, int n> Q_CX_ABLE bvec<n> operator<=(T v1, const vec<T, n> & v2);

    template <Numeric T, int n> Q_CX_ABLE bvec<n> operator>=(const vec<T, n> & v1, const vec<T, n> & v2);
    template <Numeric T, int n> Q_CX_ABLE bvec<n> operator>=(const vec<T, n> & v1, T v2);
    template <Numeric T, int n> Q_CX_ABLE bvec<n> operator>=(T v1, const vec<T, n> & v2);

    template <int n> Q_CX_ABLE bvec<n> operator&&(bvec<n> v1, bvec<n> v2);

    template <int n> Q_CX_ABLE bvec<n> operator||(bvec<n> v1, bvec<n> v2);

    template <int n> Q_CX_ABLE bvec<n> operator!(bvec<n> v1);

} // namespace qc::core

// INLINE IMPLEMENTATION ///////////////////////////////////////////////////////////////////////////////////////////////

namespace qc::core {

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    inline constexpr vec<T, 2>::vec(const U v) noexcept :
        x(T(v)), y(x)
    {}

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    inline constexpr vec<T, 2>::vec(const vec2<U> v) noexcept :
        x(T(v.x)), y(T(v.y))
    {}

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    inline constexpr vec<T, 2>::vec(const vec3<U> v) noexcept :
        x(T(v.x)), y(T(v.y))
    {}

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    inline constexpr vec<T, 2>::vec(const vec4<U> v) noexcept :
        x(T(v.x)), y(T(v.y))
    {}

    template <NumericOrBoolean T>
    inline constexpr vec<T, 2>::vec(const T v1, const T v2) noexcept :
        x(v1), y(v2)
    {}

    template <NumericOrBoolean T>
    inline constexpr vec<T, 2>::operator bool() const noexcept {
        return x || y;
    }

    template <NumericOrBoolean T>
    template <int i>
    inline T & vec<T, 2>::at() noexcept {
        static_assert(i >= 0 && i <= 1, "Index out of bounds");
        if constexpr (i == 0) return x;
        if constexpr (i == 1) return y;
    }

    template <NumericOrBoolean T>
    template <int i>
    inline constexpr T vec<T, 2>::at() const noexcept {
        static_assert(i >= 0 && i <= 1, "Index out of bounds");
        if constexpr (i == 0) return x;
        if constexpr (i == 1) return y;
    }

    template <NumericOrBoolean T>
    inline T & vec<T, 2>::operator[](const int i) {
        return *(&x + i);
    }

    template <NumericOrBoolean T>
    inline T vec<T, 2>::operator[](const int i) const {
        return *(&x + i);
    }

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    inline constexpr vec<T, 3>::vec(const U v) noexcept :
        x(T(v)), y(x), z(x)
    {}

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    inline constexpr vec<T, 3>::vec(const vec2<U> v) noexcept :
        x(T(v.x)), y(T(v.y)), z()
    {}

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    inline constexpr vec<T, 3>::vec(const vec3<U> v) noexcept :
        x(T(v.x)), y(T(v.y)), z(T(v.z))
    {}

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    inline constexpr vec<T, 3>::vec(const vec4<U> v) noexcept :
        x(T(v.x)), y(T(v.y)), z(T(v.z))
    {}

    template <NumericOrBoolean T>
    inline constexpr vec<T, 3>::vec(const T v1, const T v2, const T v3) noexcept :
        x(v1), y(v2), z(v3)
    {}

    template <NumericOrBoolean T>
    inline Q_CONSTEX vec<T, 3>::vec(const vec2<T> v1, const T v2) noexcept :
        x(v1.x), y(v1.y), z(v2)
    {}

    template <NumericOrBoolean T>
    inline Q_CX_ABLE vec<T, 3>::vec(const T v1, const vec2<T> v2) noexcept :
        x(v1), y(v2.x), z(v2.y)
    {}

    template <NumericOrBoolean T>
    inline constexpr vec<T, 3>::operator bool() const noexcept {
        return x || y || z;
    }

    template <NumericOrBoolean T>
    template <int i>
    inline T & vec<T, 3>::at() noexcept {
        static_assert(i >= 0 && i <= 2, "Index out of bounds");
        if constexpr (i == 0) return x;
        if constexpr (i == 1) return y;
        if constexpr (i == 2) return z;
    }

    template <NumericOrBoolean T>
    template <int i>
    inline constexpr T vec<T, 3>::at() const noexcept {
        static_assert(i >= 0 && i <= 2, "Index out of bounds");
        if constexpr (i == 0) return x;
        if constexpr (i == 1) return y;
        if constexpr (i == 2) return z;
    }

    template <NumericOrBoolean T>
    inline T & vec<T, 3>::operator[](const int i) {
        return *(&x + i);
    }

    template <NumericOrBoolean T>
    inline T vec<T, 3>::operator[](const int i) const {
        return *(&x + i);
    }

    template <NumericOrBoolean T>
    inline vec2<T> & vec<T, 3>::xy() noexcept {
        return reinterpret_cast<vec2<T> &>(x);
    }

    template <NumericOrBoolean T>
    inline Q_CX_ABLE vec2<T> vec<T, 3>::xy() const noexcept {
        return reinterpret_cast<const vec2<T> &>(x);
    }

    template <NumericOrBoolean T>
    inline vec2<T> & vec<T, 3>::yz() noexcept {
        return reinterpret_cast<vec2<T> &>(y);
    }

    template <NumericOrBoolean T>
    inline Q_CX_ABLE vec2<T> vec<T, 3>::yz() const noexcept {
        return reinterpret_cast<const vec2<T> &>(y);
    }

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    inline constexpr vec<T, 4>::vec(const U v) noexcept :
        x(T(v)), y(x), z(x), w(x)
    {}

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    inline constexpr vec<T, 4>::vec(const vec2<U> v) noexcept :
        x(T(v.x)), y(T(v.y)), z(), w()
    {}

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    inline constexpr vec<T, 4>::vec(const vec3<U> v) noexcept :
        x(T(v.x)), y(T(v.y)), z(T(v.z)), w()
    {}

    template <NumericOrBoolean T>
    template <NumericOrBoolean U>
    inline constexpr vec<T, 4>::vec(const vec4<U> v) noexcept :
        x(T(v.x)), y(T(v.y)), z(T(v.z)), w(T(v.w))
    {}

    template <NumericOrBoolean T>
    inline constexpr vec<T, 4>::vec(const T v1, const T v2, const T v3, const T v4) noexcept :
        x(v1), y(v2), z(v3), w(v4)
    {}

    template <NumericOrBoolean T>
    inline Q_CONSTEX vec<T, 4>::vec(const vec2<T> v1, const T v2, const T v3) noexcept :
        x(v1.x), y(v1.y), z(v2), w(v3)
    {}

    template <NumericOrBoolean T>
    inline Q_CX_ABLE vec<T, 4>::vec(const T v1, const vec2<T> v2, const T v3) noexcept :
        x(v1), y(v2.x), z(v2.y), w(v3)
    {}

    template <NumericOrBoolean T>
    inline Q_CX_ABLE vec<T, 4>::vec(const T v1, const T v2, const vec2<T> v3) noexcept :
        x(v1), y(v2), z(v3.x), w(v3.y)
    {}

    template <NumericOrBoolean T>
    inline Q_CONSTEX vec<T, 4>::vec(const vec2<T> v1, const vec2<T> v2) noexcept :
        x(v1.x), y(v1.y), z(v2.x), w(v2.y)
    {}

    template <NumericOrBoolean T>
    inline Q_CONSTEX vec<T, 4>::vec(const vec3<T> v1, const T v2) noexcept :
        x(v1.x), y(v1.y), z(v1.z), w(v2)
    {}

    template <NumericOrBoolean T>
    inline Q_CX_ABLE vec<T, 4>::vec(const T v1, const vec3<T> v2) noexcept :
        x(v1), y(v2.x), z(v2.y), w(v2.z)
    {}

    template <NumericOrBoolean T>
    inline constexpr vec<T, 4>::operator bool() const noexcept {
        return x || y || z || w;
    }

    template <NumericOrBoolean T>
    template <int i>
    inline T & vec<T, 4>::at() noexcept {
        static_assert(i >= 0 && i <= 3, "Index out of bounds");
        if constexpr (i == 0) return x;
        if constexpr (i == 1) return y;
        if constexpr (i == 2) return z;
        if constexpr (i == 3) return w;
    }

    template <NumericOrBoolean T>
    template <int i>
    inline constexpr T vec<T, 4>::at() const noexcept {
        static_assert(i >= 0 && i <= 3, "Index out of bounds");
        if constexpr (i == 0) return x;
        if constexpr (i == 1) return y;
        if constexpr (i == 2) return z;
        if constexpr (i == 3) return w;
    }

    template <NumericOrBoolean T>
    inline T & vec<T, 4>::operator[](const int i) {
        return *(&x + i);
    }

    template <NumericOrBoolean T>
    inline T vec<T, 4>::operator[](const int i) const {
        return *(&x + i);
    }

    template <NumericOrBoolean T>
    inline vec2<T> & vec<T, 4>::xy() noexcept {
        return reinterpret_cast<vec2<T> &>(x);
    }

    template <NumericOrBoolean T>
    inline Q_CX_ABLE vec2<T> vec<T, 4>::xy() const noexcept {
        return reinterpret_cast<const vec2<T> &>(x);
    }

    template <NumericOrBoolean T>
    inline vec2<T> & vec<T, 4>::yz() noexcept {
        return reinterpret_cast<vec2<T> &>(y);
    }

    template <NumericOrBoolean T>
    inline Q_CX_ABLE vec2<T> vec<T, 4>::yz() const noexcept {
        return reinterpret_cast<const vec2<T> &>(y);
    }

    template <NumericOrBoolean T>
    inline vec2<T> & vec<T, 4>::zw() noexcept {
        return reinterpret_cast<vec2<T> &>(z);
    }

    template <NumericOrBoolean T>
    inline Q_CX_ABLE vec2<T> vec<T, 4>::zw() const noexcept {
        return reinterpret_cast<const vec2<T> &>(z);
    }

    template <NumericOrBoolean T>
    inline vec3<T> & vec<T, 4>::xyz() noexcept {
        return reinterpret_cast<vec3<T> &>(x);
    }

    template <NumericOrBoolean T>
    inline Q_CX_ABLE vec3<T> vec<T, 4>::xyz() const noexcept {
        return reinterpret_cast<const vec3<T> &>(x);
    }

    template <NumericOrBoolean T>
    inline vec3<T> & vec<T, 4>::yzw() noexcept {
        return reinterpret_cast<vec3<T> &>(y);
    }

    template <NumericOrBoolean T>
    inline Q_CX_ABLE vec3<T> vec<T, 4>::yzw() const noexcept {
        return reinterpret_cast<const vec3<T> &>(y);
    }

    template <Numeric T, int n>
    inline vec<T, n> & operator++(vec<T, n> & v) {
        if constexpr (n >= 1) ++v.x;
        if constexpr (n >= 2) ++v.y;
        if constexpr (n >= 3) ++v.z;
        if constexpr (n >= 4) ++v.w;
        return v;
    }

    template <Numeric T, int n>
    inline vec<T, n> operator++(vec<T, n> & v, int) {
        vec<T, n> temp(v);
        ++v;
        return temp;
    }

    template <Numeric T, int n>
    inline vec<T, n> & operator--(vec<T, n> & v) {
        if constexpr (n >= 1) --v.x;
        if constexpr (n >= 2) --v.y;
        if constexpr (n >= 3) --v.z;
        if constexpr (n >= 4) --v.w;
        return v;
    }

    template <Numeric T, int n>
    inline vec<T, n> operator--(vec<T, n> & v, int) {
        vec<T, n> temp(v);
        --v;
        return temp;
    }

    template <Numeric T, int n>
    inline vec<T, n> & operator+=(vec<T, n> & v1, const vec<T, n> & v2) {
        if constexpr (n >= 1) v1.x += v2.x;
        if constexpr (n >= 2) v1.y += v2.y;
        if constexpr (n >= 3) v1.z += v2.z;
        if constexpr (n >= 4) v1.w += v2.w;
        return v1;
    }

    template <Numeric T, int n>
    inline vec<T, n> & operator+=(vec<T, n> & v1, const T v2) {
        if constexpr (n >= 1) v1.x += v2;
        if constexpr (n >= 2) v1.y += v2;
        if constexpr (n >= 3) v1.z += v2;
        if constexpr (n >= 4) v1.w += v2;
        return v1;
    }

    template <Numeric T, int n>
    inline vec<T, n> & operator-=(vec<T, n> & v1, const vec<T, n> & v2) {
        if constexpr (n >= 1) v1.x -= v2.x;
        if constexpr (n >= 2) v1.y -= v2.y;
        if constexpr (n >= 3) v1.z -= v2.z;
        if constexpr (n >= 4) v1.w -= v2.w;
        return v1;
    }

    template <Numeric T, int n>
    inline vec<T, n> & operator-=(vec<T, n> & v1, const T v2) {
        if constexpr (n >= 1) v1.x -= v2;
        if constexpr (n >= 2) v1.y -= v2;
        if constexpr (n >= 3) v1.z -= v2;
        if constexpr (n >= 4) v1.w -= v2;
        return v1;
    }

    template <Numeric T, int n>
    inline vec<T, n> & operator*=(vec<T, n> & v1, const vec<T, n> & v2) {
        if constexpr (n >= 1) v1.x *= v2.x;
        if constexpr (n >= 2) v1.y *= v2.y;
        if constexpr (n >= 3) v1.z *= v2.z;
        if constexpr (n >= 4) v1.w *= v2.w;
        return v1;
    }

    template <Numeric T, int n>
    inline vec<T, n> & operator*=(vec<T, n> & v1, const T v2) {
        if constexpr (n >= 1) v1.x *= v2;
        if constexpr (n >= 2) v1.y *= v2;
        if constexpr (n >= 3) v1.z *= v2;
        if constexpr (n >= 4) v1.w *= v2;
        return v1;
    }

    template <Numeric T, int n>
    inline vec<T, n> & operator/=(vec<T, n> & v1, const vec<T, n> & v2) {
        if constexpr (n >= 1) v1.x /= v2.x;
        if constexpr (n >= 2) v1.y /= v2.y;
        if constexpr (n >= 3) v1.z /= v2.z;
        if constexpr (n >= 4) v1.w /= v2.w;
        return v1;
    }

    template <Numeric T, int n>
    inline vec<T, n> & operator/=(vec<T, n> & v1, const T v2) {
        if constexpr (n > 1 && std::is_floating_point_v<T>) return v1 *= T(1.0) / v2;
        if constexpr (n >= 1) v1.x /= v2;
        if constexpr (n >= 2) v1.y /= v2;
        if constexpr (n >= 3) v1.z /= v2;
        if constexpr (n >= 4) v1.w /= v2;
        return v1;
    }

    template <Numeric T, int n>
    inline vec<T, n> & operator%=(vec<T, n> & v1, const vec<T, n> & v2) {
        if constexpr (n >= 1) v1.x = mod(v1.x, v2.x);
        if constexpr (n >= 2) v1.y = mod(v1.y, v2.y);
        if constexpr (n >= 3) v1.z = mod(v1.z, v2.z);
        if constexpr (n >= 4) v1.w = mod(v1.w, v2.w);
        return v1;
    }

    template <Numeric T, int n>
    inline vec<T, n> & operator%=(vec<T, n> & v1, const T v2) {
        if constexpr (n >= 1) v1.x = mod(v1.x, v2);
        if constexpr (n >= 2) v1.y = mod(v1.y, v2);
        if constexpr (n >= 3) v1.z = mod(v1.z, v2);
        if constexpr (n >= 4) v1.w = mod(v1.w, v2);
        return v1;
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE vec<T, n> operator+(const vec<T, n> & v) {
        return v;
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE vec<T, n> operator-(const vec<T, n> & v) {
        if constexpr (std::is_unsigned_v<T>) return v;
        if constexpr (!std::is_unsigned_v<T>) {
            if constexpr (n == 2) return {-v.x, -v.y};
            if constexpr (n == 3) return {-v.x, -v.y, -v.z};
            if constexpr (n == 4) return {-v.x, -v.y, -v.z, -v.w};
        }
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE vec<T, n> operator+(const vec<T, n> & v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return {T(v1.x + v2.x), T(v1.y + v2.y)};
        if constexpr (n == 3) return {T(v1.x + v2.x), T(v1.y + v2.y), T(v1.z + v2.z)};
        if constexpr (n == 4) return {T(v1.x + v2.x), T(v1.y + v2.y), T(v1.z + v2.z), T(v1.w + v2.w)};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE vec<T, n> operator+(const vec<T, n> & v1, const T v2) {
        if constexpr (n == 2) return {T(v1.x + v2), T(v1.y + v2)};
        if constexpr (n == 3) return {T(v1.x + v2), T(v1.y + v2), T(v1.z + v2)};
        if constexpr (n == 4) return {T(v1.x + v2), T(v1.y + v2), T(v1.z + v2), T(v1.w + v2)};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE vec<T, n> operator+(const T v1, const vec<T, n> & v2) {
        return v2 + v1;
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE vec<T, n> operator-(const vec<T, n> & v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return {T(v1.x - v2.x), T(v1.y - v2.y)};
        if constexpr (n == 3) return {T(v1.x - v2.x), T(v1.y - v2.y), T(v1.z - v2.z)};
        if constexpr (n == 4) return {T(v1.x - v2.x), T(v1.y - v2.y), T(v1.z - v2.z), T(v1.w - v2.w)};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE vec<T, n> operator-(const vec<T, n> & v1, const T v2) {
        if constexpr (n == 2) return {T(v1.x - v2), T(v1.y - v2)};
        if constexpr (n == 3) return {T(v1.x - v2), T(v1.y - v2), T(v1.z - v2)};
        if constexpr (n == 4) return {T(v1.x - v2), T(v1.y - v2), T(v1.z - v2), T(v1.w - v2)};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE vec<T, n> operator-(const T v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return {T(v1 - v2.x), T(v1 - v2.y)};
        if constexpr (n == 3) return {T(v1 - v2.x), T(v1 - v2.y), T(v1 - v2.z)};
        if constexpr (n == 4) return {T(v1 - v2.x), T(v1 - v2.y), T(v1 - v2.z), T(v1 - v2.w)};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE vec<T, n> operator*(const vec<T, n> & v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return {T(v1.x * v2.x), T(v1.y * v2.y)};
        if constexpr (n == 3) return {T(v1.x * v2.x), T(v1.y * v2.y), T(v1.z * v2.z)};
        if constexpr (n == 4) return {T(v1.x * v2.x), T(v1.y * v2.y), T(v1.z * v2.z), T(v1.w * v2.w)};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE vec<T, n> operator*(const vec<T, n> & v1, const T v2) {
        if constexpr (n == 2) return {T(v1.x * v2), T(v1.y * v2)};
        if constexpr (n == 3) return {T(v1.x * v2), T(v1.y * v2), T(v1.z * v2)};
        if constexpr (n == 4) return {T(v1.x * v2), T(v1.y * v2), T(v1.z * v2), T(v1.w * v2)};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE vec<T, n> operator*(const T v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return {T(v1 * v2.x), T(v1 * v2.y)};
        if constexpr (n == 3) return {T(v1 * v2.x), T(v1 * v2.y), T(v1 * v2.z)};
        if constexpr (n == 4) return {T(v1 * v2.x), T(v1 * v2.y), T(v1 * v2.z), T(v1 * v2.w)};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE vec<T, n> operator/(const vec<T, n> & v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return {T(v1.x / v2.x), T(v1.y / v2.y)};
        if constexpr (n == 3) return {T(v1.x / v2.x), T(v1.y / v2.y), T(v1.z / v2.z)};
        if constexpr (n == 4) return {T(v1.x / v2.x), T(v1.y / v2.y), T(v1.z / v2.z), T(v1.w / v2.w)};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE vec<T, n> operator/(const vec<T, n> & v1, const T v2) {
        if constexpr (std::is_floating_point_v<T>) {
            return v1 * (T(1.0) / v2);
        }
        else {
            if constexpr (n == 2) return {T(v1.x / v2), T(v1.y / v2)};
            if constexpr (n == 3) return {T(v1.x / v2), T(v1.y / v2), T(v1.z / v2)};
            if constexpr (n == 4) return {T(v1.x / v2), T(v1.y / v2), T(v1.z / v2), T(v1.w / v2)};
        }
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE vec<T, n> operator/(const T v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return {T(v1 / v2.x), T(v1 / v2.y)};
        if constexpr (n == 3) return {T(v1 / v2.x), T(v1 / v2.y), T(v1 / v2.z)};
        if constexpr (n == 4) return {T(v1 / v2.x), T(v1 / v2.y), T(v1 / v2.z), T(v1 / v2.w)};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE vec<T, n> operator%(const vec<T, n> & v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return {mod(v1.x, v2.x), mod(v1.y, v2.y)};
        if constexpr (n == 3) return {mod(v1.x, v2.x), mod(v1.y, v2.y), mod(v1.z, v2.z)};
        if constexpr (n == 4) return {mod(v1.x, v2.x), mod(v1.y, v2.y), mod(v1.z, v2.z), mod(v1.w, v2.w)};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE vec<T, n> operator%(const vec<T, n> & v1, const T v2) {
        if constexpr (n == 2) return {mod(v1.x, v2), mod(v1.y, v2)};
        if constexpr (n == 3) return {mod(v1.x, v2), mod(v1.y, v2), mod(v1.z, v2)};
        if constexpr (n == 4) return {mod(v1.x, v2), mod(v1.y, v2), mod(v1.z, v2), mod(v1.w, v2)};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE vec<T, n> operator%(const T v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return {mod(v1, v2.x), mod(v1, v2.y)};
        if constexpr (n == 3) return {mod(v1, v2.x), mod(v1, v2.y), mod(v1, v2.z)};
        if constexpr (n == 4) return {mod(v1, v2.x), mod(v1, v2.y), mod(v1, v2.z), mod(v1, v2.w)};
    }

    template <typename T, int n>
    inline Q_CX_ABLE bool operator==(const vec<T, n> & v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return v1.x == v2.x && v1.y == v2.y;
        if constexpr (n == 3) return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
        if constexpr (n == 4) return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
    }

    template <typename T, int n>
    inline Q_CX_ABLE bvec<n> operator==(const vec<T, n> & v1, const T v2) {
        if constexpr (n == 2) return {v1.x == v2, v1.y == v2};
        if constexpr (n == 3) return {v1.x == v2, v1.y == v2, v1.z == v2};
        if constexpr (n == 4) return {v1.x == v2, v1.y == v2, v1.z == v2, v1.w == v2};
    }

    template <typename T, int n>
    inline Q_CX_ABLE bvec<n> operator==(const T v1, const vec<T, n> & v2) {
        return v2 == v1;
    }

    template <typename T, int n>
    inline Q_CX_ABLE bool operator!=(const vec<T, n> & v1, const vec<T, n> & v2) {
        return !(v1 == v2);
    }

    template <typename T, int n>
    inline Q_CX_ABLE bvec<n> operator!=(const vec<T, n> & v1, const T v2) {
        return !(v1 == v2);
    }

    template <typename T, int n>
    inline Q_CX_ABLE bvec<n> operator!=(const T v1, const vec<T, n> & v2) {
        return !(v1 == v2);
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE bvec<n> operator<(const vec<T, n> & v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return {v1.x < v2.x, v1.y < v2.y};
        if constexpr (n == 3) return {v1.x < v2.x, v1.y < v2.y, v1.z < v2.z};
        if constexpr (n == 4) return {v1.x < v2.x, v1.y < v2.y, v1.z < v2.z, v1.w < v2.w};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE bvec<n> operator<(const vec<T, n> & v1, const T v2) {
        if constexpr (n == 2) return {v1.x < v2, v1.y < v2};
        if constexpr (n == 3) return {v1.x < v2, v1.y < v2, v1.z < v2};
        if constexpr (n == 4) return {v1.x < v2, v1.y < v2, v1.z < v2, v1.w < v2};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE bvec<n> operator<(const T v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return {v1 < v2.x, v1 < v2.y};
        if constexpr (n == 3) return {v1 < v2.x, v1 < v2.y, v1 < v2.z};
        if constexpr (n == 4) return {v1 < v2.x, v1 < v2.y, v1 < v2.z, v1 < v2.w};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE bvec<n> operator>(const vec<T, n> & v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return {v1.x > v2.x, v1.y > v2.y};
        if constexpr (n == 3) return {v1.x > v2.x, v1.y > v2.y, v1.z > v2.z};
        if constexpr (n == 4) return {v1.x > v2.x, v1.y > v2.y, v1.z > v2.z, v1.w > v2.w};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE bvec<n> operator>(const vec<T, n> & v1, const T v2) {
        if constexpr (n == 2) return {v1.x > v2, v1.y > v2};
        if constexpr (n == 3) return {v1.x > v2, v1.y > v2, v1.z > v2};
        if constexpr (n == 4) return {v1.x > v2, v1.y > v2, v1.z > v2, v1.w > v2};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE bvec<n> operator>(const T v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return {v1 > v2.x, v1 > v2.y};
        if constexpr (n == 3) return {v1 > v2.x, v1 > v2.y, v1 > v2.z};
        if constexpr (n == 4) return {v1 > v2.x, v1 > v2.y, v1 > v2.z, v1 > v2.w};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE bvec<n> operator<=(const vec<T, n> & v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return {v1.x <= v2.x, v1.y <= v2.y};
        if constexpr (n == 3) return {v1.x <= v2.x, v1.y <= v2.y, v1.z <= v2.z};
        if constexpr (n == 4) return {v1.x <= v2.x, v1.y <= v2.y, v1.z <= v2.z, v1.w <= v2.w};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE bvec<n> operator<=(const vec<T, n> & v1, const T v2) {
        if constexpr (n == 2) return {v1.x <= v2, v1.y <= v2};
        if constexpr (n == 3) return {v1.x <= v2, v1.y <= v2, v1.z <= v2};
        if constexpr (n == 4) return {v1.x <= v2, v1.y <= v2, v1.z <= v2, v1.w <= v2};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE bvec<n> operator<=(const T v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return {v1 <= v2.x, v1 <= v2.y};
        if constexpr (n == 3) return {v1 <= v2.x, v1 <= v2.y, v1 <= v2.z};
        if constexpr (n == 4) return {v1 <= v2.x, v1 <= v2.y, v1 <= v2.z, v1 <= v2.w};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE bvec<n> operator>=(const vec<T, n> & v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return {v1.x >= v2.x, v1.y >= v2.y};
        if constexpr (n == 3) return {v1.x >= v2.x, v1.y >= v2.y, v1.z >= v2.z};
        if constexpr (n == 4) return {v1.x >= v2.x, v1.y >= v2.y, v1.z >= v2.z, v1.w >= v2.w};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE bvec<n> operator>=(const vec<T, n> & v1, const T v2) {
        if constexpr (n == 2) return {v1.x >= v2, v1.y >= v2};
        if constexpr (n == 3) return {v1.x >= v2, v1.y >= v2, v1.z >= v2};
        if constexpr (n == 4) return {v1.x >= v2, v1.y >= v2, v1.z >= v2, v1.w >= v2};
    }

    template <Numeric T, int n>
    inline Q_CX_ABLE bvec<n> operator>=(const T v1, const vec<T, n> & v2) {
        if constexpr (n == 2) return {v1 >= v2.x, v1 >= v2.y};
        if constexpr (n == 3) return {v1 >= v2.x, v1 >= v2.y, v1 >= v2.z};
        if constexpr (n == 4) return {v1 >= v2.x, v1 >= v2.y, v1 >= v2.z, v1 >= v2.w};
    }

    template <int n>
    inline Q_CX_ABLE bvec<n> operator&&(const bvec<n> v1, const bvec<n> v2) {
        if constexpr (n == 2) return {v1.x && v2.x, v1.y && v2.y};
        if constexpr (n == 3) return {v1.x && v2.x, v1.y && v2.y, v1.z && v2.z};
        if constexpr (n == 4) return {v1.x && v2.x, v1.y && v2.y, v1.z && v2.z, v1.w && v2.w};
    }

    template <int n>
    inline Q_CX_ABLE bvec<n> operator||(const bvec<n> v1, const bvec<n> v2) {
        if constexpr (n == 2) return {v1.x || v2.x, v1.y || v2.y};
        if constexpr (n == 3) return {v1.x || v2.x, v1.y || v2.y, v1.z || v2.z};
        if constexpr (n == 4) return {v1.x || v2.x, v1.y || v2.y, v1.z || v2.z, v1.w || v2.w};
    }

    template <int n>
    inline Q_CX_ABLE bvec<n> operator!(const bvec<n> v) {
        if constexpr (n == 2) return {!v.x, !v.y};
        if constexpr (n == 3) return {!v.x, !v.y, !v.z};
        if constexpr (n == 4) return {!v.x, !v.y, !v.z, !v.w};
    }

} // namespace qc::core
