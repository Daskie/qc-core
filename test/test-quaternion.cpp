#include <qc-core/quaternion-ext.hpp>

#include <sstream>

#include <gtest/gtest.h>

using namespace qc::types;
using namespace qc::primitives;

template <typename T>
static void compileClassesT()
{
    T v{1.0};
    vec3<T> v3{1.0};
    vec4<T> v4{1.0};
    mat3<T> m3{v3, v3, v3};
    quat<T> q{v4};
    std::stringstream os{};

    //--------------------------------------------------------------------------
    // Quat

    // constructors
    quat<T> q_1{};
    quat<T> q_2{q};
    quat<T> q_3{std::move(q)};
    quat<T> q_4{v3, v};
    quat<T> q_6{v3};
    quat<T> q_7{v4};

    // assignment
    q = q;
    q = std::move(q);

    // conversion
    static_cast<void>(static_cast<bool>(q));

    // arithmetic assignment
    q += q;
    q -= q;
    q *= q;
    q *= v;
    v3 *= q;

    // arithmetic operators
    static_cast<void>(+q);
    static_cast<void>(-q);
    static_cast<void>(q + q);
    static_cast<void>(q - q);
    static_cast<void>(q * q);
    static_cast<void>(q * v);
    static_cast<void>(v * q);
    static_cast<void>(q * v3);

    // comparison operators
    static_cast<void>(q == q);

    // other
    os << q;
}

static void compileClasses()
{
    compileClassesT<float>();
    compileClassesT<double>();
}

template <typename T>
static void compileFunctionsT()
{
    T v{1.0};
    vec3<T> v3{1.0};
    vec4<T> v4{1.0};
    mat3<T> m3{v3, v3, v3};
    quat<T> q{v4};

    static_cast<void>(qc::dot(q, q));
    static_cast<void>(qc::magnitude(q));
    static_cast<void>(qc::magnitude2(q));
    static_cast<void>(qc::normalize(q));
    static_cast<void>(qc::inverse(q));
    static_cast<void>(qc::quatAngle(q));
    static_cast<void>(qc::quatAxis(q));
    static_cast<void>(qc::quatAxis_n(q));
    static_cast<void>(qc::mix(q, q, v));

    static_cast<void>(qc::rotateQ(v3, v));
    static_cast<void>(qc::rotateQ_n(v3, v));
    static_cast<void>(qc::alignQ(v3, v3));
    static_cast<void>(qc::alignQ_n(v3, v3));
    static_cast<void>(qc::alignQ(v3, v3, v3, v3));
    static_cast<void>(qc::alignQ_n(v3, v3, v3, v3));
    static_cast<void>(qc::eulerQ(v3, v3, v, v, v));
    static_cast<void>(qc::eulerQ_n(v3, v3, v, v, v));
    static_cast<void>(qc::toMat(q));
    static_cast<void>(qc::nlerp(q, q, v));
    static_cast<void>(qc::slerp(q, q, v));
}

static void compileFunctionsNonMatching()
{
    float _f{};
    fvec3 _fvec{};
    dvec3 _dvec{};
    fquat _fquat{};
    dquat _dquat{};

    _dquat += _fquat;
    _dquat -= _fquat;
    _dquat *= _fquat;
    _dquat *= _f;
    _dvec *= _fquat;

    static_cast<void>(_dquat + _fquat);
    static_cast<void>(_fquat + _dquat);
    static_cast<void>(_dquat - _fquat);
    static_cast<void>(_fquat - _dquat);
    static_cast<void>(_dquat * _fquat);
    static_cast<void>(_fquat * _dquat);
    static_cast<void>(_dquat * _f);
    static_cast<void>(_f * _dquat);
    static_cast<void>(_dquat * _fvec);
}

static void compileFunctions()
{
    compileFunctionsT<float>();
    compileFunctionsT<double>();
    compileFunctionsNonMatching();
}

template <typename T>
static void testPropertiesT()
{
    static_assert(std::is_standard_layout_v<quat<T>>);
    static_assert(std::is_trivially_copyable_v<quat<T>>);
    static_assert(std::is_trivially_copy_constructible_v<quat<T>>);
    static_assert(std::is_trivially_move_constructible_v<quat<T>>);
    static_assert(std::is_trivially_copy_assignable_v<quat<T>>);
    static_assert(std::is_trivially_move_assignable_v<quat<T>>);
    static_assert(std::is_trivially_destructible_v<quat<T>>);
    static_assert(sizeof(quat<T>) == 4u * sizeof(T));
    static_assert(sizeof(quat<T>[4]) == 4u * 4u * sizeof(T));
    static_assert(alignof(quat<T>) == alignof(T));
    static_assert(alignof(quat<T>[4]) == alignof(T));
}

static void testProperties()
{
    testPropertiesT<float>();
    testPropertiesT<double>();
}

template <typename T1, typename T2>
static void compileCastsTT()
{
    static_cast<void>(static_cast<quat<T2>>(quat<T1>{}));
}

template <typename T>
static void compileCastsT()
{
    compileCastsTT<T, float>();
    compileCastsTT<T, double>();
}

static void compileCasts()
{
    compileCastsT<float>();
    compileCastsT<double>();
}

TEST(Quaternion, compilation)
{
    compileClasses();
    compileFunctions();
    testProperties();
    compileCasts();
}

TEST(Quaternion, types)
{
    static_assert(Quaternion<fquat>);
    static_assert(Quaternion<dquat>);
    static_assert(!Quaternion<int>);
}
