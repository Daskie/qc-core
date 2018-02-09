#include "QCUTest.hpp"

#include <sstream>

#include "QCU/QuaternionFunc.hpp"



namespace {



template <typename T>
void compileClassesT() {
    T v(1.0);
    qcu::vec3<T> v3(1.0);
    qcu::vec4<T> v4(1.0);
    qcu::mat3<T> m3(v3, v3, v3);
    qcu::quat<T> q(v4);
    std::stringstream os;

    //--------------------------------------------------------------------------
    // Quat

    // constructors
    qcu::quat<T> q_1;
    qcu::quat<T> q_2(q);
    qcu::quat<T> q_3(std::move(q));
    qcu::quat<T> q_4(v3, v);
    qcu::quat<T> q_6(v3);
    qcu::quat<T> q_7(v4);

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
    constexpr qcu::vec3<T> v3(1.0);
    constexpr qcu::vec4<T> v4(1.0);
    constexpr qcu::mat3<T> m3(v3, v3, v3);
    constexpr qcu::quat<T> q(v4);

    //--------------------------------------------------------------------------
    // Quat

    // constructors
    qcu::quat<T> q_1;
    qcu::quat<T> q_2(q);
    qcu::quat<T> q_3(std::move(q));
    qcu::quat<T> q_4(v3, v);
    qcu::quat<T> q_6(v3);
    qcu::quat<T> q_7(v4);
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
    qcu::vec3<T> v3(1.0);
    qcu::vec4<T> v4(1.0);
    qcu::mat3<T> m3(v3, v3, v3);
    qcu::quat<T> q(v4);

    qcu::dot(q, q);
    qcu::magnitude(q);
    qcu::magnitude2(q);
    qcu::norm(q);
    qcu::inverse(q);
    qcu::quatAngle(q);
    qcu::quatAxis(q);
    qcu::quatAxis_n(q);
    qcu::mix(q, q, v);

    qcu::rotateQ(v3, v);
    qcu::rotateQ_n(v3, v);
    qcu::alignQ(v3, v3);
    qcu::alignQ_n(v3, v3);
    qcu::alignQ(v3, v3, v3, v3);
    qcu::alignQ_n(v3, v3, v3, v3);
    qcu::eulerQ(v3, v3, v, v, v);
    qcu::eulerQ_n(v3, v3, v, v, v);
    qcu::toMat(q);
    qcu::nlerp(q, q, v);
    qcu::slerp(q, q, v);
}

void compileFunctions() {
    compileFunctionsT<float>();
    compileFunctionsT<double>();
    compileFunctionsT<long double>();
}

template <typename T>
constexpr void compileFunctionsConstexprT() {
    constexpr T v(1.0);
    constexpr qcu::vec3<T> v3(1.0);
    constexpr qcu::vec4<T> v4(1.0);
    constexpr qcu::mat3<T> m3(v3, v3, v3);
    constexpr qcu::quat<T> q(v4);

    //qcu::toMat(q);
}

constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT<      float>();
    compileFunctionsConstexprT<     double>();
    compileFunctionsConstexprT<long double>();

    return true;
}

template <typename T>
void testPropertiesT() {
    static_assert(std::is_standard_layout_v<qcu::quat<T>>, "");
    static_assert(sizeof(qcu::quat<T>) == 4 * sizeof(T), "");
    static_assert(sizeof(qcu::quat<T>[4]) == 4 * 4 * sizeof(T));
    static_assert(alignof(qcu::quat<T>) == alignof(T));
    static_assert(alignof(qcu::quat<T>[4]) == alignof(T));
}

void testProperties() {
    testPropertiesT<float>();
    testPropertiesT<double>();
    testPropertiesT<long double>();
}

template <typename T1, typename T2>
void compileCastsTT() {
    static_cast<qcu::quat<T2>>(qcu::quat<T1>());
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