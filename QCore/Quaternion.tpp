namespace qc {



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUAT IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors
    


template <typename T>
constexpr quat<T>::quat() :
    a(T(0.0)), w(T(1.0))
{}

template <typename T>
constexpr quat<T>::quat(const quat<T> & q) :
    a(q.a), w(q.w)
{}

template <typename T>
constexpr quat<T>::quat(quat<T> && q) :
    a(q.a), w(q.w)
{}

template <typename T> template <typename U>
constexpr quat<T>::quat(const quat<U> & q) :
    a(q.a), w(T(q.w))
{}

template <typename T>
constexpr quat<T>::quat(const vec3<T> & a, T w) :
    a(a), w(w)
{}

template <typename T>
constexpr quat<T>::quat(const vec3<T> & v) :
    a(v), w(T(0.0))
{}

template <typename T>
constexpr quat<T>::quat(const vec4<T> & v) :
    a(v.x, v.y, v.z), w(v.w)
{}



//------------------------------------------------------------------------------
// Assignment



template <typename T>
inline quat<T> & quat<T>::operator=(const quat<T> & q) {
    a = q.a; w = q.w;
    return *this;
}

template <typename T>
inline quat<T> & quat<T>::operator=(quat<T> && q) {
    a = q.a; w = q.w;
    return *this;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUAT FUNCTIONS IMPLEMENTATION ---------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Arithmetic Assignment



template <typename T>
inline quat<T> & operator+=(quat<T> & q1, const quat<T> & q2) {
    return q1 = q1 + q2;
}

template <typename T>
inline quat<T> & operator-=(quat<T> & q1, const quat<T> & q2) {
    return q1 = q1 - q2;
}

template <typename T>
inline quat<T> & operator*=(quat<T> & q1, const quat<T> & q2) {
    return q1 = q1 * q2;
}

template <typename T>
inline quat<T> & operator*=(quat<T> & q, T v) {
    return q = q * v;
}

template <typename T>
inline quat<T> & operator/=(quat<T> & q1, const quat<T> & q2) {
    return q1 = q1 / q2;
}



//------------------------------------------------------------------------------
// Arithmetic Operators



template <typename T>
inline quat<T> operator+(const quat<T> & q) {
    return quat<T>(+q.a, +q.w);
}

template <typename T>
inline quat<T> operator-(const quat<T> & q) {
    return quat<T>(-q.a, -q.w);
}

template <typename T>
inline quat<T> operator+(const quat<T> & q1, const quat<T> & q2) {
    return quat<T>(q1.a + q2.a, q1.w + q2.w);
}

template <typename T>
inline quat<T> operator-(const quat<T> & q1, const quat<T> & q2) {
    return quat<T>(q1.a - q2.a, q1.w - q2.w);
}

template <typename T>
inline quat<T> operator*(const quat<T> & q1, const quat<T> & q2) {
    return quat<T>(
        q1.w * q2.a + q2.w * q1.a + cross(q1.a, q2.a),
        q1.w * q2.w - dot(q1.a, q2.a)
    );
}

template <typename T>
inline quat<T> operator*(const quat<T> & q, T v) {
    return quat<T>(q.a * v, q.w * v);
}

template <typename T>
inline quat<T> operator*(T v, const quat<T> & q) {
    return quat<T>(v * q.a, v * q.w);
}

template <typename T>
inline vec3<T> operator*(const quat<T> & q, const vec3<T> & v) {
    vec3<T> t(T(2.0) * cross(q.a, v));
    return v + q.w * t + cross(q.a, t);
}

template <typename T>
inline quat<T> operator/(const quat<T> & q1, const quat<T> & q2) {
    return quat<T>(q1.a * q2.w - q2.a * q1.w - cross(q1.a, q2.a), dot(q1, q2));
}



//------------------------------------------------------------------------------
// Comparison Operators



template <typename T>
inline bool operator==(const quat<T> & q1, const quat<T> & q2) {
    return q1.a == q2.a && q1.w == q2.w;
}

template <typename T>
inline bool operator!=(const quat<T> & q1, const quat<T> & q2) {
    return q1.a != q2.a || q1.w != q2.w;
}



}