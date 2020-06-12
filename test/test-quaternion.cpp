#include <sstream>

#include <CppUnitTest.h>

#include <qc-core/quaternion-ext.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace qc::core::types;

template <typename T>
static void compileClassesT() {
    T v{1.0};
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

    // conversion
    static_cast<bool>(q);

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
    /*constexpr T v{1.0};
    constexpr vec3<T> v3(1.0f);
    constexpr vec4<T> v4(1.0f);
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
    quat<T> q_7(v4);*/
}

static constexpr bool compileClassesConstexpr() {
    compileClassesConstexprT< float>();
    compileClassesConstexprT<double>();

    return true;
}

template <typename T>
static void compileFunctionsT() {
    T v{1.0};
    vec3<T> v3(1.0);
    vec4<T> v4(1.0);
    mat3<T> m3(v3, v3, v3);
    quat<T> q(v4);

    qc::core::dot(q, q);
    qc::core::magnitude(q);
    qc::core::magnitude2(q);
    qc::core::normalize(q);
    qc::core::inverse(q);
    qc::core::quatAngle(q);
    qc::core::quatAxis(q);
    qc::core::quatAxis_n(q);
    qc::core::mix(q, q, v);

    qc::core::rotateQ(v3, v);
    qc::core::rotateQ_n(v3, v);
    qc::core::alignQ(v3, v3);
    qc::core::alignQ_n(v3, v3);
    qc::core::alignQ(v3, v3, v3, v3);
    qc::core::alignQ_n(v3, v3, v3, v3);
    qc::core::eulerQ(v3, v3, v, v, v);
    qc::core::eulerQ_n(v3, v3, v, v, v);
    qc::core::toMat(q);
    qc::core::nlerp(q, q, v);
    qc::core::slerp(q, q, v);
}

static void compileFunctions() {
    compileFunctionsT< float>();
    compileFunctionsT<double>();
}

template <typename T>
static constexpr void compileFunctionsConstexprT() {
    /*constexpr T v{1.0};
    constexpr vec3<T> v3(1.0);
    constexpr vec4<T> v4(1.0);
    constexpr mat3<T> m3(v3, v3, v3);
    constexpr quat<T> q(v4);

    //toMat(q);*/
}

static constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT< float>();
    compileFunctionsConstexprT<double>();

    return true;
}

template <typename T>
static void testPropertiesT() {
    static_assert(std::             is_standard_layout_v<quat<T>>);
    static_assert(std::          is_trivially_copyable_v<quat<T>>);
    static_assert(std::is_trivially_copy_constructible_v<quat<T>>);
    static_assert(std::is_trivially_move_constructible_v<quat<T>>);
    static_assert(std::   is_trivially_copy_assignable_v<quat<T>>);
    static_assert(std::   is_trivially_move_assignable_v<quat<T>>);
    static_assert(std::      is_trivially_destructible_v<quat<T>>);
    static_assert(sizeof(quat<T>) == 4u * sizeof(T));
    static_assert(sizeof(quat<T>[4]) == 4u * 4u * sizeof(T));
    static_assert(alignof(quat<T>) == alignof(T));
    static_assert(alignof(quat<T>[4]) == alignof(T));
}

static void testProperties() {
    testPropertiesT< float>();
    testPropertiesT<double>();
}

template <typename T1, typename T2>
static void compileCastsTT() {
    static_cast<quat<T2>>(quat<T1>());
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

TEST_CLASS(TestQuaternion) {

    public:

    TEST_METHOD(testCompilation) {
        compileClasses();
        static_assert(compileClassesConstexpr(), "");
        compileFunctions();
        static_assert(compileFunctionsConstexpr(), "");
        testProperties();
        compileCasts();
    }

    TEST_METHOD(testConcepts) {
        static_assert(Quaternion<fquat>);
        static_assert(Quaternion<dquat>);
        static_assert(!Quaternion<int>);
    }

};
