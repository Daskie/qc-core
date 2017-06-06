#include "QMUTest.hpp"

#include "QMU/Quaternion.hpp"



using namespace qmu;



namespace {



template <typename T>
void testQuaternionTCompilation() {
    T v;
    vec3<T> v3;
    vec4<T> v4;
    mat3<T> m3;
    quat<T> q;
    std::stringstream os;

    //--------------------------------------------------------------------------
    // Quat

    // constructors
    quat<T> q_1;
    quat<T> q_2(q);
    quat<T> q_3(std::move(q));
    quat<T> q_4(v3, v);
    quat<T> q_5(v, v, v, v);
    quat<T> q_6(v3);
    quat<T> q_7(v4);

    // assignment operators
    q = q;
    q = std::move(q);

    // access operators
    q[0];

    // arithmetic assignment operators
    q += q;
    q -= q;
    q *= q;
    q *= v;
    q /= quat<T>(1, 1, 1, 1);

    // arithmetic operators
    +q;
    -q;
    q + q;
    q - q;
    q * q;
    q * v;
    v * q;
    q * v3;
    q / quat<T>(1, 1, 1, 1);

    // comparison operators
    q == q;
    q != q;

    // other
    q.toString();
    os << q;

    //--------------------------------------------------------------------------
    // Quat Functions

    q = quat<T>(1, 1, 1, 1);

    magnitude(q);
    normalize(q);
    inverse(q);
    angle(q);
    axis(q);
    axis_n(q);

    //--------------------------------------------------------------------------
    // Transformations

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

template <typename T>
void testQuaternionTProperties() {
    static_assert(std::is_standard_layout<quat<T>>::value, "");
    static_assert(sizeof(quat<T>) == 4 * sizeof(T), "");
}

void testQuaternionCompilation() {
    testQuaternionTCompilation<float>();
    testQuaternionTCompilation<double>();

    testQuaternionTProperties<float>();
    testQuaternionTProperties<double>();
}

template <typename T1, typename T2>
void testQuaternionTTCasts() {
    static_cast<mat2<T2>>(mat2<T1>());
    static_cast<mat3<T2>>(mat3<T1>());
    static_cast<mat4<T2>>(mat4<T1>());
}

template <typename T>
void testQuaternionTCasts() {
    testQuaternionTTCasts<T,  float>();
    testQuaternionTTCasts<T, double>();
}

void testQuaternionCasts() {
    testQuaternionTCasts< float>();
    testQuaternionTCasts<double>();
}



}



void testQuaternion() {
    testQuaternionCompilation();
    testQuaternionCasts();
}