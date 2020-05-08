#include "QCoreTest.hpp"

#include <sstream>

#include <QCore/QuaternionFunc.hpp>

template <typename T>
static void compileClassesT() {
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

static void compileClasses() {
    compileClassesT< float>();
    compileClassesT<double>();
}

template <typename T>
static constexpr void compileClassesConstexprT() {
    /*constexpr T v(1.0);
    constexpr qc::vec3<T> v3(1.0f);
    constexpr qc::vec4<T> v4(1.0f);
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
    qc::quat<T> q_7(v4);*/
}

static constexpr bool compileClassesConstexpr() {
    compileClassesConstexprT< float>();
    compileClassesConstexprT<double>();

    return true;
}

template <typename T>
static void compileFunctionsT() {
    T v(1.0);
    qc::vec3<T> v3(1.0);
    qc::vec4<T> v4(1.0);
    qc::mat3<T> m3(v3, v3, v3);
    qc::quat<T> q(v4);

    qc::dot(q, q);
    qc::magnitude(q);
    qc::magnitude2(q);
    qc::normalize(q);
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

static void compileFunctions() {
    compileFunctionsT< float>();
    compileFunctionsT<double>();
}

template <typename T>
static constexpr void compileFunctionsConstexprT() {
    /*constexpr T v(1.0);
    constexpr qc::vec3<T> v3(1.0);
    constexpr qc::vec4<T> v4(1.0);
    constexpr qc::mat3<T> m3(v3, v3, v3);
    constexpr qc::quat<T> q(v4);

    //qc::toMat(q);*/
}

static constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT< float>();
    compileFunctionsConstexprT<double>();

    return true;
}

template <typename T>
static void testPropertiesT() {
    static_assert(std::             is_standard_layout_v<qc::quat<T>>);
    static_assert(std::          is_trivially_copyable_v<qc::quat<T>>);
    static_assert(std::is_trivially_copy_constructible_v<qc::quat<T>>);
    static_assert(std::is_trivially_move_constructible_v<qc::quat<T>>);
    static_assert(std::   is_trivially_copy_assignable_v<qc::quat<T>>);
    static_assert(std::   is_trivially_move_assignable_v<qc::quat<T>>);
    static_assert(std::      is_trivially_destructible_v<qc::quat<T>>);
    static_assert(sizeof(qc::quat<T>) == 4 * sizeof(T));
    static_assert(sizeof(qc::quat<T>[4]) == 4 * 4 * sizeof(T));
    static_assert(alignof(qc::quat<T>) == alignof(T));
    static_assert(alignof(qc::quat<T>[4]) == alignof(T));
}

static void testProperties() {
    testPropertiesT< float>();
    testPropertiesT<double>();
}

template <typename T1, typename T2>
static void compileCastsTT() {
    static_cast<qc::quat<T2>>(qc::quat<T1>());
}

template <typename T>
static void compileCastsT() {
    compileCastsTT<T,  float>();
    compileCastsTT<T, double>();
}

static void compileCasts() {
    compileCastsT< float>();
    compileCastsT<double>();
}

void testQuaternion() {
    compileClasses();
    static_assert(compileClassesConstexpr(), "");
    compileFunctions();
    static_assert(compileFunctionsConstexpr(), "");
    testProperties();
    compileCasts();
}
