#include "QCoreTest.hpp"

#include <sstream>

#include "QCore/QuaternionFunc.hpp"



namespace {



template <typename T>
void compileClassesT() {
    T v(1.0);
    qc::vec3<T> v3(1.0);
    qc::vec4<T> v4(1.0);
    qc::mat3<T> m3(v3, v3, v3);
    qc::quat<T> q(v4);
    std::stringstream os;

    //--------------------------------------------------------------------------
    // Quat

    // constructors
    qc::quat<T> q_1;
    qc::quat<T> q_2(q);
    qc::quat<T> q_3(std::move(q));
    qc::quat<T> q_4(v3, v);
    qc::quat<T> q_6(v3);
    qc::quat<T> q_7(v4);

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
    constexpr qc::vec3<T> v3(1.0);
    constexpr qc::vec4<T> v4(1.0);
    constexpr qc::mat3<T> m3(v3, v3, v3);
    constexpr qc::quat<T> q(v4);

    //--------------------------------------------------------------------------
    // Quat

    // constructors
    qc::quat<T> q_1;
    qc::quat<T> q_2(q);
    qc::quat<T> q_3(std::move(q));
    qc::quat<T> q_4(v3, v);
    qc::quat<T> q_6(v3);
    qc::quat<T> q_7(v4);
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
    qc::vec3<T> v3(1.0);
    qc::vec4<T> v4(1.0);
    qc::mat3<T> m3(v3, v3, v3);
    qc::quat<T> q(v4);

    qc::dot(q, q);
    qc::magnitude(q);
    qc::magnitude2(q);
    qc::norm(q);
    qc::inverse(q);
    qc::quatAngle(q);
    qc::quatAxis(q);
    qc::quatAxis_n(q);
    qc::mix(q, q, v);

    qc::rotateQ(v3, v);
    qc::rotateQ_n(v3, v);
    qc::alignQ(v3, v3);
    qc::alignQ_n(v3, v3);
    qc::alignQ(v3, v3, v3, v3);
    qc::alignQ_n(v3, v3, v3, v3);
    qc::eulerQ(v3, v3, v, v, v);
    qc::eulerQ_n(v3, v3, v, v, v);
    qc::toMat(q);
    qc::nlerp(q, q, v);
    qc::slerp(q, q, v);
}

void compileFunctions() {
    compileFunctionsT<float>();
    compileFunctionsT<double>();
    compileFunctionsT<long double>();
}

template <typename T>
constexpr void compileFunctionsConstexprT() {
    constexpr T v(1.0);
    constexpr qc::vec3<T> v3(1.0);
    constexpr qc::vec4<T> v4(1.0);
    constexpr qc::mat3<T> m3(v3, v3, v3);
    constexpr qc::quat<T> q(v4);

    //qc::toMat(q);
}

constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT<      float>();
    compileFunctionsConstexprT<     double>();
    compileFunctionsConstexprT<long double>();

    return true;
}

template <typename T>
void testPropertiesT() {
    static_assert(std::is_standard_layout_v<qc::quat<T>>, "");
    static_assert(sizeof(qc::quat<T>) == 4 * sizeof(T), "");
    static_assert(sizeof(qc::quat<T>[4]) == 4 * 4 * sizeof(T));
    static_assert(alignof(qc::quat<T>) == alignof(T));
    static_assert(alignof(qc::quat<T>[4]) == alignof(T));
}

void testProperties() {
    testPropertiesT<float>();
    testPropertiesT<double>();
    testPropertiesT<long double>();
}

template <typename T1, typename T2>
void compileCastsTT() {
    static_cast<qc::quat<T2>>(qc::quat<T1>());
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