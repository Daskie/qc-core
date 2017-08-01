#include "QMUTest.hpp"

#include "QMU/Quaternion.hpp"



using namespace qmu;



namespace {



template <typename T>
void compileClassesT() {
    T v(1.0);
    vec3<T> v3(1.0);
    vec4<T> v4(1.0);
    mat3<T> m3(v3, v3, v3);
    quat<T> q(v4);
    std::stringstream os;

    //--------------------------------------------------------------------------
    // Quat

    // constructors
    quat<T> q_1;
    quat<T> q_2(q);
    quat<T> q_3(std::move(q));
    quat<T> q_4(v3, v);
    quat<T> q_6(v3);
    quat<T> q_7(v4);

    // assignment
    q = q;
    q = std::move(q);

    // arithmetic assignment
    q += q;
    q -= q;
    q *= q;
    q *= v;
    q /= q;

    // arithmetic operators
    +q;
    -q;
    q + q;
    q - q;
    q * q;
    q * v;
    v * q;
    q * v3;
    q / q;

    // comparison operators
    q == q;
    q != q;

    // other
    q.toString();
    os << q;
}

void compileClasses() {
    compileClassesT<float>();
    compileClassesT<double>();
    compileClassesT<long double>();
}

template <typename T>
constexpr void compileClassesConstexprT() {
    constexpr T v(1.0);
    constexpr vec3<T> v3(1.0);
    constexpr vec4<T> v4(1.0);
    constexpr mat3<T> m3(v3, v3, v3);
    constexpr quat<T> q(v4);

    //--------------------------------------------------------------------------
    // Quat

    // constructors
    quat<T> q_1;
    quat<T> q_2(q);
    quat<T> q_3(std::move(q));
    quat<T> q_4(v3, v);
    quat<T> q_6(v3);
    quat<T> q_7(v4);
}

constexpr bool compileClassesConstexpr() {
    compileClassesConstexprT<float>();
    compileClassesConstexprT<double>();
    compileClassesConstexprT<long double>();

    return true;
}

template <typename T>
void compileFunctionsT() {
    T v(1.0);
    vec3<T> v3(1.0);
    vec4<T> v4(1.0);
    mat3<T> m3(v3, v3, v3);
    quat<T> q(v4);

    dot(q, q);
    magnitude(q);
    magnitude2(q);
    norm(q);
    inverse(q);
    angle(q);
    axis(q);
    axis_n(q);
    mix(q, q, v);

    rotateQ(v3, v);
    rotateQ_n(v3, v);
    alignQ(v3, v3);
    alignQ_n(v3, v3);
    alignQ(v3, v3, v3, v3);
    alignQ_n(v3, v3, v3, v3);
    eulerQ(v3, v3, v, v, v);
    eulerQ_n(v3, v3, v, v, v);
    toMat(q);
    nlerp(q, q, v);
    slerp(q, q, v);
}

void compileFunctions() {
    compileFunctionsT<float>();
    compileFunctionsT<double>();
    compileFunctionsT<long double>();
}

template <typename T>
constexpr void compileFunctionsConstexprT() {
    constexpr T v(1.0);
    constexpr vec3<T> v3(1.0);
    constexpr vec4<T> v4(1.0);
    constexpr mat3<T> m3(v3, v3, v3);
    constexpr quat<T> q(v4);

    toMat(q);
}

constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT<      float>();
    compileFunctionsConstexprT<     double>();
    compileFunctionsConstexprT<long double>();

    return true;
}

template <typename T>
void testPropertiesT() {
    static_assert(std::is_standard_layout<quat<T>>::value, "");
    static_assert(sizeof(quat<T>) == 4 * sizeof(T), "");
}

void testProperties() {
    testPropertiesT<float>();
    testPropertiesT<double>();
    testPropertiesT<long double>();
}

template <typename T1, typename T2>
void compileCastsTT() {
    static_cast<mat2<T2>>(mat2<T1>());
    static_cast<mat3<T2>>(mat3<T1>());
    static_cast<mat4<T2>>(mat4<T1>());
}

template <typename T>
void compileCastsT() {
    compileCastsTT<T, float>();
    compileCastsTT<T, double>();
    compileCastsTT<T, long double>();
}

void compileCasts() {
    compileCastsT<float>();
    compileCastsT<double>();
    compileCastsT<long double>();
}



}



void testQuaternion() {
    compileClasses();
    static_assert(compileClassesConstexpr(), "");
    compileFunctions();
    static_assert(compileFunctionsConstexpr(), "");
    testProperties();
    compileCasts();
}