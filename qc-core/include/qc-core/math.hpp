#pragma once

#include <cmath>

#include <qc-core/matrix-ext.hpp>

namespace qc
{
    template <Floating T>
    nodisc inline vec2<T> polarToCartesian(const T theta)
    {
        return {std::cos(theta), std::sin(theta)};
    }

    template <Floating T>
    nodisc inline vec2<T> polarToCartesian(const T r, const T theta)
    {
        return r * polarToCartesian(theta);
    }

    //
    // `v.x` is the radius
    // `v.y` is theta
    //
    template <Floating T>
    nodisc inline vec2<T> polarToCartesian(const vec2<T> v)
    {
        return polarToCartesian(v.x, v.y);
    }

    template <Floating T>
    nodisc inline vec2<T> cartesianToPolar(const vec2<T> v)
    {
        return {magnitude(v), std::atan2(v.y, v.x)};
    }

    //
    // `theta` is the angle on the xy plane
    // `phi` is the angle from the z axis
    //
    template <Floating T>
    nodisc inline vec3<T> sphericalToCartesian(const T theta, const T phi)
    {
        const T sinPhi{std::sin(phi)};
        return {sinPhi * std::cos(theta), sinPhi * std::sin(theta), std::cos(phi)};
    }

    //
    // `r` is the radius
    // `theta` is the angle on the xy plane
    // `phi` is the angle from the z axis
    //
    template <Floating T>
    nodisc inline vec3<T> sphericalToCartesian(const T r, const T theta, const T phi)
    {
        return r * sphericalToCartesian(theta, phi);
    }

    //
    // `v.x` is the radius
    // `v.y` is theta, or the angle on the xy plane
    // `v.z` is the angle from the z axis
    //
    template <Floating T>
    nodisc inline vec3<T> sphericalToCartesian(const vec3<T> v)
    {
        return sphericalToCartesian(v.y, v.z) * v.x;
    }

    template <Floating T>
    nodisc inline vec3<T> cartesianToSpherical(const vec3<T> v)
    {
        const T r{magnitude(v)};
        return {r, std::atan2(v.y, v.x), std::acos(v.z / r)};
    }

    template <Floating T>
    nodisc inline vec3<T> cylindricalToCartesian(const T r, const T theta, const T z)
    {
        return {polarToCartesian(r, theta), z};
    }

    template <Floating T>
    nodisc inline vec3<T> cylindricalToCartesian(const vec3<T> v)
    {
        return cylindricalToCartesian(v.x, v.y, v.z);
    }

    template <Floating T>
    nodisc inline vec3<T> cartesianToCylindrical(const vec3<T> v)
    {
        return {magnitude(v), std::atan2(v.y, v.x), v.z};
    }

    // `a` is distance from vertex A in range [0, 1] (can be outside range and outside triangle), AX, AY, and AZ define cartesian position of A
    template <Floating T>
    nodisc inline vec2<T> barycentricToCartesian(const vec3<T> v, const vec2<T> A, const vec2<T> B, const vec2<T> C)
    {
        return {
            v.x * A.x + v.y * B.x + v.z * C.x,
            v.x * A.y + v.y * B.y + v.z * C.y};
    }

    template <Floating T>
    nodisc inline vec3<T> cartesianToBarycentric(const vec2<T> v, const vec2<T> A, const vec2<T> B, const vec2<T> C)
    {
        mat2<T> mat{
            A.x - C.x, A.y - C.y,
            B.x - C.x, B.y - C.y};
        mat = inverse(mat);
        vec3<T> bary(mat * (v - C));
        bary.z = T(1.0) - bary.x - bary.y;
        return bary;
    }

    //
    // Returns a uniformly distributed point on the perimeter of the unit circle given the random input `v`.
    // `v` should have a linear distribution in range [0, 1].
    //
    template <Floating T>
    nodisc inline vec2<T> discPoint(const T v)
    {
        return polarToCartesian((T(2.0) * number::pi<T>) * v);
    }

    //
    // Returns a uniformly distributed point in the unit circle given the random input `v`.
    // `v` should have a linear distribution in range [0, 1].
    //
    template <Floating T>
    nodisc inline vec2<T> circlePoint(const vec2<T> v)
    {
        return std::sqrt(v.x) * discPoint(v.y);
    }

    //
    // Returns a uniformly distributed point on the surface of the unit sphere given the random input `v`.
    // `v` should have a linear distribution in range [0, 1].
    //
    template <Floating T>
    nodisc inline vec3<T> spherePoint(const vec2<T> v)
    {
        return sphericalToCartesian(
            (T(2.0) * number::pi<T>) * v.x,
            std::acos(T(1.0) - T(2.0) * v.y));
    }

    //
    // Returns a uniformly distributed point in the unit sphere given the random input `v`.
    // `v` should have a linear distribution in range [0, 1].
    //
    template <Floating T>
    nodisc inline vec3<T> ballPoint(const vec3<T> v)
    {
        return std::cbrt(v.x) * spherePoint(v.yz());
    }

    template <Floating T>
    nodisc inline vec2<T> circlePointFibonacci(const u32 i, const u32 n)
    {
        const T p{T(i + 1u) / T(n + 1u)};
        return circlePoint(vec2<T>{p, number::phi<T> * T(i)});
    }

    template <Floating T>
    nodisc inline vec3<T> spherePointFibonacci(const u32 i, const u32 n)
    {
        const T p{T(i + 1u) / T(n + 1u)};
        return spherePoint(vec2<T>{number::phi<T> * T(i), p});
    }

    // This correctly avoids numeric stability issues when a is very small but not zero
    // See https://math.stackexchange.com/questions/4000135/quadratic-formula-fails-numerically-at-small-a-coefficients/4000145#4000145
    template <Floating T>
    nodisc inline Duo<T> quadraticRoots(const T a, const T b, const T c)
    {
        if (a != T(0.0))
        {
            const T h{b * b - T(4.0) * a * c};

            if (h >= T(0.0))
            {
                const T s{std::sqrt(h)};
                const T u{0.5f * (-b - (b > T(0.0) ? s : -s))};
                if (u == T(0.0))
                {
                    return {T(0.0), T(0.0)};
                }
                else
                {
                    return {u / a, c / u};
                }
            }
            else
            {
                return {number::nan<T>, number::nan<T>};
            }
        }
        else if (b != T(0.0))
        {
            return {-c / b, number::nan<T>};
        }
        else
        {
            return {number::nan<T>, number::nan<T>};
        }
    }

    template <Floating T, u32 n>
    nodisc inline T distance2ToLine(const vec<T, n> & p1, const vec<T, n> & p2, const vec<T, n> & p)
    {
        const vec<T, n> a{p2 - p1};
        const vec<T, n> b{p - p1};
        const T t{clamp(dot(a, b) / magnitude2(a), T(0.0), T(1.0))};
        return distance2(b, t * a);
    }

    template <Floating T>
    struct Dampener
    {
        const T angularFreq, dampingRatio, dt;

        Dampener(const T angularFreq, const T dampingRatio, const T dt) :
            angularFreq(angularFreq),
            dampingRatio(dampingRatio),
            dt(dt)
        {}

        virtual ~Dampener() = default;
    };

    template <Floating T>
    struct OverDampener : public Dampener<T>
    {
        const T za, zb, z0, z1, z2, expTerm1, expTerm2;

        OverDampener(const T angularFreq, const T dampingRatio, const T dt) :
            Dampener<T>(angularFreq, max(dampingRatio, T(1.001)), dt),
            za(-Dampener<T>::angularFreq * Dampener<T>::dampingRatio),
            zb(Dampener<T>::angularFreq * std::sqrt(Dampener<T>::dampingRatio * Dampener<T>::dampingRatio - T(1.0))),
            z0(T(1.0) / (T(-2.0) * zb)),
            z1(za - zb),
            z2(za + zb),
            expTerm1(std::exp(z1 * Dampener<T>::dt)),
            expTerm2(std::exp(z2 * Dampener<T>::dt))
        {}

        template <Floating U>
        void dampen(U & pos, U & vel, const U & targetPos) const
        {
            const U dp{pos - targetPos};
            const U c1{(vel - dp * z2) * z0};
            const U c2{dp - c1};
            pos = targetPos + c1 * expTerm1 + c2 * expTerm2;
            vel = c1 * z1 * expTerm1 + c2 * z2 * expTerm2;
        }
    };

    template <Floating T>
    struct CriticalDampener : public Dampener<T>
    {
        const T expTerm;

        CriticalDampener(const T angularFreq, const T dt) :
            Dampener<T>(angularFreq, T(1.0), dt),
            expTerm(std::exp(-Dampener<T>::angularFreq * Dampener<T>::dt))
        {}

        template <Floating U>
        void dampen(U & pos, U & vel, const U & targetPos) const
        {
            const U dp{pos - targetPos};
            const U c1{vel + this->angularFreq * dp};
            const U c2{(c1 * this->dt + dp) * expTerm};
            pos = targetPos + c2;
            vel = c1 * expTerm - c2 * this->angularFreq;
        }
    };

    template <Floating T>
    struct UnderDampener : public Dampener<T>
    {
        const T omegaZeta, alpha, expTerm, cosTerm, sinTerm;

        UnderDampener(const T angularFreq, const T dampingRatio, const T dt) :
            Dampener<T>{angularFreq, min(dampingRatio, T(0.999 /* TODO */)), dt},
            omegaZeta{Dampener<T>::angularFreq * Dampener<T>::dampingRatio},
            alpha{Dampener<T>::angularFreq * std::sqrt(T(1.0) - Dampener<T>::dampingRatio * Dampener<T>::dampingRatio)},
            expTerm{std::exp(-omegaZeta * dt)},
            cosTerm{std::cos(alpha * Dampener<T>::dt)},
            sinTerm{std::sin(alpha * Dampener<T>::dt)}
        {}

        void dampen(T & pos, T & vel, const T targetPos) const
        {
            const T dp{pos - targetPos};
            const T c{(vel + omegaZeta * dp) / alpha};
            pos = targetPos + expTerm * (dp * cosTerm + c * sinTerm);
            vel = -expTerm * ((dp * omegaZeta - c * alpha) * cosTerm + (dp * alpha + c * omegaZeta) * sinTerm);
        }
    };

    template <Floating T>
    inline void dampen(T & r_dist, T & r_vel, const T angularFreq, const T dt)
    {
        const T expTerm{std::exp(-angularFreq * dt)};
        const T c1{r_vel + angularFreq * r_dist};
        const T c2{(c1 * dt + r_dist) * expTerm};
        r_dist = -c2;
        r_vel = c1 * expTerm - c2 * angularFreq;
    }

    template <Floating T>
    inline void dampen(T & r_pos, const T targetPos, T & r_vel, const T angularFreq, const T dt)
    {
        T dist{r_pos - targetPos};
        dampen(dist, r_vel, angularFreq, dt);
        r_pos = targetPos - dist;
    }

    // Calculates the area of a non self-intersecting polygon
    // Points should be the vertices of the polygon given in order without duplicates
    template <Floating T>
    nodisc inline T areaOfPoly(const u64 n, const vec2<T> * const points)
    {
        T a{};
        for (u64 i{0u}; i < n - 1u; ++i)
        {
            const vec2<T> v1(points[i]), v2(points[i + 1u]);
            a += v1.x * v2.y - v2.x * v1.y;
        }
        const vec2<T> v1(points[n - 1u]), v2(points[0]);
        a += v1.x * v2.y - v2.x * v1.y;
        return T(0.5) * a;
    }

    // Calculates the centroid, or center of mass, of a non self-intersecting polygon
    // Points should be the vertices of the polygon given in order without duplicates
    template <Floating T>
    nodisc inline vec2<T> centroidOfPoly(const u64 n, const vec2<T> * const points)
    {
        T a{};
        vec2<T> c;
        for (u64 i{0u}; i < n - 1u; ++i)
        {
            const vec2<T> v1(points[i]), v2(points[i + 1u]);
            T temp{v1.x * v2.y - v2.x * v1.y};
            a += temp;
            c += (v1 + v2) * temp;
        }
        const vec2<T> v1(points[n - 1u]), v2(points[0]);
        const T temp{v1.x * v2.y - v2.x * v1.y};
        a += temp;
        c += (v1 + v2) * temp;
        return c / (T(3.0) * a);
    }
}
