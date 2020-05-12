#pragma once

#include "core-func.hpp"

namespace qc {

    //==================================================================================================================
    // TYPES ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    //==================================================================================================================

    //==============================================================================
    // Vec Types
    //------------------------------------------------------------------------------

    template <NumberOrBoolean T, int t_n> struct vec;

    inline namespace types {

        template <typename T> using vec2 = vec<T, 2>;
        template <typename T> using vec3 = vec<T, 3>;
        template <typename T> using vec4 = vec<T, 4>;

        template <int t_n> using  fvec = vec< f32, t_n>;
        template <int t_n> using  dvec = vec< f64, t_n>;
        template <int t_n> using  cvec = vec< s08, t_n>;
        template <int t_n> using ucvec = vec< u08, t_n>;
        template <int t_n> using  svec = vec< s16, t_n>;
        template <int t_n> using usvec = vec< u16, t_n>;
        template <int t_n> using  ivec = vec< s32, t_n>;
        template <int t_n> using uivec = vec< u32, t_n>;
        template <int t_n> using  lvec = vec< s64, t_n>;
        template <int t_n> using ulvec = vec< u64, t_n>;
        template <int t_n> using  nvec = vec< nat, t_n>;
        template <int t_n> using unvec = vec<unat, t_n>;
        template <int t_n> using  bvec = vec<bool, t_n>;

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
        using  nvec2 = vec< nat, 2>;
        using  nvec3 = vec< nat, 3>;
        using  nvec4 = vec< nat, 4>;
        using unvec2 = vec<unat, 2>;
        using unvec3 = vec<unat, 3>;
        using unvec4 = vec<unat, 4>;
        using  bvec2 = vec<bool, 2>;
        using  bvec3 = vec<bool, 3>;
        using  bvec4 = vec<bool, 4>;

    }

    //==================================================================================================================
    // VEC2 ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //==================================================================================================================

    template <NumberOrBoolean T> struct vec<T, 2> {

        //--------------------------------------------------------------------------
        // Static Members

        using Type = T;

        static constexpr int n{2};

        //--------------------------------------------------------------------------
        // Instance Variables

        T x{};
        T y{};

        //--------------------------------------------------------------------------
        // Construction

        constexpr vec() noexcept = default;
        constexpr vec(const vec & v) noexcept = default;
        constexpr vec(vec && v) noexcept = default;

        constexpr explicit vec(T v) noexcept;
        template <Number U> constexpr explicit vec(const U & v) noexcept;

        template <Number U> constexpr explicit vec(const vec2<U> & v) noexcept;
        template <Number U> constexpr explicit vec(const vec3<U> & v) noexcept;
        template <Number U> constexpr explicit vec(const vec4<U> & v) noexcept;

        constexpr vec(T v1, T v2) noexcept;

        //--------------------------------------------------------------------------
        // Assignment

        vec & operator=(const vec & v) noexcept = default;
        vec & operator=(vec && v) noexcept = default;

        vec & operator=(T v) noexcept;
        template <int t_n> vec & operator=(const vec<T, t_n> & v) noexcept;

        //--------------------------------------------------------------------------
        // Access

        template <int t_i> T & at() noexcept;
        template <int t_i> constexpr T at() const noexcept;

        T & operator[](int i);
        T operator[](int i) const;

    };

    //==================================================================================================================
    // VEC3 ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //==================================================================================================================

    template <NumberOrBoolean T> struct vec<T, 3> {

        //--------------------------------------------------------------------------
        // Static Members

        using Type = T;

        static constexpr int n{3};

        //--------------------------------------------------------------------------
        // Instance Variables

        T x{};
        T y{};
        T z{};

        //--------------------------------------------------------------------------
        // Construction

        constexpr vec() noexcept = default;
        constexpr vec(const vec & v) noexcept = default;
        constexpr vec(vec && v) noexcept = default;

        constexpr explicit vec(T v) noexcept;
        template <Number U> constexpr explicit vec(const U & v) noexcept;

        template <Number U> constexpr explicit vec(const vec2<U> & v) noexcept;
        template <Number U> constexpr explicit vec(const vec3<U> & v) noexcept;
        template <Number U> constexpr explicit vec(const vec4<U> & v) noexcept;

        constexpr vec(T v1, T v2, T v3) noexcept;
        Q_CONSTEX vec(const vec2<T> & v1, T v2) noexcept;
        Q_CX_ABLE vec(T v1, const vec2<T> & v2) noexcept;

        //--------------------------------------------------------------------------
        // Assignment

        vec & operator=(const vec & v) noexcept = default;
        vec & operator=(vec && v) noexcept = default;

        vec & operator=(T v) noexcept;
        template <int t_n> vec & operator=(const vec<T, t_n> & v) noexcept;

        //--------------------------------------------------------------------------
        // Access

        template <int t_i> T & at() noexcept;
        template <int t_i> constexpr T at() const noexcept;

        T & operator[](int i);
        T operator[](int i) const;

        vec2<T> & xy() noexcept;
        vec2<T> & rg() noexcept { return xy(); }
        vec2<T> & st() noexcept { return xy(); }
        Q_CX_ABLE const vec2<T> & xy() const noexcept;
        Q_CX_ABLE const vec2<T> & rg() const noexcept { return rg(); }
        Q_CX_ABLE const vec2<T> & st() const noexcept { return st(); }

        vec2<T> & yz() noexcept;
        vec2<T> & gb() noexcept { return yz(); }
        vec2<T> & tp() noexcept { return yz(); }
        Q_CX_ABLE const vec2<T> & yz() const noexcept;
        Q_CX_ABLE const vec2<T> & gb() const noexcept { return gb(); }
        Q_CX_ABLE const vec2<T> & tp() const noexcept { return tp(); }

    };

    //==================================================================================================================
    // VEC4 ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //==================================================================================================================

    template <NumberOrBoolean T> struct vec<T, 4> {

        //--------------------------------------------------------------------------
        // Static Members

        using Type = T;

        static constexpr int n{4};

        //--------------------------------------------------------------------------
        // Instance Variables

        T x{};
        T y{};
        T z{};
        T w{};

        //--------------------------------------------------------------------------
        // Construction

        constexpr vec() noexcept = default;
        constexpr vec(const vec & v) noexcept = default;
        constexpr vec(vec && v) noexcept = default;

        constexpr explicit vec(T v) noexcept;
        template <Number U> constexpr explicit vec(const U & v) noexcept;

        template <Number U> constexpr explicit vec(const vec2<U> & v) noexcept;
        template <Number U> constexpr explicit vec(const vec3<U> & v) noexcept;
        template <Number U> constexpr explicit vec(const vec4<U> & v) noexcept;

        constexpr vec(T v1, T v2, T v3, T v4) noexcept;
        Q_CONSTEX vec(const vec2<T> & v1, T v2, T v3) noexcept;
        Q_CX_ABLE vec(T v1, const vec2<T> & v2, T v3) noexcept;
        Q_CX_ABLE vec(T v1, T v2, const vec2<T> & v3) noexcept;
        Q_CONSTEX vec(const vec2<T> & v1, const vec2<T> & v2) noexcept;
        Q_CONSTEX vec(const vec3<T> & v1, T v2) noexcept;
        Q_CX_ABLE vec(T v1, const vec3<T> & v2) noexcept;

        //--------------------------------------------------------------------------
        // Assignment

        vec & operator=(const vec & v) noexcept = default;
        vec & operator=(vec && v) noexcept = default;

        vec & operator=(T v) noexcept;
        template <int t_n> vec & operator=(const vec<T, t_n> & v) noexcept;

        //--------------------------------------------------------------------------
        // Access

        template <int t_i> T & at() noexcept;
        template <int t_i> constexpr T at() const noexcept;

        T & operator[](int i);
        T operator[](int i) const;

        vec2<T> & xy() noexcept;
        vec2<T> & rg() noexcept { return xy(); }
        vec2<T> & st() noexcept { return xy(); }
        Q_CX_ABLE const vec2<T> & xy() const noexcept;
        Q_CX_ABLE const vec2<T> & rg() const noexcept { return rg(); }
        Q_CX_ABLE const vec2<T> & st() const noexcept { return st(); }

        vec2<T> & yz() noexcept;
        vec2<T> & gb() noexcept { return yz(); }
        vec2<T> & tp() noexcept { return yz(); }
        Q_CX_ABLE const vec2<T> & yz() const noexcept;
        Q_CX_ABLE const vec2<T> & gb() const noexcept { return gb(); }
        Q_CX_ABLE const vec2<T> & tp() const noexcept { return tp(); }

        vec2<T> & zw() noexcept;
        vec2<T> & ba() noexcept { return zw(); }
        vec2<T> & pq() noexcept { return zw(); }
        Q_CX_ABLE const vec2<T> & zw() const noexcept;
        Q_CX_ABLE const vec2<T> & ba() const noexcept { return ba(); }
        Q_CX_ABLE const vec2<T> & pq() const noexcept { return pq(); }

        vec3<T> & xyz() noexcept;
        vec3<T> & rgb() noexcept { return xyz(); }
        vec3<T> & stp() noexcept { return xyz(); }
        Q_CX_ABLE const vec3<T> & xyz() const noexcept;
        Q_CX_ABLE const vec3<T> & rgb() const noexcept { return rgb(); }
        Q_CX_ABLE const vec3<T> & stp() const noexcept { return stp(); }

        vec3<T> & yzw() noexcept;
        vec3<T> & gba() noexcept { return yzw(); }
        vec3<T> & tpq() noexcept { return yzw(); }
        Q_CX_ABLE const vec3<T> & yzw() const noexcept;
        Q_CX_ABLE const vec3<T> & gba() const noexcept { return gba(); }
        Q_CX_ABLE const vec3<T> & tpq() const noexcept { return tpq(); }

    };

    //==================================================================================================================
    // Constants ///////////////////////////////////////////////////////////////////////////////////////////////////////
    //------------------------------------------------------------------------------------------------------------------

    template <typename T, int t_n> constexpr vec<T, t_n> px{};
    template <typename T, int t_n> constexpr vec<T, t_n> nx{};
    template <typename T, int t_n> constexpr vec<T, t_n> py{};
    template <typename T, int t_n> constexpr vec<T, t_n> ny{};
    template <typename T, int t_n> constexpr vec<T, t_n> pz{};
    template <typename T, int t_n> constexpr vec<T, t_n> nz{};
    template <typename T, int t_n> constexpr vec<T, t_n> pw{};
    template <typename T, int t_n> constexpr vec<T, t_n> nw{};
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

    template <Floater T, int t_n> constexpr vec<T, t_n> infvec = vec<T, t_n>(infinity<T>);
    template <Floater T, int t_n> constexpr vec<T, t_n> nanvec = vec<T, t_n>(     nan<T>);

    //==================================================================================================================
    // Functions ///////////////////////////////////////////////////////////////////////////////////////////////////////
    //==================================================================================================================

    //==============================================================================
    // Arithmetic Assignment
    //------------------------------------------------------------------------------

    template <Number T, int t_n> vec<T, t_n> & operator++(vec<T, t_n> & v);
    template <Number T, int t_n> vec<T, t_n>   operator++(vec<T, t_n> & v, int);

    template <Number T, int t_n> vec<T, t_n> & operator--(vec<T, t_n> & v);
    template <Number T, int t_n> vec<T, t_n>   operator--(vec<T, t_n> & v, int);

    template <Number T, int t_n> vec<T, t_n> & operator+=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
    template <Number T, int t_n> vec<T, t_n> & operator+=(vec<T, t_n> & v1, T v2);

    template <Number T, int t_n> vec<T, t_n> & operator-=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
    template <Number T, int t_n> vec<T, t_n> & operator-=(vec<T, t_n> & v1, T v2);

    template <Number T, int t_n> vec<T, t_n> & operator*=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
    template <Number T, int t_n> vec<T, t_n> & operator*=(vec<T, t_n> & v1, T v2);

    template <Number T, int t_n> vec<T, t_n> & operator/=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
    template <Number T, int t_n> vec<T, t_n> & operator/=(vec<T, t_n> & v1, T v2);

    template <Number T, int t_n> vec<T, t_n> & operator%=(vec<T, t_n> & v1, const vec<T, t_n> & v2);
    template <Number T, int t_n> vec<T, t_n> & operator%=(vec<T, t_n> & v1, T v2);

    //==============================================================================
    // Arithmetic
    //------------------------------------------------------------------------------

    template <Number T, int t_n> Q_CX_ABLE vec<T, t_n> operator+(const vec<T, t_n> & v);

    template <Number T, int t_n> Q_CX_ABLE vec<T, t_n> operator-(const vec<T, t_n> & v);

    template <Number T, int t_n> Q_CX_ABLE  vec<T, t_n> operator+(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
    template <Number T, int t_n> Q_CX_ABLE  vec<T, t_n> operator+(const vec<T, t_n> & v1, T v2);
    template <Number T, int t_n> Q_CX_ABLE  vec<T, t_n> operator+(T v1, const vec<T, t_n> & v2);

    template <Number T, int t_n> Q_CX_ABLE  vec<T, t_n> operator-(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
    template <Number T, int t_n> Q_CX_ABLE  vec<T, t_n> operator-(const vec<T, t_n> & v1, T v2);
    template <Number T, int t_n> Q_CX_ABLE  vec<T, t_n> operator-(T v1, const vec<T, t_n> & v2);

    template <Number T, int t_n> Q_CX_ABLE  vec<T, t_n> operator*(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
    template <Number T, int t_n> Q_CX_ABLE  vec<T, t_n> operator*(const vec<T, t_n> & v1, T v2);
    template <Number T, int t_n> Q_CX_ABLE  vec<T, t_n> operator*(T v1, const vec<T, t_n> & v2);

    template <Number T, int t_n> Q_CX_ABLE  vec<T, t_n> operator/(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
    template <Number T, int t_n> Q_CX_ABLE  vec<T, t_n> operator/(const vec<T, t_n> & v1, T v2);
    template <Number T, int t_n> Q_CX_ABLE  vec<T, t_n> operator/(T v1, const vec<T, t_n> & v2);

    template <Number T, int t_n> Q_CX_ABLE vec<T, t_n> operator%(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
    template <Number T, int t_n> Q_CX_ABLE vec<T, t_n> operator%(const vec<T, t_n> & v1, T v2);
    template <Number T, int t_n> Q_CX_ABLE vec<T, t_n> operator%(T v1, const vec<T, t_n> & v2);

    //==============================================================================
    // Comparison
    //------------------------------------------------------------------------------

    template <typename T, int t_n> Q_CX_ABLE      bool operator==(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
    template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator==(const vec<T, t_n> & v1, T v2);
    template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator==(T v1, const vec<T, t_n> & v2);

    template <typename T, int t_n> Q_CX_ABLE      bool operator!=(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
    template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator!=(const vec<T, t_n> & v1, T v2);
    template <typename T, int t_n> Q_CX_ABLE bvec<t_n> operator!=(T v1, const vec<T, t_n> & v2);

    template <Number T, int t_n> Q_CX_ABLE bvec<t_n> operator<(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
    template <Number T, int t_n> Q_CX_ABLE bvec<t_n> operator<(const vec<T, t_n> & v1, T v2);
    template <Number T, int t_n> Q_CX_ABLE bvec<t_n> operator<(T v1, const vec<T, t_n> & v2);

    template <Number T, int t_n> Q_CX_ABLE bvec<t_n> operator>(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
    template <Number T, int t_n> Q_CX_ABLE bvec<t_n> operator>(const vec<T, t_n> & v1, T v2);
    template <Number T, int t_n> Q_CX_ABLE bvec<t_n> operator>(T v1, const vec<T, t_n> & v2);

    template <Number T, int t_n> Q_CX_ABLE bvec<t_n> operator<=(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
    template <Number T, int t_n> Q_CX_ABLE bvec<t_n> operator<=(const vec<T, t_n> & v1, T v2);
    template <Number T, int t_n> Q_CX_ABLE bvec<t_n> operator<=(T v1, const vec<T, t_n> & v2);

    template <Number T, int t_n> Q_CX_ABLE bvec<t_n> operator>=(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
    template <Number T, int t_n> Q_CX_ABLE bvec<t_n> operator>=(const vec<T, t_n> & v1, T v2);
    template <Number T, int t_n> Q_CX_ABLE bvec<t_n> operator>=(T v1, const vec<T, t_n> & v2);

    //==============================================================================
    // Logic
    //------------------------------------------------------------------------------

    template <int t_n> Q_CX_ABLE bvec<t_n> operator&&(const bvec<t_n> & v1, const bvec<t_n> & v2);

    template <int t_n> Q_CX_ABLE bvec<t_n> operator||(const bvec<t_n> & v1, const bvec<t_n> & v2);

    template <int t_n> Q_CX_ABLE bvec<t_n> operator!(const bvec<t_n> & v1);

    //==============================================================================
    // Condensation
    //------------------------------------------------------------------------------

    template <Number  T, int t_n> Q_CX_ABLE T sum(const vec<T, t_n> & v);

    template <Number T, int t_n> Q_CX_ABLE T product(const vec<T, t_n> & v);

    template <int t_n> Q_CX_ABLE bool any(const bvec<t_n> & v);

    template <int t_n> Q_CX_ABLE bool all(const bvec<t_n> & v);

    //==============================================================================
    // min
    //------------------------------------------------------------------------------

    template <Number T, int t_n> Q_CX_ABLE           T min(const vec<T, t_n> & v);
    template <Number T, int t_n> Q_CX_ABLE vec<T, t_n> min(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
    template <Number T, int t_n> Q_CX_ABLE vec<T, t_n> min(const vec<T, t_n> & v1, T v2);
    template <Number T, int t_n> Q_CX_ABLE vec<T, t_n> min(T v1, const vec<T, t_n> & v2);

    //==============================================================================
    // max
    //------------------------------------------------------------------------------

    template <Number T, int t_n> Q_CX_ABLE           T max(const vec<T, t_n> & v);
    template <Number T, int t_n> Q_CX_ABLE vec<T, t_n> max(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
    template <Number T, int t_n> Q_CX_ABLE vec<T, t_n> max(const vec<T, t_n> & v1, T v2);
    template <Number T, int t_n> Q_CX_ABLE vec<T, t_n> max(T v1, const vec<T, t_n> & v2);

    //==============================================================================
    // minify
    //------------------------------------------------------------------------------

    template <Number T, int t_n> vec<T, t_n> & minify(vec<T, t_n> & min, const vec<T, t_n> & v);
    template <Number T, int t_n> vec<T, t_n> & minify(vec<T, t_n> & min, T v);

    //==============================================================================
    // maxify
    //------------------------------------------------------------------------------

    template <Number T, int t_n> vec<T, t_n> & maxify(vec<T, t_n> & max, const vec<T, t_n> & v);
    template <Number T, int t_n> vec<T, t_n> & maxify(vec<T, t_n> & max, T v);

}

// INLINE IMPLEMENTATION ///////////////////////////////////////////////////////////////////////////////////////////////

namespace qc {

    //==================================================================================================================
    // VEC2 IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////
    //==================================================================================================================

    //------------------------------------------------------------------------------
    // Constructors

    template <NumberOrBoolean T>
    inline constexpr vec<T, 2>::vec(T v) noexcept :
        x(v), y(v)
    {}

    template <NumberOrBoolean T>
    template <Number U>
    inline constexpr vec<T, 2>::vec(const U & v) noexcept :
        x(T(v)), y(T(v))
    {}

    template <NumberOrBoolean T>
    template <Number U>
    inline constexpr vec<T, 2>::vec(const vec2<U> & v) noexcept :
        x(T(v.x)), y(T(v.y))
    {}

    template <NumberOrBoolean T>
    template <Number U>
    inline constexpr vec<T, 2>::vec(const vec3<U> & v) noexcept :
        x(T(v.x)), y(T(v.y))
    {}

    template <NumberOrBoolean T>
    template <Number U>
    inline constexpr vec<T, 2>::vec(const vec4<U> & v) noexcept :
        x(T(v.x)), y(T(v.y))
    {}

    template <NumberOrBoolean T>
    inline constexpr vec<T, 2>::vec(T v1, T v2) noexcept :
        x(v1), y(v2)
    {}

    //------------------------------------------------------------------------------
    // Assignment

    template <NumberOrBoolean T>
    inline vec2<T> & vec<T, 2>::operator=(T v) noexcept {
        x = v; y = v;
        return *this;
    }

    template <NumberOrBoolean T>
    template <int t_n>
    inline vec2<T> & vec<T, 2>::operator=(const vec<T, t_n> & v) noexcept {
        if constexpr (t_n >= 1) x = v.x; else x = T(0);
        if constexpr (t_n >= 2) y = v.y; else y = T(0);
        return *this;
    }

    //------------------------------------------------------------------------------
    // Access

    template <NumberOrBoolean T>
    template <int t_i>
    inline T & vec<T, 2>::at() noexcept {
        static_assert(t_i >= 0 && t_i <= 1, "Index out of bounds");
        if constexpr (t_i == 0) return x;
        if constexpr (t_i == 1) return y;
    }

    template <NumberOrBoolean T>
    template <int t_i>
    inline constexpr T vec<T, 2>::at() const noexcept {
        static_assert(t_i >= 0 && t_i <= 1, "Index out of bounds");
        if constexpr (t_i == 0) return x;
        if constexpr (t_i == 1) return y;
    }

    template <NumberOrBoolean T>
    inline T & vec<T, 2>::operator[](int i) {
        return *(&x + i);
    }

    template <NumberOrBoolean T>
    inline T vec<T, 2>::operator[](int i) const {
        return *(&x + i);
    }

    //==================================================================================================================
    // VEC3 IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////
    //==================================================================================================================

    //------------------------------------------------------------------------------
    // Constructors

    template <NumberOrBoolean T>
    inline constexpr vec<T, 3>::vec(T v) noexcept :
        x(v), y(v), z(v)
    {}

    template <NumberOrBoolean T>
    template <Number U>
    inline constexpr vec<T, 3>::vec(const U & v) noexcept :
        x(T(v)), y(T(v)), z(T(v))
    {}

    template <NumberOrBoolean T>
    template <Number U>
    inline constexpr vec<T, 3>::vec(const vec2<U> & v) noexcept :
        x(T(v.x)), y(T(v.y)), z()
    {}

    template <NumberOrBoolean T>
    template <Number U>
    inline constexpr vec<T, 3>::vec(const vec3<U> & v) noexcept :
        x(T(v.x)), y(T(v.y)), z(T(v.z))
    {}

    template <NumberOrBoolean T>
    template <Number U>
    inline constexpr vec<T, 3>::vec(const vec4<U> & v) noexcept :
        x(T(v.x)), y(T(v.y)), z(T(v.z))
    {}

    template <NumberOrBoolean T>
    inline constexpr vec<T, 3>::vec(T v1, T v2, T v3) noexcept :
        x(v1), y(v2), z(v3)
    {}

    template <NumberOrBoolean T>
    inline Q_CONSTEX vec<T, 3>::vec(const vec2<T> & v1, T v2) noexcept :
        x(v1.x), y(v1.y), z(v2)
    {}

    template <NumberOrBoolean T>
    inline Q_CX_ABLE vec<T, 3>::vec(T v1, const vec2<T> & v2) noexcept :
        x(v1), y(v2.x), z(v2.y)
    {}

    //------------------------------------------------------------------------------
    // Assignment

    template <NumberOrBoolean T>
    inline vec3<T> & vec<T, 3>::operator=(T v) noexcept {
        x = v; y = v; z = v;
        return *this;
    }

    template <NumberOrBoolean T>
    template <int t_n>
    inline vec3<T> & vec<T, 3>::operator=(const vec<T, t_n> & v) noexcept {
        if constexpr (t_n >= 1) x = v.x; else x = T(0);
        if constexpr (t_n >= 2) y = v.y; else y = T(0);
        if constexpr (t_n >= 3) z = v.z; else z = T(0);
        return *this;
    }

    //------------------------------------------------------------------------------
    // Access

    template <NumberOrBoolean T>
    template <int t_i>
    inline T & vec<T, 3>::at() noexcept {
        static_assert(t_i >= 0 && t_i <= 2, "Index out of bounds");
        if constexpr (t_i == 0) return x;
        if constexpr (t_i == 1) return y;
        if constexpr (t_i == 2) return z;
    }

    template <NumberOrBoolean T>
    template <int t_i>
    inline constexpr T vec<T, 3>::at() const noexcept {
        static_assert(t_i >= 0 && t_i <= 2, "Index out of bounds");
        if constexpr (t_i == 0) return x;
        if constexpr (t_i == 1) return y;
        if constexpr (t_i == 2) return z;
    }

    template <NumberOrBoolean T>
    inline T & vec<T, 3>::operator[](int i) {
        return *(&x + i);
    }

    template <NumberOrBoolean T>
    inline T vec<T, 3>::operator[](int i) const {
        return *(&x + i);
    }

    template <NumberOrBoolean T>
    inline vec2<T> & vec<T, 3>::xy() noexcept {
        return reinterpret_cast<vec2<T> &>(x);
    }

    template <NumberOrBoolean T>
    inline Q_CX_ABLE const vec2<T> & vec<T, 3>::xy() const noexcept {
        return reinterpret_cast<const vec2<T> &>(x);
    }

    template <NumberOrBoolean T>
    inline vec2<T> & vec<T, 3>::yz() noexcept {
        return reinterpret_cast<vec2<T> &>(y);
    }

    template <NumberOrBoolean T>
    inline Q_CX_ABLE const vec2<T> & vec<T, 3>::yz() const noexcept {
        return reinterpret_cast<const vec2<T> &>(y);
    }

    //==================================================================================================================
    // VEC4 IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////
    //==================================================================================================================

    //------------------------------------------------------------------------------
    // Constructors

    template <NumberOrBoolean T>
    inline constexpr vec<T, 4>::vec(T v) noexcept :
        x(v), y(v), z(v), w(v)
    {}

    template <NumberOrBoolean T>
    template <Number U>
    inline constexpr vec<T, 4>::vec(const U & v) noexcept :
        x(T(v)), y(T(v)), z(T(v)), w(T(v))
    {}

    template <NumberOrBoolean T>
    template <Number U>
    inline constexpr vec<T, 4>::vec(const vec2<U> & v) noexcept :
        x(T(v.x)), y(T(v.y)), z(), w()
    {}

    template <NumberOrBoolean T>
    template <Number U>
    inline constexpr vec<T, 4>::vec(const vec3<U> & v) noexcept :
        x(T(v.x)), y(T(v.y)), z(T(v.z)), w()
    {}

    template <NumberOrBoolean T>
    template <Number U>
    inline constexpr vec<T, 4>::vec(const vec4<U> & v) noexcept :
        x(T(v.x)), y(T(v.y)), z(T(v.z)), w(T(v.w))
    {}

    template <NumberOrBoolean T>
    inline constexpr vec<T, 4>::vec(T v1, T v2, T v3, T v4) noexcept :
        x(v1), y(v2), z(v3), w(v4)
    {}

    template <NumberOrBoolean T>
    inline Q_CONSTEX vec<T, 4>::vec(const vec2<T> & v1, T v2, T v3) noexcept :
        x(v1.x), y(v1.y), z(v2), w(v3)
    {}

    template <NumberOrBoolean T>
    inline Q_CX_ABLE vec<T, 4>::vec(T v1, const vec2<T> & v2, T v3) noexcept :
        x(v1), y(v2.x), z(v2.y), w(v3)
    {}

    template <NumberOrBoolean T>
    inline Q_CX_ABLE vec<T, 4>::vec(T v1, T v2, const vec2<T> & v3) noexcept :
        x(v1), y(v2), z(v3.x), w(v3.y)
    {}

    template <NumberOrBoolean T>
    inline Q_CONSTEX vec<T, 4>::vec(const vec2<T> & v1, const vec2<T> & v2) noexcept :
        x(v1.x), y(v1.y), z(v2.x), w(v2.y)
    {}

    template <NumberOrBoolean T>
    inline Q_CONSTEX vec<T, 4>::vec(const vec3<T> & v1, T v2) noexcept :
        x(v1.x), y(v1.y), z(v1.z), w(v2)
    {}

    template <NumberOrBoolean T>
    inline Q_CX_ABLE vec<T, 4>::vec(T v1, const vec3<T> & v2) noexcept :
        x(v1), y(v2.x), z(v2.y), w(v2.z)
    {}

    //------------------------------------------------------------------------------
    // Assignment

    template <NumberOrBoolean T>
    inline vec4<T> & vec<T, 4>::operator=(T v) noexcept {
        x = v; y = v; z = v; w = v;
        return *this;
    }

    template <NumberOrBoolean T>
    template <int t_n>
    inline vec4<T> & vec<T, 4>::operator=(const vec<T, t_n> & v) noexcept {
        if constexpr (t_n >= 1) x = v.x; else x = T(0);
        if constexpr (t_n >= 2) y = v.y; else y = T(0);
        if constexpr (t_n >= 3) z = v.z; else z = T(0);
        if constexpr (t_n >= 4) w = v.w; else w = T(0);
        return *this;
    }

    //------------------------------------------------------------------------------
    // Access

    template <NumberOrBoolean T>
    template <int t_i>
    inline T & vec<T, 4>::at() noexcept {
        static_assert(t_i >= 0 && t_i <= 3, "Index out of bounds");
        if constexpr (t_i == 0) return x;
        if constexpr (t_i == 1) return y;
        if constexpr (t_i == 2) return z;
        if constexpr (t_i == 3) return w;
    }

    template <NumberOrBoolean T>
    template <int t_i>
    inline constexpr T vec<T, 4>::at() const noexcept {
        static_assert(t_i >= 0 && t_i <= 3, "Index out of bounds");
        if constexpr (t_i == 0) return x;
        if constexpr (t_i == 1) return y;
        if constexpr (t_i == 2) return z;
        if constexpr (t_i == 3) return w;
    }

    template <NumberOrBoolean T>
    inline T & vec<T, 4>::operator[](int i) {
        return *(&x + i);
    }

    template <NumberOrBoolean T>
    inline T vec<T, 4>::operator[](int i) const {
        return *(&x + i);
    }

    template <NumberOrBoolean T>
    inline vec2<T> & vec<T, 4>::xy() noexcept {
        return reinterpret_cast<vec2<T> &>(x);
    }

    template <NumberOrBoolean T>
    inline Q_CX_ABLE const vec2<T> & vec<T, 4>::xy() const noexcept {
        return reinterpret_cast<const vec2<T> &>(x);
    }

    template <NumberOrBoolean T>
    inline vec2<T> & vec<T, 4>::yz() noexcept {
        return reinterpret_cast<vec2<T> &>(y);
    }

    template <NumberOrBoolean T>
    inline Q_CX_ABLE const vec2<T> & vec<T, 4>::yz() const noexcept {
        return reinterpret_cast<const vec2<T> &>(y);
    }

    template <NumberOrBoolean T>
    inline vec2<T> & vec<T, 4>::zw() noexcept {
        return reinterpret_cast<vec2<T> &>(z);
    }

    template <NumberOrBoolean T>
    inline Q_CX_ABLE const vec2<T> & vec<T, 4>::zw() const noexcept {
        return reinterpret_cast<const vec2<T> &>(z);
    }

    template <NumberOrBoolean T>
    inline vec3<T> & vec<T, 4>::xyz() noexcept {
        return reinterpret_cast<vec3<T> &>(x);
    }

    template <NumberOrBoolean T>
    inline Q_CX_ABLE const vec3<T> & vec<T, 4>::xyz() const noexcept {
        return reinterpret_cast<const vec3<T> &>(x);
    }

    template <NumberOrBoolean T>
    inline vec3<T> & vec<T, 4>::yzw() noexcept {
        return reinterpret_cast<vec3<T> &>(y);
    }

    template <NumberOrBoolean T>
    inline Q_CX_ABLE const vec3<T> & vec<T, 4>::yzw() const noexcept {
        return reinterpret_cast<const vec3<T> &>(y);
    }

    //==================================================================================================================
    // FUNCTION IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////
    //==================================================================================================================

    //------------------------------------------------------------------------------
    // Arithmetic Assignment

    //--- pre increment ---

    template <Number T, int t_n>
    inline vec<T, t_n> & operator++(vec<T, t_n> & v) {
        if constexpr (t_n >= 1) ++v.x;
        if constexpr (t_n >= 2) ++v.y;
        if constexpr (t_n >= 3) ++v.z;
        if constexpr (t_n >= 4) ++v.w;
        return v;
    }

    //--- post increment ---

    template <Number T, int t_n>
    inline vec<T, t_n> operator++(vec<T, t_n> & v, int) {
        vec<T, t_n> temp(v);
        ++v;
        return temp;
    }

    //--- pre decrement ---

    template <Number T, int t_n>
    inline vec<T, t_n> & operator--(vec<T, t_n> & v) {
        if constexpr (t_n >= 1) --v.x;
        if constexpr (t_n >= 2) --v.y;
        if constexpr (t_n >= 3) --v.z;
        if constexpr (t_n >= 4) --v.w;
        return v;
    }

    //--- post decrement ---

    template <Number T, int t_n>
    inline vec<T, t_n> operator--(vec<T, t_n> & v, int) {
        vec<T, t_n> temp(v);
        --v;
        return temp;
    }

    //--- add assign ---

    template <Number T, int t_n>
    inline vec<T, t_n> & operator+=(vec<T, t_n> & v1, const vec<T, t_n> & v2) {
        if constexpr (t_n >= 1) v1.x += v2.x;
        if constexpr (t_n >= 2) v1.y += v2.y;
        if constexpr (t_n >= 3) v1.z += v2.z;
        if constexpr (t_n >= 4) v1.w += v2.w;
        return v1;
    }

    template <Number T, int t_n>
    inline vec<T, t_n> & operator+=(vec<T, t_n> & v1, T v2) {
        if constexpr (t_n >= 1) v1.x += v2;
        if constexpr (t_n >= 2) v1.y += v2;
        if constexpr (t_n >= 3) v1.z += v2;
        if constexpr (t_n >= 4) v1.w += v2;
        return v1;
    }

    //--- subtract assign ---

    template <Number T, int t_n>
    inline vec<T, t_n> & operator-=(vec<T, t_n> & v1, const vec<T, t_n> & v2) {
        if constexpr (t_n >= 1) v1.x -= v2.x;
        if constexpr (t_n >= 2) v1.y -= v2.y;
        if constexpr (t_n >= 3) v1.z -= v2.z;
        if constexpr (t_n >= 4) v1.w -= v2.w;
        return v1;
    }

    template <Number T, int t_n>
    inline vec<T, t_n> & operator-=(vec<T, t_n> & v1, T v2) {
        if constexpr (t_n >= 1) v1.x -= v2;
        if constexpr (t_n >= 2) v1.y -= v2;
        if constexpr (t_n >= 3) v1.z -= v2;
        if constexpr (t_n >= 4) v1.w -= v2;
        return v1;
    }

    //--- multiply assign ---

    template <Number T, int t_n>
    inline vec<T, t_n> & operator*=(vec<T, t_n> & v1, const vec<T, t_n> & v2) {
        if constexpr (t_n >= 1) v1.x *= v2.x;
        if constexpr (t_n >= 2) v1.y *= v2.y;
        if constexpr (t_n >= 3) v1.z *= v2.z;
        if constexpr (t_n >= 4) v1.w *= v2.w;
        return v1;
    }

    template <Number T, int t_n>
    inline vec<T, t_n> & operator*=(vec<T, t_n> & v1, T v2) {
        if constexpr (t_n >= 1) v1.x *= v2;
        if constexpr (t_n >= 2) v1.y *= v2;
        if constexpr (t_n >= 3) v1.z *= v2;
        if constexpr (t_n >= 4) v1.w *= v2;
        return v1;
    }

    //--- divide assign ---

    template <Number T, int t_n>
    inline vec<T, t_n> & operator/=(vec<T, t_n> & v1, const vec<T, t_n> & v2) {
        if constexpr (t_n >= 1) v1.x /= v2.x;
        if constexpr (t_n >= 2) v1.y /= v2.y;
        if constexpr (t_n >= 3) v1.z /= v2.z;
        if constexpr (t_n >= 4) v1.w /= v2.w;
        return v1;
    }

    template <Number T, int t_n>
    inline vec<T, t_n> & operator/=(vec<T, t_n> & v1, T v2) {
        if constexpr (t_n > 1 && std::is_floating_point_v<T>) return v1 *= T(1.0) / v2;
        if constexpr (t_n >= 1) v1.x /= v2;
        if constexpr (t_n >= 2) v1.y /= v2;
        if constexpr (t_n >= 3) v1.z /= v2;
        if constexpr (t_n >= 4) v1.w /= v2;
        return v1;
    }

    //--- modulus assign ---

    template <Number T, int t_n>
    inline vec<T, t_n> & operator%=(vec<T, t_n> & v1, const vec<T, t_n> & v2) {
        if constexpr (t_n >= 1) v1.x = mod(v1.x, v2.x);
        if constexpr (t_n >= 2) v1.y = mod(v1.y, v2.y);
        if constexpr (t_n >= 3) v1.z = mod(v1.z, v2.z);
        if constexpr (t_n >= 4) v1.w = mod(v1.w, v2.w);
        return v1;
    }

    template <Number T, int t_n>
    inline vec<T, t_n> & operator%=(vec<T, t_n> & v1, T v2) {
        if constexpr (t_n >= 1) v1.x = mod(v1.x, v2);
        if constexpr (t_n >= 2) v1.y = mod(v1.y, v2);
        if constexpr (t_n >= 3) v1.z = mod(v1.z, v2);
        if constexpr (t_n >= 4) v1.w = mod(v1.w, v2);
        return v1;
    }

    //------------------------------------------------------------------------------
    // Arithmetic Operators

    //--- positive ---

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> operator+(const vec<T, t_n> & v) {
        return v;
    }

    //--- negative ---

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> operator-(const vec<T, t_n> & v) {
        if constexpr (std::is_unsigned_v<T>) return v;
        if constexpr (!std::is_unsigned_v<T>) {
            if constexpr (t_n == 2) return {-v.x, -v.y};
            if constexpr (t_n == 3) return {-v.x, -v.y, -v.z};
            if constexpr (t_n == 4) return {-v.x, -v.y, -v.z, -v.w};
        }
    }

    //--- add ---

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> operator+(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
        if constexpr (t_n == 2) return {T(v1.x + v2.x), T(v1.y + v2.y)};
        if constexpr (t_n == 3) return {T(v1.x + v2.x), T(v1.y + v2.y), T(v1.z + v2.z)};
        if constexpr (t_n == 4) return {T(v1.x + v2.x), T(v1.y + v2.y), T(v1.z + v2.z), T(v1.w + v2.w)};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> operator+(const vec<T, t_n> & v1, T v2) {
        if constexpr (t_n == 2) return {T(v1.x + v2), T(v1.y + v2)};
        if constexpr (t_n == 3) return {T(v1.x + v2), T(v1.y + v2), T(v1.z + v2)};
        if constexpr (t_n == 4) return {T(v1.x + v2), T(v1.y + v2), T(v1.z + v2), T(v1.w + v2)};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> operator+(T v1, const vec<T, t_n> & v2) {
        return v2 + v1;
    }

    //--- subtract ---

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> operator-(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
        if constexpr (t_n == 2) return {T(v1.x - v2.x), T(v1.y - v2.y)};
        if constexpr (t_n == 3) return {T(v1.x - v2.x), T(v1.y - v2.y), T(v1.z - v2.z)};
        if constexpr (t_n == 4) return {T(v1.x - v2.x), T(v1.y - v2.y), T(v1.z - v2.z), T(v1.w - v2.w)};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> operator-(const vec<T, t_n> & v1, T v2) {
        if constexpr (t_n == 2) return {T(v1.x - v2), T(v1.y - v2)};
        if constexpr (t_n == 3) return {T(v1.x - v2), T(v1.y - v2), T(v1.z - v2)};
        if constexpr (t_n == 4) return {T(v1.x - v2), T(v1.y - v2), T(v1.z - v2), T(v1.w - v2)};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> operator-(T v1, const vec<T, t_n> & v2) {
        if constexpr (t_n == 2) return {T(v1 - v2.x), T(v1 - v2.y)};
        if constexpr (t_n == 3) return {T(v1 - v2.x), T(v1 - v2.y), T(v1 - v2.z)};
        if constexpr (t_n == 4) return {T(v1 - v2.x), T(v1 - v2.y), T(v1 - v2.z), T(v1 - v2.w)};
    }

    //--- multiply ---

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> operator*(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
        if constexpr (t_n == 2) return {T(v1.x * v2.x), T(v1.y * v2.y)};
        if constexpr (t_n == 3) return {T(v1.x * v2.x), T(v1.y * v2.y), T(v1.z * v2.z)};
        if constexpr (t_n == 4) return {T(v1.x * v2.x), T(v1.y * v2.y), T(v1.z * v2.z), T(v1.w * v2.w)};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> operator*(const vec<T, t_n> & v1, T v2) {
        if constexpr (t_n == 2) return {T(v1.x * v2), T(v1.y * v2)};
        if constexpr (t_n == 3) return {T(v1.x * v2), T(v1.y * v2), T(v1.z * v2)};
        if constexpr (t_n == 4) return {T(v1.x * v2), T(v1.y * v2), T(v1.z * v2), T(v1.w * v2)};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> operator*(T v1, const vec<T, t_n> & v2) {
        if constexpr (t_n == 2) return {T(v1 * v2.x), T(v1 * v2.y)};
        if constexpr (t_n == 3) return {T(v1 * v2.x), T(v1 * v2.y), T(v1 * v2.z)};
        if constexpr (t_n == 4) return {T(v1 * v2.x), T(v1 * v2.y), T(v1 * v2.z), T(v1 * v2.w)};
    }

    //--- divide ---

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> operator/(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
        if constexpr (t_n == 2) return {T(v1.x / v2.x), T(v1.y / v2.y)};
        if constexpr (t_n == 3) return {T(v1.x / v2.x), T(v1.y / v2.y), T(v1.z / v2.z)};
        if constexpr (t_n == 4) return {T(v1.x / v2.x), T(v1.y / v2.y), T(v1.z / v2.z), T(v1.w / v2.w)};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> operator/(const vec<T, t_n> & v1, T v2) {
        if constexpr (std::is_floating_point_v<T>) {
            return v1 * (T(1.0) / v2);
        }
        else {
            if constexpr (t_n == 2) return {T(v1.x / v2), T(v1.y / v2)};
            if constexpr (t_n == 3) return {T(v1.x / v2), T(v1.y / v2), T(v1.z / v2)};
            if constexpr (t_n == 4) return {T(v1.x / v2), T(v1.y / v2), T(v1.z / v2), T(v1.w / v2)};
        }
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> operator/(T v1, const vec<T, t_n> & v2) {
        if constexpr (t_n == 2) return {T(v1 / v2.x), T(v1 / v2.y)};
        if constexpr (t_n == 3) return {T(v1 / v2.x), T(v1 / v2.y), T(v1 / v2.z)};
        if constexpr (t_n == 4) return {T(v1 / v2.x), T(v1 / v2.y), T(v1 / v2.z), T(v1 / v2.w)};
    }

    //--- modulus ---

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> operator%(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
        if constexpr (t_n == 2) return {mod(v1.x, v2.x), mod(v1.y, v2.y)};
        if constexpr (t_n == 3) return {mod(v1.x, v2.x), mod(v1.y, v2.y), mod(v1.z, v2.z)};
        if constexpr (t_n == 4) return {mod(v1.x, v2.x), mod(v1.y, v2.y), mod(v1.z, v2.z), mod(v1.w, v2.w)};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> operator%(const vec<T, t_n> & v1, T v2) {
        if constexpr (t_n == 2) return {mod(v1.x, v2), mod(v1.y, v2)};
        if constexpr (t_n == 3) return {mod(v1.x, v2), mod(v1.y, v2), mod(v1.z, v2)};
        if constexpr (t_n == 4) return {mod(v1.x, v2), mod(v1.y, v2), mod(v1.z, v2), mod(v1.w, v2)};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> operator%(T v1, const vec<T, t_n> & v2) {
        if constexpr (t_n == 2) return {mod(v1, v2.x), mod(v1, v2.y)};
        if constexpr (t_n == 3) return {mod(v1, v2.x), mod(v1, v2.y), mod(v1, v2.z)};
        if constexpr (t_n == 4) return {mod(v1, v2.x), mod(v1, v2.y), mod(v1, v2.z), mod(v1, v2.w)};
    }

    //------------------------------------------------------------------------------
    // Comparison Operators

    //--- equal to ---

    template <typename T, int t_n>
    inline Q_CX_ABLE bool operator==(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
        if constexpr (t_n == 2) return v1.x == v2.x && v1.y == v2.y;
        if constexpr (t_n == 3) return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
        if constexpr (t_n == 4) return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
    }

    template <typename T, int t_n>
    inline Q_CX_ABLE bvec<t_n> operator==(const vec<T, t_n> & v1, T v2) {
        if constexpr (t_n == 2) return {v1.x == v2, v1.y == v2};
        if constexpr (t_n == 3) return {v1.x == v2, v1.y == v2, v1.z == v2};
        if constexpr (t_n == 4) return {v1.x == v2, v1.y == v2, v1.z == v2, v1.w == v2};
    }

    template <typename T, int t_n>
    inline Q_CX_ABLE bvec<t_n> operator==(T v1, const vec<T, t_n> & v2) {
        return v2 == v1;
    }

    //--- not equal to ---

    template <typename T, int t_n>
    inline Q_CX_ABLE bool operator!=(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
        return !(v1 == v2);
    }

    template <typename T, int t_n>
    inline Q_CX_ABLE bvec<t_n> operator!=(const vec<T, t_n> & v1, T v2) {
        return !(v1 == v2);
    }

    template <typename T, int t_n>
    inline Q_CX_ABLE bvec<t_n> operator!=(T v1, const vec<T, t_n> & v2) {
        return !(v1 == v2);
    }

    //--- less than ---

    template <Number T, int t_n>
    inline Q_CX_ABLE bvec<t_n> operator<(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
        if constexpr (t_n == 2) return {v1.x < v2.x, v1.y < v2.y};
        if constexpr (t_n == 3) return {v1.x < v2.x, v1.y < v2.y, v1.z < v2.z};
        if constexpr (t_n == 4) return {v1.x < v2.x, v1.y < v2.y, v1.z < v2.z, v1.w < v2.w};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE bvec<t_n> operator<(const vec<T, t_n> & v1, T v2) {
        if constexpr (t_n == 2) return {v1.x < v2, v1.y < v2};
        if constexpr (t_n == 3) return {v1.x < v2, v1.y < v2, v1.z < v2};
        if constexpr (t_n == 4) return {v1.x < v2, v1.y < v2, v1.z < v2, v1.w < v2};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE bvec<t_n> operator<(T v1, const vec<T, t_n> & v2) {
        if constexpr (t_n == 2) return {v1 < v2.x, v1 < v2.y};
        if constexpr (t_n == 3) return {v1 < v2.x, v1 < v2.y, v1 < v2.z};
        if constexpr (t_n == 4) return {v1 < v2.x, v1 < v2.y, v1 < v2.z, v1 < v2.w};
    }

    //--- greater than ---

    template <Number T, int t_n>
    inline Q_CX_ABLE bvec<t_n> operator>(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
        if constexpr (t_n == 2) return {v1.x > v2.x, v1.y > v2.y};
        if constexpr (t_n == 3) return {v1.x > v2.x, v1.y > v2.y, v1.z > v2.z};
        if constexpr (t_n == 4) return {v1.x > v2.x, v1.y > v2.y, v1.z > v2.z, v1.w > v2.w};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE bvec<t_n> operator>(const vec<T, t_n> & v1, T v2) {
        if constexpr (t_n == 2) return {v1.x > v2, v1.y > v2};
        if constexpr (t_n == 3) return {v1.x > v2, v1.y > v2, v1.z > v2};
        if constexpr (t_n == 4) return {v1.x > v2, v1.y > v2, v1.z > v2, v1.w > v2};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE bvec<t_n> operator>(T v1, const vec<T, t_n> & v2) {
        if constexpr (t_n == 2) return {v1 > v2.x, v1 > v2.y};
        if constexpr (t_n == 3) return {v1 > v2.x, v1 > v2.y, v1 > v2.z};
        if constexpr (t_n == 4) return {v1 > v2.x, v1 > v2.y, v1 > v2.z, v1 > v2.w};
    }

    //--- less than or equal to ---

    template <Number T, int t_n>
    inline Q_CX_ABLE bvec<t_n> operator<=(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
        if constexpr (t_n == 2) return {v1.x <= v2.x, v1.y <= v2.y};
        if constexpr (t_n == 3) return {v1.x <= v2.x, v1.y <= v2.y, v1.z <= v2.z};
        if constexpr (t_n == 4) return {v1.x <= v2.x, v1.y <= v2.y, v1.z <= v2.z, v1.w <= v2.w};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE bvec<t_n> operator<=(const vec<T, t_n> & v1, T v2) {
        if constexpr (t_n == 2) return {v1.x <= v2, v1.y <= v2};
        if constexpr (t_n == 3) return {v1.x <= v2, v1.y <= v2, v1.z <= v2};
        if constexpr (t_n == 4) return {v1.x <= v2, v1.y <= v2, v1.z <= v2, v1.w <= v2};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE bvec<t_n> operator<=(T v1, const vec<T, t_n> & v2) {
        if constexpr (t_n == 2) return {v1 <= v2.x, v1 <= v2.y};
        if constexpr (t_n == 3) return {v1 <= v2.x, v1 <= v2.y, v1 <= v2.z};
        if constexpr (t_n == 4) return {v1 <= v2.x, v1 <= v2.y, v1 <= v2.z, v1 <= v2.w};
    }

    //--- greater than or equal to ---

    template <Number T, int t_n>
    inline Q_CX_ABLE bvec<t_n> operator>=(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
        if constexpr (t_n == 2) return {v1.x >= v2.x, v1.y >= v2.y};
        if constexpr (t_n == 3) return {v1.x >= v2.x, v1.y >= v2.y, v1.z >= v2.z};
        if constexpr (t_n == 4) return {v1.x >= v2.x, v1.y >= v2.y, v1.z >= v2.z, v1.w >= v2.w};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE bvec<t_n> operator>=(const vec<T, t_n> & v1, T v2) {
        if constexpr (t_n == 2) return {v1.x >= v2, v1.y >= v2};
        if constexpr (t_n == 3) return {v1.x >= v2, v1.y >= v2, v1.z >= v2};
        if constexpr (t_n == 4) return {v1.x >= v2, v1.y >= v2, v1.z >= v2, v1.w >= v2};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE bvec<t_n> operator>=(T v1, const vec<T, t_n> & v2) {
        if constexpr (t_n == 2) return {v1 >= v2.x, v1 >= v2.y};
        if constexpr (t_n == 3) return {v1 >= v2.x, v1 >= v2.y, v1 >= v2.z};
        if constexpr (t_n == 4) return {v1 >= v2.x, v1 >= v2.y, v1 >= v2.z, v1 >= v2.w};
    }

    //------------------------------------------------------------------------------
    // Logic Operators

    template <int t_n>
    inline Q_CX_ABLE bvec<t_n> operator&&(const bvec<t_n> & v1, const bvec<t_n> & v2) {
        if constexpr (t_n == 2) return {v1.x && v2.x, v1.y && v2.y};
        if constexpr (t_n == 3) return {v1.x && v2.x, v1.y && v2.y, v1.z && v2.z};
        if constexpr (t_n == 4) return {v1.x && v2.x, v1.y && v2.y, v1.z && v2.z, v1.w && v2.w};
    }

    template <int t_n>
    inline Q_CX_ABLE bvec<t_n> operator||(const bvec<t_n> & v1, const bvec<t_n> & v2) {
        if constexpr (t_n == 2) return {v1.x || v2.x, v1.y || v2.y};
        if constexpr (t_n == 3) return {v1.x || v2.x, v1.y || v2.y, v1.z || v2.z};
        if constexpr (t_n == 4) return {v1.x || v2.x, v1.y || v2.y, v1.z || v2.z, v1.w || v2.w};
    }

    template <int t_n>
    inline Q_CX_ABLE bvec<t_n> operator!(const bvec<t_n> & v) {
        if constexpr (t_n == 2) return {!v.x, !v.y};
        if constexpr (t_n == 3) return {!v.x, !v.y, !v.z};
        if constexpr (t_n == 4) return {!v.x, !v.y, !v.z, !v.w};
    }

    //------------------------------------------------------------------------------
    // Condensation

    template <Number T, int t_n>
    inline Q_CX_ABLE T sum(const vec<T, t_n> & v) {
        if constexpr (t_n == 2) return v.x + v.y;
        if constexpr (t_n == 3) return v.x + v.y + v.z;
        if constexpr (t_n == 4) return v.x + v.y + v.z + v.w;
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE T product(const vec<T, t_n> & v) {
        if constexpr (t_n == 2) return v.x * v.y;
        if constexpr (t_n == 3) return v.x * v.y * v.z;
        if constexpr (t_n == 4) return v.x * v.y * v.z * v.w;
    }

    template <int t_n>
    inline Q_CX_ABLE bool all(const bvec<t_n> & v) {
        if constexpr (t_n == 2) return v.x && v.y;
        if constexpr (t_n == 3) return v.x && v.y && v.z;
        if constexpr (t_n == 4) return v.x && v.y && v.z && v.w;
    }

    template <int t_n>
    inline Q_CX_ABLE bool any(const bvec<t_n> & v) {
        if constexpr (t_n == 2) return v.x || v.y;
        if constexpr (t_n == 3) return v.x || v.y || v.z;
        if constexpr (t_n == 4) return v.x || v.y || v.z || v.w;
    }

    //------------------------------------------------------------------------------
    // Other

    template <Number T, int t_n>
    inline Q_CX_ABLE T min(const vec<T, t_n> & v) {
        if constexpr (t_n == 2) return min(v.x, v.y);
        if constexpr (t_n == 3) return min(v.x, v.y, v.z);
        if constexpr (t_n == 4) return min(v.x, v.y, v.z, v.w);
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> min(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
        if constexpr (t_n == 2) return {min(v1.x, v2.x), min(v1.y, v2.y)};
        if constexpr (t_n == 3) return {min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z)};
        if constexpr (t_n == 4) return {min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z), min(v1.w, v2.w)};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> min(const vec<T, t_n> & v1, T v2) {
        if constexpr (t_n == 2) return {min(v1.x, v2), min(v1.y, v2)};
        if constexpr (t_n == 3) return {min(v1.x, v2), min(v1.y, v2), min(v1.z, v2)};
        if constexpr (t_n == 4) return {min(v1.x, v2), min(v1.y, v2), min(v1.z, v2), min(v1.w, v2)};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> min(T v1, const vec<T, t_n> & v2) {
        return min(v2, v1);
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE T max(const vec<T, t_n> & v) {
        if constexpr (t_n == 2) return max(v.x, v.y);
        if constexpr (t_n == 3) return max(v.x, v.y, v.z);
        if constexpr (t_n == 4) return max(v.x, v.y, v.z, v.w);
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> max(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
        if constexpr (t_n == 2) return {max(v1.x, v2.x), max(v1.y, v2.y)};
        if constexpr (t_n == 3) return {max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z)};
        if constexpr (t_n == 4) return {max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z), max(v1.w, v2.w)};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> max(const vec<T, t_n> & v1, T v2) {
        if constexpr (t_n == 2) return {max(v1.x, v2), max(v1.y, v2)};
        if constexpr (t_n == 3) return {max(v1.x, v2), max(v1.y, v2), max(v1.z, v2)};
        if constexpr (t_n == 4) return {max(v1.x, v2), max(v1.y, v2), max(v1.z, v2), max(v1.w, v2)};
    }

    template <Number T, int t_n>
    inline Q_CX_ABLE vec<T, t_n> max(T v1, const vec<T, t_n> & v2) {
        return max(v2, v1);
    }

    template <Number T, int t_n>
    inline vec<T, t_n> & minify(vec<T, t_n> & min, const vec<T, t_n> & v) {
        if constexpr (t_n >= 1) minify(min.x, v.x);
        if constexpr (t_n >= 2) minify(min.y, v.y);
        if constexpr (t_n >= 3) minify(min.z, v.z);
        if constexpr (t_n >= 4) minify(min.w, v.w);
        return min;
    }

    template <Number T, int t_n>
    inline vec<T, t_n> & minify(vec<T, t_n> & min, T v) {
        if constexpr (t_n >= 1) minify(min.x, v);
        if constexpr (t_n >= 2) minify(min.y, v);
        if constexpr (t_n >= 3) minify(min.z, v);
        if constexpr (t_n >= 4) minify(min.w, v);
        return min;
    }

    template <Number T, int t_n>
    inline vec<T, t_n> & maxify(vec<T, t_n> & max, const vec<T, t_n> & v) {
        if constexpr (t_n >= 1) maxify(max.x, v.x);
        if constexpr (t_n >= 2) maxify(max.y, v.y);
        if constexpr (t_n >= 3) maxify(max.z, v.z);
        if constexpr (t_n >= 4) maxify(max.w, v.w);
        return max;
    }

    template <Number T, int t_n>
    inline vec<T, t_n> & maxify(vec<T, t_n> & max, T v) {
        if constexpr (t_n >= 1) maxify(max.x, v);
        if constexpr (t_n >= 2) maxify(max.y, v);
        if constexpr (t_n >= 3) maxify(max.z, v);
        if constexpr (t_n >= 4) maxify(max.w, v);
        return max;
    }

}
