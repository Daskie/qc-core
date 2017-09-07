#include "QMUTest.hpp"

#include "QMU/Quaternion.hpp"



namespace {



template <typename T>
void compileClassesT() {
    T v(1.0);
    qmu::vec3<T> v3(1.0);
    qmu::vec4<T> v4(1.0);
    qmu::mat3<T> m3(v3, v3, v3);
    qmu::quat<T> q(v4);
    std::stringstream os;

    //--------------------------------------------------------------------------
    // Quat

    // constructors
    qmu::quat<T> q_1;
    qmu::quat<T> q_2(q);
    qmu::quat<T> q_3(std::move(q));
    qmu::quat<T> q_4(v3, v);
    qmu::quat<T> q_6(v3);
    qmu::quat<T> q_7(v4);

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
    constexpr qmu::vec3<T> v3(1.0);
    constexpr qmu::vec4<T> v4(1.0);
    constexpr qmu::mat3<T> m3(v3, v3, v3);
    constexpr qmu::quat<T> q(v4);

    //--------------------------------------------------------------------------
    // Quat

    // constructors
    qmu::quat<T> q_1;
    qmu::quat<T> q_2(q);
    qmu::quat<T> q_3(std::move(q));
    qmu::quat<T> q_4(v3, v);
    qmu::quat<T> q_6(v3);
    qmu::quat<T> q_7(v4);
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
    qmu::vec3<T> v3(1.0);
    qmu::vec4<T> v4(1.0);
    qmu::mat3<T> m3(v3, v3, v3);
    qmu::quat<T> q(v4);

    qmu::dot(q, q);
    qmu::magnitude(q);
    qmu::magnitude2(q);
    qmu::norm(q);
    qmu::inverse(q);
    qmu::quatAngle(q);
    qmu::quatAxis(q);
    qmu::quatAxis_n(q);
    qmu::mix(q, q, v);

    qmu::rotateQ(v3, v);
    qmu::rotateQ_n(v3, v);
    qmu::alignQ(v3, v3);
    qmu::alignQ_n(v3, v3);
    qmu::alignQ(v3, v3, v3, v3);
    qmu::alignQ_n(v3, v3, v3, v3);
    qmu::eulerQ(v3, v3, v, v, v);
    qmu::eulerQ_n(v3, v3, v, v, v);
    qmu::toMat(q);
    qmu::nlerp(q, q, v);
    qmu::slerp(q, q, v);
}

void compileFunctions() {
    compileFunctionsT<float>();
    compileFunctionsT<double>();
    compileFunctionsT<long double>();
}

template <typename T>
constexpr void compileFunctionsConstexprT() {
    constexpr T v(1.0);
    constexpr qmu::vec3<T> v3(1.0);
    constexpr qmu::vec4<T> v4(1.0);
    constexpr qmu::mat3<T> m3(v3, v3, v3);
    constexpr qmu::quat<T> q(v4);

    qmu::toMat(q);
}

constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT<      float>();
    compileFunctionsConstexprT<     double>();
    compileFunctionsConstexprT<long double>();

    return true;
}

template <typename T>
void testPropertiesT() {
    static_assert(std::is_standard_layout_v<qmu::quat<T>>, "");
    static_assert(sizeof(qmu::quat<T>) == 4 * sizeof(T), "");
}

void testProperties() {
    testPropertiesT<float>();
    testPropertiesT<double>();
    testPropertiesT<long double>();
}

template <typename T1, typename T2>
void compileCastsTT() {
    static_cast<qmu::quat<T2>>(qmu::quat<T1>());
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