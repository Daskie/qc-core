namespace qc {



//------------------------------------------------------------------------------
// Other



//--- operator<< ---

template <typename T, int t_n>
inline std::ostream & operator<<(std::ostream & os, const mat<T, t_n> & m) {
    os << "[";
    if constexpr (t_n >= 1) { os << m.c1; }
    if constexpr (t_n >= 2) { os << m.c2; }
    if constexpr (t_n >= 3) { os << m.c3; }
    if constexpr (t_n >= 4) { os << m.c4; }
    os << "]";
    return os;
}

//--- isIdentity ---

template <typename T, int t_n>
inline bool isIdentity(const mat<T, t_n> & m) {
    if constexpr (t_n == 1) {
        return
            m.c1.x == T(1.0);
    }

    if constexpr (t_n == 2) {
        return
            m.c1.x == T(1.0) && m.c2.y == T(1.0) &&
            m.c2.x == T(0.0) &&
            m.c1.y == T(0.0);
    }

    if constexpr (t_n == 3) {
        return
            m.c1.x == T(1.0) && m.c2.y == T(1.0) && m.c3.z == T(1.0) &&
            m.c3.x == T(0.0) && m.c3.y == T(0.0) &&
            m.c1.y == T(0.0) && m.c1.z == T(0.0) &&
            m.c2.x == T(0.0) && m.c2.z == T(0.0);
    }

    if constexpr (t_n == 4) {
        return
            m.c1.x == T(1.0) && m.c2.y == T(1.0) && m.c3.z == T(1.0) && m.c4.w == T(1.0) &&
            m.c4.x == T(0.0) && m.c4.y == T(0.0) && m.c4.z == T(0.0) &&
            m.c1.y == T(0.0) && m.c1.z == T(0.0) && m.c1.w == T(0.0) &&
            m.c2.x == T(0.0) && m.c2.z == T(0.0) && m.c2.w == T(0.0) &&
            m.c3.x == T(0.0) && m.c3.y == T(0.0) && m.c3.w == T(0.0);
    }
}

//--- transpose ---

template <typename T, int t_n>
inline mat<T, t_n> transpose(const mat<T, t_n> & m) {
    if constexpr (t_n == 2) return mat2<T>(m.row<0>(), m.row<1>());
    if constexpr (t_n == 3) return mat3<T>(m.row<0>(), m.row<1>(), m.row<2>());
    if constexpr (t_n == 4) return mat4<T>(m.row<0>(), m.row<1>(), m.row<2>(), m.row<3>());
}

//--- cofactor ---

template <typename T, int t_n>
inline mat<T, t_n> cofactor(const mat<T, t_n> & m) {
    if constexpr (t_n == 2) return mat2<T>(
        +m.c2.y, -m.c2.x,
        -m.c1.y, +m.c1.x
    );

    if constexpr (t_n == 3) return mat3<T>(
        +(m.c2.y * m.c3.z - m.c3.y * m.c2.z), -(m.c2.x * m.c3.z - m.c3.x * m.c2.z), +(m.c2.x * m.c3.y - m.c3.x * m.c2.y),
        -(m.c1.y * m.c3.z - m.c3.y * m.c1.z), +(m.c1.x * m.c3.z - m.c3.x * m.c1.z), -(m.c1.x * m.c3.y - m.c3.x * m.c1.y),
        +(m.c1.y * m.c2.z - m.c2.y * m.c1.z), -(m.c1.x * m.c2.z - m.c2.x * m.c1.z), +(m.c1.x * m.c2.y - m.c2.x * m.c1.y)
    );

    if constexpr (t_n == 4) {
        T yz12(m.c1.y * m.c2.z - m.c2.y * m.c1.z);
        T yz13(m.c1.y * m.c3.z - m.c3.y * m.c1.z);
        T yz14(m.c1.y * m.c4.z - m.c4.y * m.c1.z);
        T yw12(m.c1.y * m.c2.w - m.c2.y * m.c1.w);
        T yw13(m.c1.y * m.c3.w - m.c3.y * m.c1.w);
        T yw14(m.c1.y * m.c4.w - m.c4.y * m.c1.w);
        T yz23(m.c2.y * m.c3.z - m.c3.y * m.c2.z);
        T yz24(m.c2.y * m.c4.z - m.c4.y * m.c2.z);
        T yw23(m.c2.y * m.c3.w - m.c3.y * m.c2.w);
        T yw24(m.c2.y * m.c4.w - m.c4.y * m.c2.w);
        T zw12(m.c1.z * m.c2.w - m.c2.z * m.c1.w);
        T zw13(m.c1.z * m.c3.w - m.c3.z * m.c1.w);
        T zw14(m.c1.z * m.c4.w - m.c4.z * m.c1.w);
        T yz34(m.c3.y * m.c4.z - m.c4.y * m.c3.z);
        T yw34(m.c3.y * m.c4.w - m.c4.y * m.c3.w);
        T zw23(m.c2.z * m.c3.w - m.c3.z * m.c2.w);
        T zw24(m.c2.z * m.c4.w - m.c4.z * m.c2.w);
        T zw34(m.c3.z * m.c4.w - m.c4.z * m.c3.w);

        T xyz123(m.c1.x * yz23 - m.c2.x * yz13 + m.c3.x * yz12);
        T xyz124(m.c1.x * yz24 - m.c2.x * yz14 + m.c4.x * yz12);
        T xyz134(m.c1.x * yz34 - m.c3.x * yz14 + m.c4.x * yz13);
        T xyw123(m.c1.x * yw23 - m.c2.x * yw13 + m.c3.x * yw12);
        T xyw124(m.c1.x * yw24 - m.c2.x * yw14 + m.c4.x * yw12);
        T xyw134(m.c1.x * yw34 - m.c3.x * yw14 + m.c4.x * yw13);
        T xzw123(m.c1.x * zw23 - m.c2.x * zw13 + m.c3.x * zw12);
        T xzw124(m.c1.x * zw24 - m.c2.x * zw14 + m.c4.x * zw12);
        T xzw134(m.c1.x * zw34 - m.c3.x * zw14 + m.c4.x * zw13);
        T xyz234(m.c2.x * yz34 - m.c3.x * yz24 + m.c4.x * yz23);
        T xyw234(m.c2.x * yw34 - m.c3.x * yw24 + m.c4.x * yw23);
        T xzw234(m.c2.x * zw34 - m.c3.x * zw24 + m.c4.x * zw23);
        T yzw123(m.c1.y * zw23 - m.c2.y * zw13 + m.c3.y * zw12);
        T yzw124(m.c1.y * zw24 - m.c2.y * zw14 + m.c4.y * zw12);
        T yzw134(m.c1.y * zw34 - m.c3.y * zw14 + m.c4.y * zw13);
        T yzw234(m.c2.y * zw34 - m.c3.y * zw24 + m.c4.y * zw23);

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
    if constexpr (t_n == 1) return
        m.c1.x;

    if constexpr (t_n == 2) return
        + m.c1.x * m.c2.y
        - m.c2.x * m.c1.y;

    if constexpr (t_n == 3) return
        + m.c1.x * (m.c2.y * m.c3.z - m.c3.y * m.c2.z)
        - m.c2.x * (m.c1.y * m.c3.z - m.c3.y * m.c1.z)
        + m.c3.x * (m.c1.y * m.c2.z - m.c2.y * m.c1.z);

    if constexpr (t_n == 4) {
        T zw12 = m.c1.z * m.c2.w - m.c2.z * m.c1.w;
        T zw13 = m.c1.z * m.c3.w - m.c3.z * m.c1.w;
        T zw14 = m.c1.z * m.c4.w - m.c4.z * m.c1.w;
        T zw23 = m.c2.z * m.c3.w - m.c3.z * m.c2.w;
        T zw24 = m.c2.z * m.c4.w - m.c4.z * m.c2.w;
        T zw34 = m.c3.z * m.c4.w - m.c4.z * m.c3.w;

        return
            + m.c1.x * (m.c2.y * zw34 - m.c3.y * zw24 + m.c4.y * zw23)
            - m.c2.x * (m.c1.y * zw34 - m.c3.y * zw14 + m.c4.y * zw13)
            + m.c3.x * (m.c1.y * zw24 - m.c2.y * zw14 + m.c4.y * zw12)
            - m.c4.x * (m.c1.y * zw23 - m.c2.y * zw13 + m.c3.y * zw12);
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

template <typename T, int t_mn, int t_vn, eif_t<t_mn == t_vn + 1>>
inline mat<T, t_mn> & translate(mat<T, t_mn> & m, const vec<T, t_vn> & delta) {
    if constexpr (t_vn == 1 && t_mn == 2) {
        m.c1.x += delta.x * m.c1.y;
        m.c2.x += delta.x * m.c2.y;

        return m;
    }

    if constexpr (t_vn == 2 && t_mn == 3) {
        m.c1.x += delta.x * m.c1.z;
        m.c2.x += delta.x * m.c2.z;
        m.c3.x += delta.x * m.c3.z;
        m.c1.y += delta.y * m.c1.z;
        m.c2.y += delta.y * m.c2.z;
        m.c3.y += delta.y * m.c3.z;

        return m;
    }

    if constexpr (t_vn == 3 && t_mn == 4) {
        m.c1.x += delta.x * m.c1.w;
        m.c2.x += delta.x * m.c2.w;
        m.c3.x += delta.x * m.c3.w;
        m.c4.x += delta.x * m.c4.w;
        m.c1.y += delta.y * m.c1.w;
        m.c2.y += delta.y * m.c2.w;
        m.c3.y += delta.y * m.c3.w;
        m.c4.y += delta.y * m.c4.w;
        m.c1.z += delta.z * m.c1.w;
        m.c2.z += delta.z * m.c2.w;
        m.c3.z += delta.z * m.c3.w;
        m.c4.z += delta.z * m.c4.w;

        return m;
    }
}

template <typename T, int t_n>
inline mat<T, t_n> scale(const vec<T, t_n> & scale) {
    if constexpr (t_n == 2) return mat2<T>(
        scale.x,  T(0.0),
         T(0.0), scale.y
    );

    if constexpr (t_n == 3) return mat3<T>(
        scale.x,  T(0.0),  T(0.0),
         T(0.0), scale.y,  T(0.0),
         T(0.0),  T(0.0), scale.z
    );

    if constexpr (t_n == 4) return mat4<T>(
        scale.x,  T(0.0),  T(0.0),  T(0.0),
         T(0.0), scale.y,  T(0.0),  T(0.0),
         T(0.0),  T(0.0), scale.z,  T(0.0),
         T(0.0),  T(0.0),  T(0.0), scale.w
    ); 
}

template <typename T, int t_mn, int t_vn>
inline mat<T, t_mn> & scale(mat<T, t_mn> & m, const vec<T, t_vn> & scale) {
    if constexpr (t_vn == 1 && t_mn == 2) {        
        m.c1.x *= scale.x;
        m.c2.x *= scale.x;

        return m;
    }

    if constexpr (t_vn == 2 && t_mn == 2) {
        m.c1.x *= scale.x;
        m.c2.x *= scale.x;
        m.c1.y *= scale.y;
        m.c2.y *= scale.y;

        return m;
    }

    if constexpr (t_vn == 2 && t_mn == 3) {
        m.c1.x *= scale.x;
        m.c2.x *= scale.x;
        m.c3.x *= scale.x;
        m.c1.y *= scale.y;
        m.c2.y *= scale.y;
        m.c3.y *= scale.y;

        return m;
    }

    if constexpr (t_vn == 3 && t_mn == 3) {
        m.c1.x *= scale.x;
        m.c2.x *= scale.x;
        m.c3.x *= scale.x;
        m.c1.y *= scale.y;
        m.c2.y *= scale.y;
        m.c3.y *= scale.y;
        m.c1.z *= scale.z;
        m.c2.z *= scale.z;
        m.c3.z *= scale.z;

        return m;
    }

    if constexpr (t_vn == 3 && t_mn == 4) {
        m.c1.x *= scale.x;
        m.c2.x *= scale.x;
        m.c3.x *= scale.x;
        m.c4.x *= scale.x;
        m.c1.y *= scale.y;
        m.c2.y *= scale.y;
        m.c3.y *= scale.y;
        m.c4.y *= scale.y;
        m.c1.z *= scale.z;
        m.c2.z *= scale.z;
        m.c3.z *= scale.z;
        m.c4.z *= scale.z;

        return m;
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

    return rotate_n(normalize(axis), sinTheta, cosTheta);
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
    return euler_n(normalize(forward), normalize(up), theta, phi, psi);
}

template <typename T>
inline mat3<T> euler_n(const vec3<T> & forward, const vec3<T> & up, T theta, T phi, T psi) {
    return rotate_n(up, theta) * rotate_n(cross(forward, up), phi) * rotate_n(forward, psi);
}

template <typename T, int t_n>
inline mat<T, t_n> align(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return align_n(normalize(v1), normalize(v2));
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
    return align_n(normalize(forward1), normalize(up1), normalize(forward2), normalize(up2));
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
    vec3<T> w(normalize(camLoc - lookAt));
    vec3<T> u(normalize(cross(up, w)));
    vec3<T> v(cross(w, u));

    return view_on(camLoc, u, v, w);
}

template <typename T>
inline mat4<T> view(const vec3<T> & camLoc, const vec3<T> & camU, const vec3<T> & camV, const vec3<T> & camW) {
    return view_n(camLoc, normalize(camU), normalize(camV), normalize(camW));
}

template <typename T>
inline mat4<T> view_n(const vec3<T> & camLoc, const vec3<T> & camU, const vec3<T> & camV, const vec3<T> & camW) {
    return mat4<T>(mapTo(camU, camV, camW)) * translate(-camLoc);
}

template <typename T>
inline mat4<T> view_o(const vec3<T> & camLoc, const vec3<T> & camU, const vec3<T> & camV, const vec3<T> & camW) {
    return view_on(camLoc, normalize(camU), normalize(camV), normalize(camW));
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