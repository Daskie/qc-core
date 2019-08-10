namespace qc {

//------------------------------------------------------------------------------
// Other

template <typename T>
inline std::ostream & operator<<(std::ostream & os, const quat<T> & q) {
    return os << "[ " << q.a.i << " " << q.a.j << " " << q.a.k << " | " << q.w << " ]";
}

//------------------------------------------------------------------------------
// Uncategorized

template <typename T>
inline T dot(const quat<T> & q1, const quat<T> & q2) {
    return dot(q1.a, q2.a) + q1.w * q2.w;
}

template <typename T>
inline T magnitude(const quat<T> & q) {
    return std::sqrt(magnitude2(q));
}

template <typename T>
inline T magnitude2(const quat<T> & q) {
    return magnitude2(q.a) + q.w * q.w;
}

template <typename T>
inline quat<T> normalize(const quat<T> & q) {
    T m2(magnitude2(q));
    if (zero(m2)) {
        return {};
    }
    T m_inv(T(1.0) / std::sqrt(m2));
    return {q.a * m_inv, q.w * m_inv};
}

template <typename T>
inline quat<T> inverse(const quat<T> & q) {
    return {-q.a, q.w};
}

template <typename T>
inline T quatAngle(const quat<T> & q) {
    return std::acos(q.w) * T(2.0);
}

template <typename T>
inline vec3<T> quatAxis(const quat<T> & q) {
    return quatAxis_n(normalize(q));
}

template <typename T>
inline vec3<T> quatAxis_n(const quat<T> & q) {
    T d2(T(1.0) - q.w * q.w);
    if (zero(d2)) {
        return {};
    }
    return q.a * (T(1.0) / std::sqrt(d2));
}

template <typename T>
inline quat<T> mix(const quat<T> & q1, const quat<T> & q2, T t) {
    T s(T(1.0) - t);
    return {s * q1.a + t * q2.a, s * q1.w + t * q2.w};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORMATIONS IMPLEMENTATION --------------------------------------------------------------------------------------

/*inline quat<T> pow(const quat<T> & q, T t) {
    return angleAxis(angle(q) * t, axis(q));
}*/

template <typename T>
inline quat<T> rotateQ(const vec3<T> & axis, T angle) {
    return rotateQ_n(normalize(axis), angle);
}
template <typename T>
inline quat<T> rotateQ_n(const vec3<T> & axis, T angle) {
    return {std::sin(angle * T(0.5)) * axis, std::cos(angle * T(0.5))};
}

template <typename T>
inline quat<T> alignQ(const vec3<T> & v1, const vec3<T> & v2) {
    return alignQ_n(normalize(v1), normalize(v2));
}
template <typename T>
inline quat<T> alignQ_n(const vec3<T> & v1, const vec3<T> & v2) {
    return rotateQ(cross(v1, v2), std::acos(dot(v1, v2)));
}

template <typename T>
inline quat<T> alignQ(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2) {
    return alignQ_n(normalize(forward1), normalize(up1), normalize(forward2), normalize(up2));
}
template <typename T>
inline quat<T> alignQ_n(const vec3<T> & forward1, const vec3<T> & up1, const vec3<T> & forward2, const vec3<T> & up2) {
    quat<T> q(alignQ_n(forward1, forward2));
    return alignQ_n(q * up1, up2) * q;
}

template <typename T>
inline quat<T> eulerQ(const vec3<T> & forward, const vec3<T> & up, T theta, T phi, T psi) {
    return eulerQ_n(normalize(forward), normalize(up), theta, phi, psi);
}
template <typename T>
inline quat<T> eulerQ_n(const vec3<T> & forward, const vec3<T> & up, T theta, T phi, T psi) {
    return rotateQ_n(up, theta) * rotateQ_n(cross(forward, up), phi) * rotateQ_n(forward, psi);
}

template <typename T>
Q_CX_ABLE mat3<T> toMat(const quat<T> & q) {
    T wi(q.w   * q.a.i);
    T wj(q.w   * q.a.j);
    T wk(q.w   * q.a.k);
    T ii(q.a.i * q.a.i);
    T ij(q.a.i * q.a.j);
    T ik(q.a.i * q.a.k);
    T jj(q.a.j * q.a.j);
    T jk(q.a.j * q.a.k);
    T kk(q.a.k * q.a.k);

    constexpr T t_1(1.0), t_2(2.0);

    return {
        t_1 - t_2 * (jj + kk), t_2       * (ij + wk), t_2       * (ik - wj),
        t_2       * (ij - wk), t_1 - t_2 * (ii + kk), t_2       * (jk + wi),
        t_2       * (ik + wj), t_2       * (jk - wi), t_1 - t_2 * (ii + jj)
    };
}

template <typename T>
inline quat<T> nlerp(const quat<T> & q1, const quat<T> & q2, T t) {
    return normalize(quat<T>(mix(q1, q2, t)));
}

template <typename T>
inline quat<T> slerp(const quat<T> & q1, const quat<T> & q2_, T t) {
    quat<T> q2(q2_);

    T cosHalfTheta(dot(q1, q2));

    //make sure to take the shorter route
    if (cosHalfTheta < T(0.0)) {
        cosHalfTheta = -cosHalfTheta;
        q2 = -q2;
    }
    //if parallel, no interpolation necessary
    if (equal(cosHalfTheta, T(1.0))) {
        return q1;
    }

    T halfTheta(std::acos(cosHalfTheta));
    T sinHalfTheta(std::sqrt(T(1.0) - cosHalfTheta * cosHalfTheta));

    return (q1 * std::sin((T(1.0) - t) * halfTheta) + q2 * std::sin(t * halfTheta)) * (T(1.0) / sinHalfTheta);
}

}
