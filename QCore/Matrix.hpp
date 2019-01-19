#pragma once



// Column-major ordering
//
//  x1 x2 x3    00 03 06
//  y1 y2 y3    01 04 07
//  z1 z2 z3    02 05 08



#include "Vector.hpp"



namespace qc {



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Types ---------------------------------------------------------------------------------------------------------------



template <typename T, int t_n> struct mat;

namespace types {

    using qc::mat;

    template <typename T> using mat2 = mat<T, 2>;
    template <typename T> using mat3 = mat<T, 3>;
    template <typename T> using mat4 = mat<T, 4>;

    template <int t_n> using fmat = mat< float, t_n>;
    template <int t_n> using dmat = mat<double, t_n>;

    using fmat2 = mat< float, 2>;
    using fmat3 = mat< float, 3>;
    using fmat4 = mat< float, 4>;
    using dmat2 = mat<double, 2>;
    using dmat3 = mat<double, 3>;
    using dmat4 = mat<double, 4>;

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT2 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct mat<T, 2> {

    static_assert(std::is_floating_point_v<T>, "mat2<T> must have floating point T");

    using type = T;
    static constexpr int dimension{2};

    vec2<T> c1, c2;

    //--- constructors ---

    constexpr mat();
    constexpr mat(const mat2<T> & m);
    constexpr mat(mat2<T> && m);

    constexpr mat(
        const vec2<T> & c1,
        const vec2<T> & c2
    );
    constexpr mat(
        T x1, T y1,
        T x2, T y2
    );

    template <typename U> constexpr explicit mat(const mat2<U> & m);
    template <typename U> constexpr explicit mat(const mat3<U> & m);
    template <typename U> constexpr explicit mat(const mat4<U> & m);

    //--- assignment ---

    mat2<T> & operator=(const mat2<T> & m);
    mat2<T> & operator=(mat2<T> && m);

    template <typename U, int t_n> mat2<T> & operator=(const mat<U, t_n> & m);

    //--- access ---
    
    vec2<T> & col(int i);
    const vec2<T> & col(int i) const;

    vec2<T> row(int i) const;

    template <int t_i> constexpr vec2<T> row() const;

    template <int t_i> constexpr const vec2<T> & col() const;

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT3 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct mat<T, 3> {

    static_assert(std::is_floating_point_v<T>, "mat3<T> must have floating point T");

    using type = T;
    static constexpr int dimension{3};

    vec3<T> c1, c2, c3;

    //--- constructors ---

    constexpr mat();
    constexpr mat(const mat3<T> & m);
    constexpr mat(mat3<T> && m);

    constexpr mat(
        const vec3<T> & c1,
        const vec3<T> & c2,
        const vec3<T> & c3
    );
    constexpr mat(
        T x1, T y1, T z1,
        T x2, T y2, T z2,
        T x3, T y3, T z3
    );

    template <typename U> constexpr explicit mat(const mat2<U> & m);
    template <typename U> constexpr explicit mat(const mat3<U> & m);
    template <typename U> constexpr explicit mat(const mat4<U> & m);

    //--- assignment ---

    mat3<T> & operator=(const mat3<T> & m);
    mat3<T> & operator=(mat3<T> && m);
    
    template <typename U, int t_n> mat3<T> & operator=(const mat<U, t_n> & m);

    //--- access ---

    vec3<T> & col(int i);
    const vec3<T> & col(int i) const;

    vec3<T> row(int i) const;

    template <int t_i> constexpr vec3<T> row() const;

    template <int t_i> constexpr const vec3<T> & col() const;

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT4 ----------------------------------------------------------------------------------------------------------------



template <typename T>
struct mat<T, 4> {

    static_assert(std::is_floating_point_v<T>, "mat4<T> must have floating point T");

    using type = T;
    static constexpr int dimension{4};

    vec4<T> c1, c2, c3, c4;

    //--- constructors ---

    constexpr mat();
    constexpr mat(const mat4<T> & m);
    constexpr mat(mat4<T> && m);

    constexpr mat(
        const vec4<T> & c1,
        const vec4<T> & c2,
        const vec4<T> & c3,
        const vec4<T> & c4
    );
    constexpr mat(
        T x1, T y1, T z1, T w1,
        T x2, T y2, T z2, T w2,
        T x3, T y3, T z3, T w3,
        T x4, T y4, T z4, T w4
    );

    template <typename U> constexpr explicit mat(const mat2<U> & m);
    template <typename U> constexpr explicit mat(const mat3<U> & m);
    template <typename U> constexpr explicit mat(const mat4<U> & m);

    //--- assignment ---

    mat4<T> & operator=(const mat4<T> & m);
    mat4<T> & operator=(mat4<T> && m);
    
    template <typename U, int t_n> mat4<T> & operator=(const mat<U, t_n> & m);

    //--- access ---
    
    vec4<T> & col(int i);
    const vec4<T> & col(int i) const;

    vec4<T> row(int i) const;

    template <int t_i> constexpr vec4<T> row() const;

    template <int t_i> constexpr const vec4<T> & col() const;

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT FUNCTIONS -------------------------------------------------------------------------------------------------------



//--- arithmetic assignment ---

template <typename T, int t_n> mat<T, t_n> & operator+=(mat<T, t_n> & m, T v);
template <typename T, int t_n> mat<T, t_n> & operator+=(mat<T, t_n> & m1, const mat<T, t_n> & m2);

template <typename T, int t_n> mat<T, t_n> & operator-=(mat<T, t_n> & m, T v);
template <typename T, int t_n> mat<T, t_n> & operator-=(mat<T, t_n> & m1, const mat<T, t_n> & m2);

template <typename T, int t_n> mat<T, t_n> & operator*=(mat<T, t_n> & m, T v);
template <typename T, int t_n> mat<T, t_n> & operator*=(mat<T, t_n> & m1, const mat<T, t_n> & m2);

template <typename T, int t_n> mat<T, t_n> & operator/=(mat<T, t_n> & m, T v);

//--- arithmetic operators ---

template <typename T, int t_n> mat<T, t_n> operator+(const mat<T, t_n> & m);

template <typename T, int t_n> mat<T, t_n> operator-(const mat<T, t_n> & m);

template <typename T, int t_n> mat<T, t_n> operator+(const mat<T, t_n> & m1, const mat<T, t_n> & m2);
template <typename T, int t_n> mat<T, t_n> operator+(const mat<T, t_n> & m, T v);
template <typename T, int t_n> mat<T, t_n> operator+(T v, const mat<T, t_n> & m);

template <typename T, int t_n> mat<T, t_n> operator-(const mat<T, t_n> & m1, const mat<T, t_n> & m2);
template <typename T, int t_n> mat<T, t_n> operator-(const mat<T, t_n> & m, T v);
template <typename T, int t_n> mat<T, t_n> operator-(T v, const mat<T, t_n> & m);

template <typename T, int t_n, int t_o> mat<T, t_o> operator*(const mat<T, t_n> & m1, const mat<T, t_n> & m2);
template <typename T, int t_n> mat<T, t_n> operator*(const mat<T, t_n> & m, T v);
template <typename T, int t_n> mat<T, t_n> operator*(T v, const mat<T, t_n> & m);
template <typename T, int t_n> vec<T, t_n> operator*(const mat<T, t_n> & m, const vec<T, t_n> & v);

template <typename T, int t_n> mat<T, t_n> operator/(const mat<T, t_n> & m, T v);
template <typename T, int t_n> mat<T, t_n> operator/(T v, const mat<T, t_n> & m);

//--- comparison operators ---

template <typename T, int t_n> bool operator==(const mat<T, t_n> & m1, const mat<T, t_n> & m2);

template <typename T, int t_n> bool operator!=(const mat<T, t_n> & m1, const mat<T, t_n> & m2);

//--- constants ---

template <typename T, int t_n> constexpr mat<T, t_n> fullMat(T v);

template <typename T, int t_n> constexpr mat<T, t_n> nullMat();



}



#include "Matrix.tpp"