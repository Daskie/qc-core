#include <qc-core/math.hpp>

#include <gtest/gtest.h>

using namespace qc::primitives;
using namespace qc::types;

template <Floating T>
void _testCompileT()
{
    T v{};
    vec2<T> v2{};
    vec3<T> v3{};
    vec4<T> v4{};

    static_cast<void>(qc::polarToCartesian(v));
    static_cast<void>(qc::polarToCartesian(v, v));
    static_cast<void>(qc::polarToCartesian(v2));

    static_cast<void>(qc::cartesianToPolar(v2));

    static_cast<void>(qc::sphericalToCartesian(v, v));
    static_cast<void>(qc::sphericalToCartesian(v, v, v));
    static_cast<void>(qc::sphericalToCartesian(v3));

    static_cast<void>(qc::cartesianToSpherical(v3));

    static_cast<void>(qc::cylindricalToCartesian(v3));

    static_cast<void>(qc::cartesianToCylindrical(v3));

    static_cast<void>(qc::barycentricToCartesian(v3, v2, v2, v2));

    static_cast<void>(qc::cartesianToBarycentric(v2, v2, v2, v2));

    static_cast<void>(qc::discPoint(v));

    static_cast<void>(qc::circlePoint(v2));

    static_cast<void>(qc::spherePoint(v2));

    static_cast<void>(qc::ballPoint(v3));

    static_cast<void>(qc::circlePointFibonacci<T>(0u, 1u));

    static_cast<void>(qc::spherePointFibonacci<T>(0u, 1u));

    static_cast<void>(qc::quadraticRoots(v, v, v));

    static_cast<void>(qc::distance2ToLine(v2, v2, v2));
    static_cast<void>(qc::distance2ToLine(v3, v3, v3));
    static_cast<void>(qc::distance2ToLine(v4, v4, v4));

    qc::Dampener<T> damper{v, v, v};

    qc::OverDampener<T> overDampener{v, v, v};
    overDampener.dampen(v, v, v);

    qc::CriticalDampener<T> criticalDampener{v, v};
    criticalDampener.dampen(v, v, v);

    qc::UnderDampener<T> underDampener{v, v, v};
    underDampener.dampen(v, v, v);

    qc::dampen(v, v, v, v, v);
    qc::dampen(v, v, v, v);

    static_cast<void>(qc::areaOfPoly(1u, &v2));

    static_cast<void>(qc::centroidOfPoly(1u, &v2));
}

TEST(Math, compile)
{
    _testCompileT<f32>();
    _testCompileT<f64>();
}
