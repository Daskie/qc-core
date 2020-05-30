#pragma once

#include <cmath>

#include "matrix-ext.hpp"

namespace qc::core {

    template <Floater T>
    inline vec2<T> polarToCartesian(const vec2<T> & v) {
        return {
            v.rad * std::cos(v.theta),
            v.rad * std::sin(v.theta)
        };
    }

    template <Floater T>
    inline vec2<T> cartesianToPolar(const vec2<T> & v) {
        return {
            magnitude(v),
            std::atan2(v.y, v.x)
        };
    }

    //r is radius, theta is angle on xy plane, phi is angle from z axis
    template <Floater T>
    inline vec3<T> sphericalToCartesian(const vec3<T> & v) {
        T sinTheta = std::sin(v.theta);
        T cosTheta = std::cos(v.theta);
        T sinPhi = std::sin(v.phi);
        T cosPhi = std::cos(v.phi);

        return {
            v.rad * sinPhi * cosTheta,
            v.rad * sinPhi * sinTheta,
            v.rad * cosPhi
        };
    }

    template <Floater T>
    inline vec3<T> cartesianToSpherical(const vec3<T> & v) {
        T rad(magnitude(v));
        return {
            rad,
            std::atan2(v.y, v.x),
            std::acos(v.z / rad)
        };
    }

    template <Floater T>
    inline vec3<T> cylindricToCartesian(const vec3<T> & v) {
        return {
            v.rad * std::cos(v.theta),
            v.rad * std::sin(v.theta),
            v.z
        };
    }

    template <Floater T>
    inline vec3<T> cartesianToCylindric(const vec3<T> & v) {
        return {
            magnitude(v),
            std::atan2(v.y, v.x),
            v.z
        };
    }

    //a is distance from vertex A in range [0, 1] (can be outside range and outside triangle), AX, AY, and AZ define cartesian location of A
    inline fvec2 barycentricToCartesian(const fvec3 & v, const fvec2 & A, const fvec2 & B, const fvec2 & C) {
        return fvec2(
            v.x * A.x + v.y * B.x + v.z * C.x,
            v.x * A.y + v.y * B.y + v.z * C.y
        );
    }

    inline fvec3 cartesianToBarycentric(const fvec2 & v, const fvec2 & A, const fvec2 & B, const fvec2 & C) {
        fmat2 mat(
            A.x - C.x, A.y - C.y,
            B.x - C.x, B.y - C.y
        );
        mat = inverse(mat);
        fvec3 bary(mat * (v - C));
        bary.z = 1.0f - bary.x - bary.y;
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
        return (v.z - v.y) / v.x;
    }

    inline float baryToAngleB(const fvec3 & v) {
        return (v.x - v.z) / v.y;
    }

    inline float baryToAngleC(const fvec3 & v) {
        return (v.y - v.x) / v.z;
    }

    //given a bary angle, return point along given a corresponding to angle
    inline fvec3 baryFromAngleA(float angle, float a) {
        fvec3 v;
        v.x = a;
        v.z = (angle - 1.0f) * (a - 1.0f);
        v.y = 1.0f - v.x - v.z;
        return v;
    }

    inline fvec3 baryFromAngleB(float angle, float b) {
        fvec3 v;
        v.y = b;
        v.x = (angle - 1.0f) * (b - 1.0f);
        v.z = 1.0f - v.y - v.x;
        return v;
    }

    inline fvec3 baryFromAngleC(float angle, float c) {
        fvec3 v;
        v.z = c;
        v.y = (angle - 1.0f) * (c - 1.0f);
        v.x = 1.0f - v.z - v.y;
        return v;
    }

    template <Floater T>
    inline vec2<T> pointOnDiscFibonacci(int i, int n) {
        return polarToCartesian(vec2<T>(
            std::sqrt(T(i) / T(n - 1)),
            T(2.0) * pi<T> * (T(2.0) - phi<T>) * T(i)
        ));
    }

    template <Floater T>
    inline vec3<T> pointOnSphereFibonacci(int i, int n) {
        T z(T(1.0) - T(2 * i) / T(n - 1));
        return cylindricToCartesian(vec3<T>(
            std::sqrt(T(1.0) - z * z),
            T(2.0) * pi<T> * (T(2.0) - phi<T>) * T(i),
            z
        ));
    }

    template <typename T>
    struct Dampener {

        static_assert(is_floating_point_v<T>);

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
            U c1(vel + this->angularFreq * dp);
            U c2((c1 * this->dt + dp) * expTerm);
            pos = targetPos + c2;
            vel = c1 * expTerm - c2 * this->angularFreq;
        }

    };

    template <Floater T, typename U>
    inline void dampen(U & r_pos, const U & targetPos, U & r_vel, T angularFreq, T dt) {
        U dist(r_pos - targetPos);
        dampen(dist, r_vel, angularFreq, dt);
        r_pos = targetPos - dist;
    }

    template <Floater T, typename U>
    inline void dampen(U & r_dist, U & r_vel, T angularFreq, T dt) {
        T expTerm(std::exp(-angularFreq * dt));
        U c1(r_vel + angularFreq * r_dist);
        U c2((c1 * dt + r_dist) * expTerm);
        r_dist = -c2;
        r_vel = c1 * expTerm - c2 * angularFreq;
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

    // Calculates the area of a non self-intersecting polygon
    // Points should be the vertices of the polygon given in order without duplicates
    template <Floater T>
    inline T areaOfPoly(size_t n, const vec2<T> * points) {
        T a{};
        for (size_t i(0u); i < n - 1u; ++i) {
            const vec2<T> & v1(points[i]), v2(points[i + 1u]);
            a += v1.x * v2.y - v2.x * v1.y;
        }
        const vec2<T> & v1(points[n - 1u]), v2(points[0]);
        a += v1.x * v2.y - v2.x * v1.y;
        return T(0.5) * a;
    }

    // Calculates the centroid, or center of mass, of a non self-intersecting polygon
    // Points should be the vertices of the polygon given in order without duplicates
    template <Floater T>
    inline vec2<T> centroidOfPoly(size_t n, const vec2<T> * points) {
        T a{};
        vec2<T> c;
        for (size_t i(0u); i < n - 1u; ++i) {
            const vec2<T> & v1(points[i]), v2(points[i + 1u]);
            T temp(v1.x * v2.y - v2.x * v1.y);
            a += temp;
            c += (v1 + v2) * temp;
        }
        const vec2<T> & v1(points[n - 1u]), v2(points[0]);
        T temp(v1.x * v2.y - v2.x * v1.y);
        a += temp;
        c += (v1 + v2) * temp;
        return c / (T(3.0) * a);
    }

}
