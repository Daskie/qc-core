#pragma once



#include <cmath>

#include "Matrix.hpp"



namespace qcu {



template <typename T, eif_floating_t<T> = 0>
inline vec2<T> polarToCartesian(const vec2<T> & v) {
    return vec2<T>(
        v.rad * std::cos(v.theta),
        v.rad * std::sin(v.theta)
    );
}

template <typename T, eif_floating_t<T> = 0>
inline vec2<T> cartesianToPolar(const vec2<T> & v) {
    return vec2<T>(
        magnitude(v),
        std::atan2(v.y, v.x)
    );
}

//r is radius, theta is angle on xy plane, phi is angle from z axis
template <typename T, eif_floating_t<T> = 0>
inline vec3<T> sphericalToCartesian(const vec3<T> & v) {
    T sinTheta = std::sin(v.theta);
    T cosTheta = std::cos(v.theta);
    T sinPhi = std::sin(v.phi);
    T cosPhi = std::cos(v.phi);

    return vec3<T>(
        v.rad * sinPhi * cosTheta,
        v.rad * sinPhi * sinTheta,
        v.rad * cosPhi
    );
}

template <typename T, eif_floating_t<T> = 0>
inline vec3<T> cartesianToSpherical(const vec3<T> & v) {
    T rad(magnitude(v));
    return vec3<T>(
        rad,
        std::atan2(v.y, v.x),
        std::acos(v.z / rad)
    );
}

template <typename T, eif_floating_t<T> = 0>
inline vec3<T> cylindricToCartesian(const vec3<T> & v) {
    return vec3<T>(
        v.rad * std::cos(v.theta),
        v.rad * std::sin(v.theta),
        v.z
    );
}

template <typename T, eif_floating_t<T> = 0>
inline vec3<T> cartesianToCylindric(const vec3<T> & v) {
    return vec3<T>(
        magnitude(v),
        std::atan2(v.y, v.x),
        v.z
    );
}

//a is distance from vertex A in range [0, 1] (can be outside range and outside triangle), AX, AY, and AZ define cartesian location of A
inline fvec2 barycentricToCartesian(const fvec3 & v, const fvec2 & A, const fvec2 & B, const fvec2 & C) {
    return fvec2(
        v.alpha * A.x + v.beta * B.x + v.gamma * C.x,
        v.alpha * A.y + v.beta * B.y + v.gamma * C.y
    );
}

inline fvec3 cartesianToBarycentric(const fvec2 & v, const fvec2 & A, const fvec2 & B, const fvec2 & C) {
    fmat2 mat(
        A.x - C.x, A.y - C.y,
        B.x - C.x, B.y - C.y
    );
    mat = inverse(mat);
    fvec3 bary(mat * (v - C));
    bary.gamma = 1.0f - bary.alpha - bary.beta;
    return bary;
}

//maps a point in cartesian space to the surface of a sphere and returns cartesian coordinates
//the point's x and y components, along with thetaPerUnit, determine the distance in radians from the origin
//the point's z component determines the radius
inline fvec3 mapToSphere(const fvec3 & v, float thetaPerUnit) {
    static const fmat2 perpMat = rotate(pi<float> / 2.0f);

    fvec2 perp = perpMat * fvec2(v);
    float theta = magnitude(fvec2(v)) * thetaPerUnit;
    fmat3 rot = rotate(fvec3(perp.x, perp.y, 0.0f), theta);

    return rot * fvec3(0.0f, 0.0f, v.z);
}

//draw a line from v to A; gets the angle of this line w/ respect to the A bisector
//possible angles range from -1 (along AB side) to 1 (along AC side), w/ linear-ness
inline float baryToAngleA(const fvec3 & v) {
    return (v.gamma - v.beta) / v.alpha;
}

inline float baryToAngleB(const fvec3 & v) {
    return (v.alpha - v.gamma) / v.beta;
}

inline float baryToAngleC(const fvec3 & v) {
    return (v.beta - v.alpha) / v.gamma;
}

//given a bary angle, return point along given a corresponding to angle
inline fvec3 baryFromAngleA(float angle, float a) {
    fvec3 v;
    v.alpha = a;
    v.gamma = (angle - 1) * (a - 1);
    v.beta = 1 - v.alpha - v.gamma;
    return v;
}

inline fvec3 baryFromAngleB(float angle, float b) {
    fvec3 v;
    v.beta = b;
    v.alpha = (angle - 1) * (b - 1);
    v.gamma = 1 - v.beta - v.alpha;
    return v;
}

inline fvec3 baryFromAngleC(float angle, float c) {
    fvec3 v;
    v.gamma = c;
    v.beta = (angle - 1) * (c - 1);
    v.alpha = 1 - v.gamma - v.beta;
    return v;
}

template <typename T, eif_floating_t<T> = 0>
inline vec2<T> pointOnDiscFibonacci(nat i, nat n) {
    return polarToCartesian(qcu::vec2<T>(
        std::sqrt(T(i) / T(n)),
        phi<T> * T(i)
    ));
}

template <typename T, eif_floating_t<T> = 0>
inline vec3<T> pointOnSphereFibonacci(nat i, nat n) {
    T z((1 - 1 / T(n)) * (1 - 2 * T(i) /  T(n - 1)));
    return cylindricToCartesian(qcu::vec3<T>(
        std::sqrt(1 - z * z),
        phi<T> * T(i),
        z
    ));
}



template <typename T>
struct Dampener {

    static_assert(std::is_floating_point_v<T>);

    const T angularFreq, dampingRatio, dt;

    Dampener(T angularFreq, T dampingRatio, T dt) :
        angularFreq(angularFreq),
        dampingRatio(dampingRatio),
        dt(dt)
    {}

    virtual ~Dampener() = default;

};

template <typename T>
struct OverDampener : public Dampener<T> {

    const T za, zb, z0, z1, z2, expTerm1, expTerm2;

    OverDampener(T angularFreq, T dampingRatio, T dt) :
        Dampener(angularFreq, max(dampingRatio, T(1.001)), dt),
        za(-this->angularFreq * this->dampingRatio),
        zb(this->angularFreq * std::sqrt(this->dampingRatio * this->dampingRatio - T(1.0))),
        z0(T(1.0) / (T(-2.0) * zb)),
        z1(za - zb),
        z2(za + zb),
        expTerm1(std::exp(z1 * this->dt)),
        expTerm2(std::exp(z2 * this->dt))
    {}

    template <typename U>
    void dampen(U & pos, U & vel, const U & targetPos) const {
        U dp(pos - targetPos);
        U c1((vel - dp * z2) * z0);
        U c2(dp - c1);
        pos = targetPos + c1 * expTerm1 + c2 * expTerm2;
        vel = c1 * z1 * expTerm1 + c2 * z2 * expTerm2;
    }

};

template <typename T>
struct CriticalDampener : public Dampener<T> {

    const T expTerm;

    CriticalDampener(T angularFreq, T dt) :
        Dampener(angularFreq, T(1.0), dt),
        expTerm(std::exp(-this->angularFreq * this->dt))
    {}

    template <typename U>
    void dampen(U & pos, U & vel, const U & targetPos) const {
        U dp(pos - targetPos);
        U c1(vel + angularFreq * dp);
        U c2((c1 * dt + dp) * expTerm);
        pos = targetPos + c2;
        vel = c1 * expTerm - c2 * angularFreq;
    }

};

template <typename T, typename U, eif_floating_t<T> = 0>
void dampen(U & pos, U & vel, const U & targetPos, T angularFreq, T dt) {
    T expTerm(std::exp(-angularFreq * dt));
    U dp(pos - targetPos);
    U c1(vel + angularFreq * dp);
    U c2((c1 * dt + dp) * expTerm);
    pos = targetPos + c2;
    vel = c1 * expTerm - c2 * angularFreq;
}

template <typename T>
struct UnderDampener : public Dampener<T> {

    const T omegaZeta, alpha, expTerm, cosTerm, sinTerm;

    UnderDampener(T angularFreq, T dampingRatio, T dt) :
        Dampener(angularFreq, min(dampingRatio, T(0.999)), dt),
        omegaZeta(this->angularFreq * this->dampingRatio),
        alpha(this->angularFreq * std::sqrt(T(1.0) - this->dampingRatio * this->dampingRatio)),
        expTerm(std::exp(-omegaZeta * dt)),
        cosTerm(std::cos(alpha * this->dt)),
        sinTerm(std::sin(alpha * this->dt))
    {}

    template <typename U>
    void dampen(U & pos, U & vel, const U & targetPos) const {
        U dp(pos - targetPos);
        U c((vel + omegaZeta * dp) / alpha);
        pos = targetPos + expTerm * (dp * cosTerm + c * sinTerm);
        vel = -expTerm * ((dp * omegaZeta - c * alpha) * cosTerm + (dp * alpha + c * omegaZeta) * sinTerm);
    }

};



}