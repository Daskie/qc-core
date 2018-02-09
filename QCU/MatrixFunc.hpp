#pragma once



#include "Matrix.hpp"
#include "VectorFunc.hpp"



namespace qcu {



template <typename T, int t_m, int t_n> inline std::ostream & operator<<(std::ostream & os, const mat<T, t_m, t_n> & m);

template <typename T, int t_n> inline bool isIdentity(const mat<T, t_n, t_n> & m);

template <typename T, int t_m, int t_n> inline mat<T, t_n, t_m> transpose(const mat<T, t_m, t_n> & m);

template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> cofactor(const mat<T, t_m, t_n> & m);

template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> adjoint(const mat<T, t_m, t_n> & m);

template <typename T, int t_m, int t_n> inline T determinant(const mat<T, t_m, t_n> & m);

template <typename T, int t_m, int t_n> inline mat<T, t_m, t_n> inverse(const mat<T, t_m, t_n> & m);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORMATIONS -----------------------------------------------------------------------------------------------------



template <typename T, int t_n> inline mat<T, t_n + 1> translate(const vec<T, t_n> & delta);
template <typename T, int t_m, int t_n, eif_t<t_m == t_n + 1> = 0> inline mat<T, t_m> & translate(mat<T, t_m> & mat, const vec<T, t_n> & delta);

template <typename T, int t_n> inline mat<T, t_n> scale(const vec<T, t_n> & scale);
template <typename T, int t_m, int t_n> inline mat<T, t_m> & scale(mat<T, t_m> & mat, const vec<T, t_n> & scale);

template <typename T> inline mat2<T> rotate(T angle);

template <typename T> inline mat3<T> rotateX(T angle);

template <typename T> inline mat3<T> rotateY(T angle);

template <typename T> inline mat3<T> rotateZ(T angle);

template <typename T> inline mat3<T> rotate(const vec3<T> & axis, T sinTheta, T cosTheta);
template <typename T> inline mat3<T> rotate_n(const vec3<T> & axis, T sinTheta, T cosTheta);

template <typename T> inline mat3<T> rotate(const vec3<T> & axis, T angle);
template <typename T> inline mat3<T> rotate_n(const vec3<T> & axis, T angle);

//theta: thumb points up, phi: right, psi: forward
template <typename T> inline mat3<T> euler(const vec3<T> & forward, const vec3<T> & up, T theta, T phi, T psi);
template <typename T> inline mat3<T> euler_n(const vec3<T> & forward, const vec3<T> & up, T theta, T phi, T psi);

template <typename T, int t_n> inline mat<T, t_n> align(const vec<T, t_n> & v1, const vec<T, t_n> & v2);
template <typename T, int t_n> inline mat<T, t_n> align_n(const vec<T, t_n> & v1, const vec<T, t_n> & v2);

//expects orthogonal fvectors
template <typename T> inline mat3<T> align(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2);
template <typename T> inline mat3<T> align_n(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2);

// _o variants (orthogonal) usable when the transformation matrix, T, from basis
// A to B is orthogonal i.e. A's basis vectors don't need to be orthogonal, nor
// B's, but the angles between A's basis vectors must be the same as B's
template <typename T> inline mat2<T> map(const vec2<T> & x1, const vec2<T> & y1, const vec2<T> & x2, const vec2<T> & y2);
template <typename T> inline mat2<T> map_o(const vec2<T> & x1, const vec2<T> & y1, const vec2<T> & x2, const vec2<T> & y2);
template <typename T> inline mat3<T> map(const vec3<T> & x1, const vec3<T> & y1, const vec3<T> & z1, const vec3<T> & x2, const vec3<T> & y2, const vec3<T> & z2);
template <typename T> inline mat3<T> map_o(const vec3<T> & x1, const vec3<T> & y1, const vec3<T> & z1, const vec3<T> & x2, const vec3<T> & y2, const vec3<T> & z2);

template <typename T> inline mat2<T> mapTo(const vec2<T> & x, const vec2<T> & y);
template <typename T> inline mat2<T> mapTo_o(const vec2<T> & x, const vec2<T> & y);
template <typename T> inline mat3<T> mapTo(const vec3<T> & x, const vec3<T> & y, const vec3<T> & z);
template <typename T> inline mat3<T> mapTo_o(const vec3<T> & x, const vec3<T> & y, const vec3<T> & z);

template <typename T> inline mat2<T> mapFrom(const vec2<T> & x, const vec2<T> & y);
template <typename T> inline mat3<T> mapFrom(const vec3<T> & x, const vec3<T> & y, const vec3<T> & z);

template <typename T> inline mat4<T> orthoProj(T width, T height, T near, T far);
template <typename T> inline mat4<T> orthoProjAsym(T left, T right, T bottom, T top, T near, T far);

//fov is angle in radians between top and bottom planes, aspectRatio is screen width / height, zNear is distance to near plane, zFar is distance to far plane
template <typename T> inline mat4<T> perspProj(T fov, T aspectRatio, T near, T far);
//fovNX is angle between center and left plane, fovPX between center and right, fovNY between center and bottom, fovPY between center and top
template <typename T> inline mat4<T> perspProjAsym(T fovLeft, T fovRight, T fovBottom, T fovTop, T near, T far);

//forward and up must not be parallel
template <typename T> inline mat4<T> view(const vec3<T> & camLoc, const vec3<T> & camForward, const vec3<T> & up);

template <typename T> inline mat4<T> view(const vec3<T> & camLoc, const vec3<T> & camU, const vec3<T> & camV, const vec3<T> & camW);
template <typename T> inline mat4<T> view_n(const vec3<T> & camLoc, const vec3<T> & camU, const vec3<T> & camV, const vec3<T> & camW);
//basis vectors are orthonormal (optimination)
template <typename T> inline mat4<T> view_o(const vec3<T> & camLoc, const vec3<T> & camU, const vec3<T> & camV, const vec3<T> & camW);
template <typename T> inline mat4<T> view_on(const vec3<T> & camLoc, const vec3<T> & camU, const vec3<T> & camV, const vec3<T> & camW);



//==============================================================================================================================================================
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================================================



//------------------------------------------------------------------------------
// Other



//--- operator<< ---

namespace detail {

template <int t_j, typename T, int t_m, int t_n>
inline std::ostream & printCol(std::ostream & os, const mat<T, t_m, t_n> & m) {
    if constexpr (t_m == 1) return os << m.at<0, t_j>();
    if constexpr (t_m == 2) return os << m.at<0, t_j>() << " " << m.at<1, t_j>();
    if constexpr (t_m == 3) return os << m.at<0, t_j>() << " " << m.at<1, t_j>() << " " << m.at<2, t_j>();
    if constexpr (t_m == 4) return os << m.at<0, t_j>() << " " << m.at<1, t_j>() << " " << m.at<2, t_j>() << " " << m.at<3, t_j>();
}

}

template <typename T, int t_m, int t_n>
inline std::ostream & operator<<(std::ostream & os, const mat<T, t_m, t_n> & m) {
    os << "[";
    if constexpr (t_n >= 1) { os << " "; detail::printCol<0>(os, m); os << " "; }
    if constexpr (t_n >= 2) { os << "| "; detail::printCol<1>(os, m); os << " "; }
    if constexpr (t_n >= 3) { os << "| "; detail::printCol<2>(os, m); os << " "; }
    if constexpr (t_n >= 4) { os << "| "; detail::printCol<3>(os, m); os << " "; }
    os << "]";
    return os;
}

//--- isIdentity ---

template <typename T, int t_n>
inline bool isIdentity(const mat<T, t_n, t_n> & m) {
    if constexpr (t_n == 1) {
        return
            m.x1 == T(1.0);
    }

    if constexpr (t_n == 2) {
        return
            m.x1 == T(1.0) && m.y2 == T(1.0) &&
            m.x2 == T(0.0) &&
            m.y1 == T(0.0);
    }

    if constexpr (t_n == 3) {
        return
            m.x1 == T(1.0) && m.y2 == T(1.0) && m.z3 == T(1.0) &&
            m.x2 == T(0.0) && m.x3 == T(0.0) &&
            m.y1 == T(0.0) && m.y3 == T(0.0) &&
            m.z1 == T(0.0) && m.z2 == T(0.0);
    }

    if constexpr (t_n == 4) {
        return
            m.x1 == T(1.0) && m.y2 == T(1.0) && m.z3 == T(1.0) && m.w4 == T(1.0) &&
            m.x2 == T(0.0) && m.x3 == T(0.0) && m.x4 == T(0.0) &&
            m.y1 == T(0.0) && m.y3 == T(0.0) && m.y4 == T(0.0) &&
            m.z1 == T(0.0) && m.z2 == T(0.0) && m.z4 == T(0.0) &&
            m.w1 == T(0.0) && m.w2 == T(0.0) && m.w3 == T(0.0);
    }
}

//--- transpose ---

template <typename T, int t_m, int t_n>
inline mat<T, t_n, t_m> transpose(const mat<T, t_m, t_n> & m) {
    if constexpr (t_m == 1) return mat<T, t_n, t_m>(m.row<0>());
    if constexpr (t_m == 2) return mat<T, t_n, t_m>(m.row<0>(), m.row<1>());
    if constexpr (t_m == 3) return mat<T, t_n, t_m>(m.row<0>(), m.row<1>(), m.row<2>());
    if constexpr (t_m == 4) return mat<T, t_n, t_m>(m.row<0>(), m.row<1>(), m.row<2>(), m.row<3>());
}

//--- cofactor ---

template <typename T, int t_n>
inline mat<T, t_n> cofactor(const mat<T, t_n> & m) {
    if constexpr (t_n == 1) {
        return mat1<T>(T(1));
    }

    if constexpr (t_n == 2) {
        return mat2<T>(
            +m.y2, -m.x2,
            -m.y1, +m.x1
        );
    }

    if constexpr (t_n == 3) {
        return mat3<T>(
            +(m.y2 * m.z3 - m.y3 * m.z2), -(m.x2 * m.z3 - m.x3 * m.z2), +(m.x2 * m.y3 - m.x3 * m.y2),
            -(m.y1 * m.z3 - m.y3 * m.z1), +(m.x1 * m.z3 - m.x3 * m.z1), -(m.x1 * m.y3 - m.x3 * m.y1),
            +(m.y1 * m.z2 - m.y2 * m.z1), -(m.x1 * m.z2 - m.x2 * m.z1), +(m.x1 * m.y2 - m.x2 * m.y1)
        );
    }

    if constexpr (t_n == 4) {
        T yz12(m.y1 * m.z2 - m.y2 * m.z1);
        T yz13(m.y1 * m.z3 - m.y3 * m.z1);
        T yz14(m.y1 * m.z4 - m.y4 * m.z1);
        T yw12(m.y1 * m.w2 - m.y2 * m.w1);
        T yw13(m.y1 * m.w3 - m.y3 * m.w1);
        T yw14(m.y1 * m.w4 - m.y4 * m.w1);
        T yz23(m.y2 * m.z3 - m.y3 * m.z2);
        T yz24(m.y2 * m.z4 - m.y4 * m.z2);
        T yw23(m.y2 * m.w3 - m.y3 * m.w2);
        T yw24(m.y2 * m.w4 - m.y4 * m.w2);
        T zw12(m.z1 * m.w2 - m.z2 * m.w1);
        T zw13(m.z1 * m.w3 - m.z3 * m.w1);
        T zw14(m.z1 * m.w4 - m.z4 * m.w1);
        T yz34(m.y3 * m.z4 - m.y4 * m.z3);
        T yw34(m.y3 * m.w4 - m.y4 * m.w3);
        T zw23(m.z2 * m.w3 - m.z3 * m.w2);
        T zw24(m.z2 * m.w4 - m.z4 * m.w2);
        T zw34(m.z3 * m.w4 - m.z4 * m.w3);

        T xyz123(m.x1 * yz23 - m.x2 * yz13 + m.x3 * yz12);
        T xyz124(m.x1 * yz24 - m.x2 * yz14 + m.x4 * yz12);
        T xyz134(m.x1 * yz34 - m.x3 * yz14 + m.x4 * yz13);
        T xyw123(m.x1 * yw23 - m.x2 * yw13 + m.x3 * yw12);
        T xyw124(m.x1 * yw24 - m.x2 * yw14 + m.x4 * yw12);
        T xyw134(m.x1 * yw34 - m.x3 * yw14 + m.x4 * yw13);
        T xzw123(m.x1 * zw23 - m.x2 * zw13 + m.x3 * zw12);
        T xzw124(m.x1 * zw24 - m.x2 * zw14 + m.x4 * zw12);
        T xzw134(m.x1 * zw34 - m.x3 * zw14 + m.x4 * zw13);
        T xyz234(m.x2 * yz34 - m.x3 * yz24 + m.x4 * yz23);
        T xyw234(m.x2 * yw34 - m.x3 * yw24 + m.x4 * yw23);
        T xzw234(m.x2 * zw34 - m.x3 * zw24 + m.x4 * zw23);
        T yzw123(m.y1 * zw23 - m.y2 * zw13 + m.y3 * zw12);
        T yzw124(m.y1 * zw24 - m.y2 * zw14 + m.y4 * zw12);
        T yzw134(m.y1 * zw34 - m.y3 * zw14 + m.y4 * zw13);
        T yzw234(m.y2 * zw34 - m.y3 * zw24 + m.y4 * zw23);

        return mat4<T>(
            +yzw234, -xzw234, +xyw234, -xyz234,
            -yzw134, +xzw134, -xyw134, +xyz134,
            +yzw124, -xzw124, +xyw124, -xyz124,
            -yzw123, +xzw123, -xyw123, +xyz123
        );
    }
}

//-- adjoint ---

template <typename T, int t_n>
inline mat<T, t_n> adjoint(const mat<T, t_n> & m) {
    return transpose(cofactor(m));
}

//--- determinant ---

template <typename T, int t_n>
inline T determinant(const mat<T, t_n> & m) {
    if constexpr (t_n == 1) {
        return m.x1;
    }

    if constexpr (t_n == 2) {
        return
            + m.x1 * m.y2
            - m.x2 * m.y1;
    }

    if constexpr (t_n == 3) {
        return
            + m.x1 * (m.y2 * m.z3 - m.y3 * m.z2)
            - m.x2 * (m.y1 * m.z3 - m.y3 * m.z1)
            + m.x3 * (m.y1 * m.z2 - m.y2 * m.z1);
    }

    if constexpr (t_n == 4) {
        T zw12 = m.z1 * m.w2 - m.z2 * m.w1;
        T zw13 = m.z1 * m.w3 - m.z3 * m.w1;
        T zw14 = m.z1 * m.w4 - m.z4 * m.w1;
        T zw23 = m.z2 * m.w3 - m.z3 * m.w2;
        T zw24 = m.z2 * m.w4 - m.z4 * m.w2;
        T zw34 = m.z3 * m.w4 - m.z4 * m.w3;

        return
            + m.x1 * (m.y2 * zw34 - m.y3 * zw24 + m.y4 * zw23)
            - m.x2 * (m.y1 * zw34 - m.y3 * zw14 + m.y4 * zw13)
            + m.x3 * (m.y1 * zw24 - m.y2 * zw14 + m.y4 * zw12)
            - m.x4 * (m.y1 * zw23 - m.y2 * zw13 + m.y3 * zw12);
    }
}

//--- inverse ---

template <typename T, int t_n>
inline mat<T, t_n> inverse(const mat<T, t_n> & m) {
    T det(determinant(m));
    if (zero(det)) {
        return nullMat<T, t_n>();
    }

    return adjoint(m) / determinant(m);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORMATIONS IMPLEMENTATION --------------------------------------------------------------------------------------



template <typename T, int t_n>
inline mat<T, t_n + 1> translate(const vec<T, t_n> & delta) {
    if constexpr (t_n == 1) {
        return mat2<T>(
             T(1.0), T(0.0),
            delta.x, T(1.0)
        );
    }

    if constexpr (t_n == 2) {
        return mat3<T>(
             T(1.0),  T(0.0), T(0.0),
             T(0.0),  T(1.0), T(0.0),
            delta.x, delta.y, T(1.0)
        );
    }

    if constexpr (t_n == 3) {
        return mat4<T>(
             T(1.0),  T(0.0),  T(0.0), T(0.0),
             T(0.0),  T(1.0),  T(0.0), T(0.0),
             T(0.0),  T(0.0),  T(1.0), T(0.0),
            delta.x, delta.y, delta.z, T(1.0)
        );
    }
}

template <typename T, int t_m, int t_n, eif_t<t_m == t_n + 1>>
inline mat<T, t_m> & translate(mat<T, t_m> & mat, const vec<T, t_n> & delta) {
    if constexpr (t_n == 1 && t_m == 2) {
        mat.x1 += delta.x * mat.y1;
        mat.x2 += delta.x * mat.y2;
        return mat;
    }

    if constexpr (t_n == 2 && t_m == 3) {
        mat.x1 += delta.x * mat.z1;
        mat.x2 += delta.x * mat.z2;
        mat.x3 += delta.x * mat.z3;
        mat.y1 += delta.y * mat.z1;
        mat.y2 += delta.y * mat.z2;
        mat.y3 += delta.y * mat.z3;
        return mat;
    }

    if constexpr (t_n == 3 && t_m == 4) {
        mat.x1 += delta.x * mat.w1;
        mat.x2 += delta.x * mat.w2;
        mat.x3 += delta.x * mat.w3;
        mat.x4 += delta.x * mat.w4;
        mat.y1 += delta.y * mat.w1;
        mat.y2 += delta.y * mat.w2;
        mat.y3 += delta.y * mat.w3;
        mat.y4 += delta.y * mat.w4;
        mat.z1 += delta.z * mat.w1;
        mat.z2 += delta.z * mat.w2;
        mat.z3 += delta.z * mat.w3;
        mat.z4 += delta.z * mat.w4;
        return mat;
    }
}

template <typename T, int t_n>
inline mat<T, t_n> scale(const vec<T, t_n> & scale) {
    if constexpr (t_n == 1) {
        return mat1<T>(
            scale.x
        );
    }

    if constexpr (t_n == 2) {
        return mat2<T>(
            scale.x,  T(0.0),
             T(0.0), scale.y
        );
    }

    if constexpr (t_n == 3) {
        return mat3<T>(
            scale.x,  T(0.0),  T(0.0),
             T(0.0), scale.y,  T(0.0),
             T(0.0),  T(0.0), scale.z
        );
    }    
}

template <typename T, int t_m, int t_n>
inline mat<T, t_m> & scale(mat<T, t_m> & mat, const vec<T, t_n> & scale) {
    if constexpr (t_n == 1 && t_m == 1) {
        mat.x1 *= scale.x;
        return mat;
    }

    if constexpr (t_n == 1 && t_m == 2) {        
        mat.x1 *= scale.x;
        mat.x2 *= scale.x;
        return mat;
    }

    if constexpr (t_n == 2 && t_m == 2) {
        mat.x1 *= scale.x;
        mat.x2 *= scale.x;
        mat.y1 *= scale.y;
        mat.y2 *= scale.y;
        return mat;
    }

    if constexpr (t_n == 2 && t_m == 3) {
        mat.x1 *= scale.x;
        mat.x2 *= scale.x;
        mat.x3 *= scale.x;
        mat.y1 *= scale.y;
        mat.y2 *= scale.y;
        mat.y3 *= scale.y;
        return mat;
    }

    if constexpr (t_n == 3 && t_m == 3) {
        mat.x1 *= scale.x;
        mat.x2 *= scale.x;
        mat.x3 *= scale.x;
        mat.y1 *= scale.y;
        mat.y2 *= scale.y;
        mat.y3 *= scale.y;
        mat.z1 *= scale.z;
        mat.z2 *= scale.z;
        mat.z3 *= scale.z;
        return mat;
    }

    if constexpr (t_n == 3 && t_m == 4) {
        mat.x1 *= scale.x;
        mat.x2 *= scale.x;
        mat.x3 *= scale.x;
        mat.x4 *= scale.x;
        mat.y1 *= scale.y;
        mat.y2 *= scale.y;
        mat.y3 *= scale.y;
        mat.y4 *= scale.y;
        mat.z1 *= scale.z;
        mat.z2 *= scale.z;
        mat.z3 *= scale.z;
        mat.z4 *= scale.z;
        return mat;
    }
}

template <typename T>
inline mat2<T> rotate(T angle) {
    T s(std::sin(angle));
    T c(std::cos(angle));

    return mat2<T>(
         c, s,
        -s, c
    );
}

template <typename T>
inline mat3<T> rotateX(T angle) {
    T s(std::sin(angle));
    T c(std::cos(angle));

    return mat3<T>(
        T(1.0), T(0.0), T(0.0),
        T(0.0),      c,      s,
        T(0.0),     -s,      c
    );
}

template <typename T>
inline mat3<T> rotateY(T angle) {
    T s(std::sin(angle));
    T c(std::cos(angle));

    return mat3<T>(
             c, T(0.0),     -s,
        T(0.0), T(1.0), T(0.0),
             s, T(0.0),      c
    );
}

template <typename T>
inline mat3<T> rotateZ(T angle) {
    T s(std::sin(angle));
    T c(std::cos(angle));

    return mat3<T>(
             c,      s, T(0.0),
            -s,      c, T(0.0),
        T(0.0), T(0.0), T(1.0)
    );
}

template <typename T>
inline mat3<T> rotate(const vec3<T> & axis, T sinTheta, T cosTheta) {
    if (zero(magnitude2(axis))) { //can't rotate around 0 length fvector
        return mat3<T>();
    }

    return rotate_n(norm(axis), sinTheta, cosTheta);
}

template <typename T>
inline mat3<T> rotate_n(const vec3<T> & axis, T s, T c) {
    T cm(T(1.0) - c);
    T xs(axis.x * s);
    T ys(axis.y * s);
    T zs(axis.z * s);
    T xcm(axis.x * cm);
    T ycm(axis.y * cm);
    T zcm(axis.z * cm);
    T xycm(xcm * axis.y);
    T yzcm(ycm * axis.z);
    T zxcm(zcm * axis.x);

    return mat3<T>(
         xcm * axis.x +  c, xycm          + zs, zxcm          - ys,
        xycm          - zs,  ycm * axis.y +  c, yzcm          + xs,
        zxcm          + ys, yzcm          - xs,  zcm * axis.z +  c
    );
}

template <typename T>
inline mat3<T> rotate(const vec3<T> & axis, T angle) {
    return rotate(axis, std::sin(angle), std::cos(angle));
}

template <typename T>
inline mat3<T> rotate_n(const vec3<T> & axis, T angle) {
    return rotate_n(axis, std::sin(angle), std::cos(angle));
}

template <typename T>
inline mat3<T> euler(const vec3<T> & forward, const vec3<T> & up, T theta, T phi, T psi) {
    return euler_n(norm(forward), norm(up), theta, phi, psi);
}

template <typename T>
inline mat3<T> euler_n(const vec3<T> & forward, const vec3<T> & up, T theta, T phi, T psi) {
    return rotate_n(up, theta) * rotate_n(cross(forward, up), phi) * rotate_n(forward, psi);
}

template <typename T, int t_n>
inline mat<T, t_n> align(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return align_n(norm(v1), norm(v2));
}

template <typename T>
inline mat2<T> align_n(const vec2<T> & v1, const vec2<T> & v2) {
    T c(cross(v1, v2));
    T d(dot(v1, v2));

    return rotate(c < T(0.0) ? -std::acos(d) : std::acos(d));
}

template <typename T>
inline mat3<T> align_n(const vec3<T> & v1, const vec3<T> & v2) {
    T d(dot(v1, v2));
    if (equal(d, T(1.0))) { // already aligned, and would break rotation
        return mat3<T>();
    }
    if (equal(d, T(-1.0))) { // opposite direction, pick arbitrary axis to rotate around
        return rotate_n(ortho(v1), pi<T>);
    }

    vec3<T> c(cross(v1, v2));
    T m(magnitude(c));

    return rotate_n(c * (T(1.0) / m), m, d);
}

template <typename T>
inline mat3<T> align(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2) {
    return align_n(norm(forward1), norm(up1), norm(forward2), norm(up2));
}

template <typename T>
inline mat3<T> align_n(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2) {
    mat3<T> m = align_n(forward1, forward2);
    return align_n(m * up1, up2) * m;
}

template <typename T>
inline mat2<T> map(const vec2<T> & x1, const vec2<T> & y1, const vec2<T> & x2, const vec2<T> & y2) {
    mat2<T> a(x1, y1);
    mat2<T> b(x2, y2);

    return inverse(b) * a;
}

template <typename T>
inline mat2<T> map_o(const vec2<T> & x1, const vec2<T> & y1, const vec2<T> & x2, const vec2<T> & y2) {
    mat2<T> a(x1, y1);
    mat2<T> b(x2, y2);

    return transpose(b) * a;
}

template <typename T>
inline mat3<T> map(const vec3<T> & x1, const vec3<T> & y1, const vec3<T> & z1, const vec3<T> & x2, const vec3<T> & y2, const vec3<T> & z2) {
    mat3<T> a(x1, y1, z1);
    mat3<T> b(x2, y2, z2);

    return inverse(b) * a;
}

template <typename T>
inline mat3<T> map_o(const vec3<T> & x1, const vec3<T> & y1, const vec3<T> & z1, const vec3<T> & x2, const vec3<T> & y2, const vec3<T> & z2) {
    mat3<T> a(x1, y1, z1);
    mat3<T> b(x2, y2, z2);

    return transpose(b) * a;
}

template <typename T>
inline mat2<T> mapTo(const vec2<T> & x, const vec2<T> & y) {
    return inverse(mat2<T>(x, y));
}

template <typename T>
inline mat2<T> mapTo_o(const vec2<T> & x, const vec2<T> & y) {
    return transpose(mat2<T>(x, y));
}

template <typename T>
inline mat3<T> mapTo(const vec3<T> & x, const vec3<T> & y, const vec3<T> & z) {
    return inverse(mat3<T>(x, y, z));
}

template <typename T>
inline mat3<T> mapTo_o(const vec3<T> & x, const vec3<T> & y, const vec3<T> & z) {
    return transpose(mat3<T>(x, y, z));
}

template <typename T>
inline mat2<T> mapFrom(const vec2<T> & x, const vec2<T> & y) {
    return mat2<T>(x, y);
}

template <typename T>
inline mat3<T> mapFrom(const vec3<T> & x, const vec3<T> & y, const vec3<T> & z) {
    return mat3<T>(x, y, z);
}

template <typename T>
inline mat4<T> orthoProj(T width, T height, T near, T far) {
    return mat4<T>(
        T(2.0) / width,          T(0.0),                      T(0.0), T(0.0),
                T(0.0), T(2.0) / height,                      T(0.0), T(0.0),
                T(0.0),          T(0.0),       T(2.0) / (near - far), T(0.0),
                T(0.0),          T(0.0), (far + near) / (near - far), T(1.0)
    );
}

template <typename T>
inline mat4<T> orthoProjAsym(T left, T right, T bottom, T top, T near, T far) {
    return mat4<T>(
                T(2.0) / (right - left),                          T(0.0),                      T(0.0), T(0.0),
                                 T(0.0),         T(2.0) / (top - bottom),                      T(0.0), T(0.0),
                                 T(0.0),                          T(0.0),       T(2.0) / (near - far), T(0.0),
        (right + left) / (left - right), (top + bottom) / (bottom - top), (far + near) / (near - far), T(1.0)
    );
}

template <typename T>
inline mat4<T> perspProj(T fov, T aspectRatio, T near, T far) {
    T near_right(T(1.0) / std::tan(fov / T(2.0)));

    return mat4<T>(
        near_right,                   T(0.0),                             T(0.0), T( 0.0),
            T(0.0), near_right * aspectRatio,                             T(0.0), T( 0.0),
            T(0.0),                   T(0.0),        (far + near) / (near - far), T(-1.0),
            T(0.0),                   T(0.0), T(2.0) * far * near / (near - far), T( 0.0)
    );
}

template <typename T>
inline mat4<T> perspProjAsym(T fovLeft, T fovRight, T fovBottom, T fovTop, T near, T far) {
    T left(near * -std::tan(fovLeft));
    T right(near * std::tan(fovRight));
    T bottom(near * -std::tan(fovBottom));
    T top(near * std::tan(fovTop));

    return mat4<T>(
         T(2.0) * near / (right - left),                          T(0.0),                             T(0.0), T( 0.0),
                                 T(0.0),  T(2.0) * near / (top - bottom),                             T(0.0), T( 0.0),
        (right + left) / (right - left), (top + bottom) / (top - bottom),        (far + near) / (near - far), T(-1.0),
                                 T(0.0),                          T(0.0), T(2.0) * far * near / (near - far), T( 0.0)
    );
}

template <typename T>
inline mat4<T> view(const vec3<T> & camLoc, const vec3<T> & lookAt, const vec3<T> & up) {
    vec3<T> w(norm(camLoc - lookAt));
    vec3<T> u(norm(cross(up, w)));
    vec3<T> v(cross(w, u));

    return view_on(camLoc, u, v, w);
}

template <typename T>
inline mat4<T> view(const vec3<T> & camLoc, const vec3<T> & camU, const vec3<T> & camV, const vec3<T> & camW) {
    return view_n(camLoc, norm(camU), norm(camV), norm(camW));
}

template <typename T>
inline mat4<T> view_n(const vec3<T> & camLoc, const vec3<T> & camU, const vec3<T> & camV, const vec3<T> & camW) {
    return mat4<T>(mapTo(camU, camV, camW)) * translate(-camLoc);
}

template <typename T>
inline mat4<T> view_o(const vec3<T> & camLoc, const vec3<T> & camU, const vec3<T> & camV, const vec3<T> & camW) {
    return view_on(camLoc, norm(camU), norm(camV), norm(camW));
}

template <typename T>
inline mat4<T> view_on(const vec3<T> & camLoc, const vec3<T> & camU, const vec3<T> & camV, const vec3<T> & camW) {
    vec3<T> trans(-camLoc);
    return mat4<T>(
                  camU.x,           camV.x,           camW.x, T(0.0),
                  camU.y,           camV.y,           camW.y, T(0.0),
                  camU.z,           camV.z,           camW.z, T(0.0),
        dot(camU, trans), dot(camV, trans), dot(camW, trans), T(1.0)
    );
}



}