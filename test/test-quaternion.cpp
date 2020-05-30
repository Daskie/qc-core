#include <sstream>

#include <qc-core/quaternion-ext.hpp>

template <typename T>
static void compileClassesT() {
    T v(1.0);
    qc::core::vec3<T> v3(1.0);
    qc::core::vec4<T> v4(1.0);
    qc::core::mat3<T> m3(v3, v3, v3);
    qc::core::quat<T> q(v4);
    std::stringstream os;

    //--------------------------------------------------------------------------
    // Quat

    // constructors
    qc::core::quat<T> q_1;
    qc::core::quat<T> q_2(q);
    qc::core::quat<T> q_3(std::move(q));
    qc::core::quat<T> q_4(v3, v);
    qc::core::quat<T> q_6(v3);
    qc::core::quat<T> q_7(v4);

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
    constexpr qc::core::vec3<T> v3(1.0f);
    constexpr qc::core::vec4<T> v4(1.0f);
    constexpr qc::core::mat3<T> m3(v3, v3, v3);
    constexpr qc::core::quat<T> q(v4);

    //--------------------------------------------------------------------------
    // Quat

    // constructors
    qc::core::quat<T> q_1;
    qc::core::quat<T> q_2(q);
    qc::core::quat<T> q_3(std::move(q));
    qc::core::quat<T> q_4(v3, v);
    qc::core::quat<T> q_6(v3);
    qc::core::quat<T> q_7(v4);*/
}

static constexpr bool compileClassesConstexpr() {
    compileClassesConstexprT< float>();
    compileClassesConstexprT<double>();

    return true;
}

template <typename T>
static void compileFunctionsT() {
    T v(1.0);
    qc::core::vec3<T> v3(1.0);
    qc::core::vec4<T> v4(1.0);
    qc::core::mat3<T> m3(v3, v3, v3);
    qc::core::quat<T> q(v4);

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
    /*constexpr T v(1.0);
    constexpr qc::core::vec3<T> v3(1.0);
    constexpr qc::core::vec4<T> v4(1.0);
    constexpr qc::core::mat3<T> m3(v3, v3, v3);
    constexpr qc::core::quat<T> q(v4);

    //qc::core::toMat(q);*/
}

static constexpr bool compileFunctionsConstexpr() {
    compileFunctionsConstexprT< float>();
    compileFunctionsConstexprT<double>();

    return true;
}

template <typename T>
static void testPropertiesT() {
    static_assert(std::             is_standard_layout_v<qc::core::quat<T>>);
    static_assert(std::          is_trivially_copyable_v<qc::core::quat<T>>);
    static_assert(std::is_trivially_copy_constructible_v<qc::core::quat<T>>);
    static_assert(std::is_trivially_move_constructible_v<qc::core::quat<T>>);
    static_assert(std::   is_trivially_copy_assignable_v<qc::core::quat<T>>);
    static_assert(std::   is_trivially_move_assignable_v<qc::core::quat<T>>);
    static_assert(std::      is_trivially_destructible_v<qc::core::quat<T>>);
    static_assert(sizeof(qc::core::quat<T>) == 4 * sizeof(T));
    static_assert(sizeof(qc::core::quat<T>[4]) == 4 * 4 * sizeof(T));
    static_assert(alignof(qc::core::quat<T>) == alignof(T));
    static_assert(alignof(qc::core::quat<T>[4]) == alignof(T));
}

static void testProperties() {
    testPropertiesT< float>();
    testPropertiesT<double>();
}

template <typename T1, typename T2>
static void compileCastsTT() {
    static_cast<qc::core::quat<T2>>(qc::core::quat<T1>());
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
