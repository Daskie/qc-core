namespace qc {



//======================================================================================================================
// VEC1 IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr vec<T, 1>::vec() :
    x(T(0))
{}

template <typename T>
constexpr vec<T, 1>::vec(const vec1<T> & v) :
    x(v.x)
{}

template <typename T>
constexpr vec<T, 1>::vec(vec1<T> && v) :
    x(v.x)
{}

template <typename T>
template <typename U>
constexpr vec<T, 1>::vec(const vec1<U> & v) :
    x(T(v.x))
{}

template <typename T>
template <typename U>
constexpr vec<T, 1>::vec(const vec2<U> & v) :
    x(T(v.x))
{}

template <typename T>
template <typename U>
constexpr vec<T, 1>::vec(const vec3<U> & v) :
    x(T(v.x))
{}

template <typename T>
template <typename U>
constexpr vec<T, 1>::vec(const vec4<U> & v) :
    x(T(v.x))
{}

template <typename T>
constexpr vec<T, 1>::vec(const T & v) :
    x(v)
{}



//------------------------------------------------------------------------------
// Assignment



template <typename T>
inline vec1<T> & vec<T, 1>::operator=(const vec1<T> & v) {
    x = v.x;
    return *this;
}

template <typename T>
inline vec1<T> & vec<T, 1>::operator=(vec1<T> && v) {
    x = v.x;
    return *this;
}

template <typename T>
inline vec1<T> & vec<T, 1>::operator=(const T & v) {
    x = v;
    return *this;
}

template <typename T>
template <int t_n>
inline vec1<T> & vec<T, 1>::operator=(const vec<T, t_n> & v) {
    if constexpr (t_n >= 1) x = v.x;
    if constexpr (t_n < 1) x = T(0);
    return *this;
}



//------------------------------------------------------------------------------
// Access



template <typename T>
inline T & vec<T, 1>::operator[](int i) {
    return *(&x + i);
}

template <typename T>
inline const T & vec<T, 1>::operator[](int i) const {
    return *(&x + i);
}



template <typename T>
template <int t_i>
inline T & vec<T, 1>::at() {
    static_assert(t_i == 0, "index out of bounds");
    if constexpr (t_i == 0) return x;
}

template <typename T>
template <int t_i>
constexpr const T & vec<T, 1>::at() const {
    static_assert(t_i == 0, "index out of bounds");
    if constexpr (t_i == 0) return x;
}



//======================================================================================================================
// VEC2 IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr vec<T, 2>::vec() :
    x(T(0)), y(T(0))
{}

template <typename T>
constexpr vec<T, 2>::vec(const vec2<T> & v) :
    x(v.x), y(v.y)
{}

template <typename T>
constexpr vec<T, 2>::vec(vec2<T> && v) :
    x(v.x), y(v.y)
{}

template <typename T>
template <typename U>
constexpr vec<T, 2>::vec(const vec1<U> & v) :
    x(T(v.x)), y(T(0))
{}

template <typename T>
template <typename U>
constexpr vec<T, 2>::vec(const vec2<U> & v) :
    x(T(v.x)), y(T(v.y))
{}

template <typename T>
template <typename U>
constexpr vec<T, 2>::vec(const vec3<U> & v) :
    x(T(v.x)), y(T(v.y))
{}

template <typename T>
template <typename U>
constexpr vec<T, 2>::vec(const vec4<U> & v) :
    x(T(v.x)), y(T(v.y))
{}

template <typename T>
constexpr vec<T, 2>::vec(const T & v) :
    x(v), y(v)
{}

template <typename T>
constexpr vec<T, 2>::vec(const T & v1, const T & v2) :
    x(v1), y(v2)
{}

template <typename T>
Q_CX_ABLE vec<T, 2>::vec(const vec1<T> & v1, const T & v2) :
    x(v1.x), y(v2)
{}

template <typename T>
Q_CX_ABLE vec<T, 2>::vec(const T & v1, const vec1<T> & v2) :
    x(v1), y(v2.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 2>::vec(const vec1<T> & v1, const vec1<T> & v2) :
    x(v1.x), y(v2.x)
{}



//------------------------------------------------------------------------------
// Assignment



template <typename T>
inline vec2<T> & vec<T, 2>::operator=(const vec2<T> & v) {
    x = v.x; y = v.y;
    return *this;
}

template <typename T>
inline vec2<T> & vec<T, 2>::operator=(vec2<T> && v) {
    x = v.x; y = v.y;
    return *this;
}

template <typename T>
inline vec2<T> & vec<T, 2>::operator=(const T & v) {
    x = v; y = v;
    return *this;
}

template <typename T>
template <int t_n>
inline vec2<T> & vec<T, 2>::operator=(const vec<T, t_n> & v) {
    if constexpr (t_n >= 1) x = v.x; if constexpr (t_n < 1) x = T(0);
    if constexpr (t_n >= 2) y = v.y; if constexpr (t_n < 2) y = T(0);
    return *this;
}



//------------------------------------------------------------------------------
// Access



template <typename T>
inline T & vec<T, 2>::operator[](int i) {
    return *(&x + i);
}

template <typename T>
inline const T & vec<T, 2>::operator[](int i) const {
    return *(&x + i);
}



template <typename T>
template <int t_i>
inline T & vec<T, 2>::at() {
    static_assert(t_i >= 0 && t_i <= 1, "index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
}

template <typename T>
template <int t_i>
constexpr const T & vec<T, 2>::at() const {
    static_assert(t_i >= 0 && t_i <= 1, "index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
}



//======================================================================================================================
// VEC3 IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr vec<T, 3>::vec() :
    x(T(0)), y(T(0)), z(T(0))
{}

template <typename T>
constexpr vec<T, 3>::vec(const vec3<T> & v) :
    x(v.x), y(v.y), z(v.z)
{}

template <typename T>
constexpr vec<T, 3>::vec(vec3<T> && v) :
    x(v.x), y(v.y), z(v.z)
{}

template <typename T>
template <typename U>
constexpr vec<T, 3>::vec(const vec1<U> & v) :
    x(T(v.x)), y(T(0)), z(T(0))
{}

template <typename T>
template <typename U>
constexpr vec<T, 3>::vec(const vec2<U> & v) :
    x(T(v.x)), y(T(v.y)), z(T(0))
{}

template <typename T>
template <typename U>
constexpr vec<T, 3>::vec(const vec3<U> & v) :
    x(T(v.x)), y(T(v.y)), z(T(v.z))
{}

template <typename T>
template <typename U>
constexpr vec<T, 3>::vec(const vec4<U> & v) :
    x(T(v.x)), y(T(v.y)), z(T(v.z))
{}

template <typename T>
constexpr vec<T, 3>::vec(const T & v) :
    x(v), y(v), z(v)
{}

template <typename T>
constexpr vec<T, 3>::vec(const T & v1, const T & v2, const T & v3) :
    x(v1), y(v2), z(v3)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(const vec1<T> & v1, const T & v2, const T & v3) :
    x(v1.x), y(v2), z(v3)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(const T & v1, const vec1<T> & v2, const T & v3) :
    x(v1), y(v2.x), z(v3)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(const T & v1, const T & v2, const vec1<T> & v3) :
    x(v1), y(v2), z(v3.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(const vec1<T> & v1, const vec1<T> & v2, const T & v3) :
    x(v1.x), y(v2.x), z(v3)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(const vec1<T> & v1, const T & v2, const vec1<T> & v3) :
    x(v1.x), y(v2), z(v3.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(const T & v1, const vec1<T> & v2, const vec1<T> & v3) :
    x(v1), y(v2.x), z(v3.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(const vec1<T> & v1, const vec1<T> & v2, const vec1<T> & v3) :
    x(v1.x), y(v2.x), z(v3.x)
{}

template <typename T>
Q_CONSTEX vec<T, 3>::vec(const vec2<T> & v1, const T & v2) :
    x(v1.x), y(v1.y), z(v2)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(const vec2<T> & v1, const vec1<T> & v2) :
    x(v1.x), y(v1.y), z(v2.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(const T & v1, const vec2<T> & v2) :
    x(v1), y(v2.x), z(v2.y)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(const vec1<T> & v1, const vec2<T> & v2) :
    x(v1.x), y(v2.x), z(v2.y)
{}



//------------------------------------------------------------------------------
// Assignment



template <typename T>
inline vec3<T> & vec<T, 3>::operator=(const vec3<T> & v) {
    x = v.x; y = v.y; z = v.z;
    return *this;
}

template <typename T>
inline vec3<T> & vec<T, 3>::operator=(vec3<T> && v) {
    x = v.x; y = v.y; z = v.z;
    return *this;
}

template <typename T>
inline vec3<T> & vec<T, 3>::operator=(const T & v) {
    x = v; y = v; z = v;
    return *this;
}

template <typename T>
template <int t_n>
inline vec3<T> & vec<T, 3>::operator=(const vec<T, t_n> & v) {
    if constexpr (t_n >= 1) x = v.x; if constexpr (t_n < 1) x = T(0);
    if constexpr (t_n >= 2) y = v.y; if constexpr (t_n < 2) y = T(0);
    if constexpr (t_n >= 3) z = v.z; if constexpr (t_n < 3) z = T(0);
    return *this;
}



//------------------------------------------------------------------------------
// Access



template <typename T>
inline T & vec<T, 3>::operator[](int i) {
    return *(&x + i);
}

template <typename T>
inline const T & vec<T, 3>::operator[](int i) const {
    return *(&x + i);
}

template <typename T>
template <int t_i>
inline T & vec<T, 3>::at() {
    static_assert(t_i >= 0 && t_i <= 2, "index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
    if constexpr (t_i == 2) return z;
}

template <typename T>
template <int t_i>
constexpr const T & vec<T, 3>::at() const {
    static_assert(t_i >= 0 && t_i <= 2, "index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
    if constexpr (t_i == 2) return z;
}

template <typename T>
inline vec2<T> & vec<T, 3>::xy() {
    return *reinterpret_cast<vec2<T> *>(&x);
}

template <typename T>
inline vec2<T> & vec<T, 3>::rg() {
    return *reinterpret_cast<vec2<T> *>(&r);
}

template <typename T>
inline vec2<T> & vec<T, 3>::st() {
    return *reinterpret_cast<vec2<T> *>(&s);
}

template <typename T>
inline vec2<T> & vec<T, 3>::yz() {
    return *reinterpret_cast<vec2<T> *>(&y);
}

template <typename T>
inline vec2<T> & vec<T, 3>::gb() {
    return *reinterpret_cast<vec2<T> *>(&g);
}

template <typename T>
inline vec2<T> & vec<T, 3>::tp() {
    return *reinterpret_cast<vec2<T> *>(&t);
}

template <typename T>
inline const vec2<T> & vec<T, 3>::xy() const {
    return *reinterpret_cast<const vec2<T> *>(&x);
}

template <typename T>
inline const vec2<T> & vec<T, 3>::rg() const {
    return *reinterpret_cast<const vec2<T> *>(&r);
}

template <typename T>
inline const vec2<T> & vec<T, 3>::st() const {
    return *reinterpret_cast<const vec2<T> *>(&s);
}

template <typename T>
inline const vec2<T> & vec<T, 3>::yz() const {
    return *reinterpret_cast<const vec2<T> *>(&y);
}

template <typename T>
inline const vec2<T> & vec<T, 3>::gb() const {
    return *reinterpret_cast<const vec2<T> *>(&g);
}

template <typename T>
inline const vec2<T> & vec<T, 3>::tp() const {
    return *reinterpret_cast<const vec2<T> *>(&t);
}



//======================================================================================================================
// VEC4 IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr vec<T, 4>::vec() :
    x(T(0)), y(T(0)), z(T(0)), w(T(0))
{}

template <typename T>
constexpr vec<T, 4>::vec(const vec4<T> & v) :
    x(v.x), y(v.y), z(v.z), w(v.w)
{}

template <typename T>
constexpr vec<T, 4>::vec(vec4<T> && v) :
    x(v.x), y(v.y), z(v.z), w(v.w)
{}

template <typename T>
template <typename U>
constexpr vec<T, 4>::vec(const vec1<U> & v) :
    x(T(v.x)), y(T(0)), z(T(0)), w(T(0))
{}

template <typename T>
template <typename U>
constexpr vec<T, 4>::vec(const vec2<U> & v) :
    x(T(v.x)), y(T(v.y)), z(T(0)), w(T(0))
{}

template <typename T>
template <typename U>
constexpr vec<T, 4>::vec(const vec3<U> & v) :
    x(T(v.x)), y(T(v.y)), z(T(v.z)), w(T(0))
{}

template <typename T>
template <typename U>
constexpr vec<T, 4>::vec(const vec4<U> & v) :
    x(T(v.x)), y(T(v.y)), z(T(v.z)), w(T(v.w))
{}

template <typename T>
constexpr vec<T, 4>::vec(const T & v) :
    x(v), y(v), z(v), w(v)
{}

template <typename T>
constexpr vec<T, 4>::vec(const T & v1, const T & v2, const T & v3, const T & v4) :
    x(v1), y(v2), z(v3), w(v4)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const T & v2, const T & v3, const T & v4) :
    x(v1.x), y(v2), z(v3), w(v4)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const vec1<T> & v2, const T & v3, const T & v4) :
    x(v1), y(v2.x), z(v3), w(v4)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const T & v2, const vec1<T> & v3, const T & v4) :
    x(v1), y(v2), z(v3.x), w(v4)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const T & v2, const T & v3, const vec1<T> & v4) :
    x(v1), y(v2), z(v3), w(v4.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const vec1<T> & v2, const T & v3, const T & v4) :
    x(v1.x), y(v2.x), z(v3), w(v4)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const T & v2, const vec1<T> & v3, const T & v4) :
    x(v1.x), y(v2), z(v3.x), w(v4)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const T & v2, const T & v3, const vec1<T> & v4) :
    x(v1.x), y(v2), z(v3), w(v4.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const vec1<T> & v2, const vec1<T> & v3, const T & v4) :
    x(v1), y(v2.x), z(v3.x), w(v4)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const vec1<T> & v2, const T & v3, const vec1<T> & v4) :
    x(v1), y(v2.x), z(v3), w(v4.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const T & v2, const vec1<T> & v3, const vec1<T> & v4) :
    x(v1), y(v2), z(v3.x), w(v4.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const vec1<T> & v2, const vec1<T> & v3, const T & v4) :
    x(v1.x), y(v2.x), z(v3.x), w(v4)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const vec1<T> & v2, const T & v3, const vec1<T> & v4) :
    x(v1.x), y(v2.x), z(v3), w(v4.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const T & v2, const vec1<T> & v3, const vec1<T> & v4) :
    x(v1.x), y(v2), z(v3.x), w(v4.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const vec1<T> & v2, const vec1<T> & v3, const vec1<T> & v4) :
    x(v1), y(v2.x), z(v3.x), w(v4.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const vec1<T> & v2, const vec1<T> & v3, const vec1<T> & v4) :
    x(v1.x), y(v2.x), z(v3.x), w(v4.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec2<T> & v1, const T & v2, const T & v3) :
    x(v1.x), y(v1.y), z(v2), w(v3)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec2<T> & v1, const vec1<T> & v2, const T & v3) :
    x(v1.x), y(v1.y), z(v2.x), w(v3)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec2<T> & v1, const T & v2, const vec1<T> & v3) :
    x(v1.x), y(v1.y), z(v2), w(v3.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec2<T> & v1, const vec1<T> & v2, const vec1<T> & v3) :
    x(v1.x), y(v1.y), z(v2.x), w(v3.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const vec2<T> & v2, const T & v3) :
    x(v1), y(v2.x), z(v2.y), w(v3)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const vec2<T> & v2, const T & v3) :
    x(v1.x), y(v2.x), z(v2.y), w(v3)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const vec2<T> & v2, const vec1<T> & v3) :
    x(v1), y(v2.x), z(v2.y), w(v3.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const vec2<T> & v2, const vec1<T> & v3) :
    x(v1.x), y(v2.x), z(v2.y), w(v3.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const T & v2, const vec2<T> & v3) :
    x(v1), y(v2), z(v3.x), w(v3.y)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const T & v2, const vec2<T> & v3) :
    x(v1.x), y(v2), z(v3.x), w(v3.y)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const vec1<T> & v2, const vec2<T> & v3) :
    x(v1), y(v2.x), z(v3.x), w(v3.y)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const vec1<T> & v2, const vec2<T> & v3) :
    x(v1.x), y(v2.x), z(v3.x), w(v3.y)
{}

template <typename T>
Q_CONSTEX vec<T, 4>::vec(const vec2<T> & v1, const vec2<T> & v2) :
    x(v1.x), y(v1.y), z(v2.x), w(v2.y)
{}

template <typename T>
Q_CONSTEX vec<T, 4>::vec(const vec3<T> & v1, const T & v2) :
    x(v1.x), y(v1.y), z(v1.z), w(v2)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec3<T> & v1, const vec1<T> & v2) :
    x(v1.x), y(v1.y), z(v1.z), w(v2.x)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const T & v1, const vec3<T> & v2) :
    x(v1), y(v2.x), z(v2.y), w(v2.z)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(const vec1<T> & v1, const vec3<T> & v2) :
    x(v1.x), y(v2.x), z(v2.y), w(v2.z)
{}



//------------------------------------------------------------------------------
// Assignment



template <typename T>
inline vec4<T> & vec<T, 4>::operator=(const vec4<T> & v) {
    x = v.x; y = v.y; z = v.z; w = v.w;
    return *this;
}

template <typename T>
inline vec4<T> & vec<T, 4>::operator=(vec4<T> && v) {
    x = v.x; y = v.y; z = v.z; w = v.w;
    return *this;
}

template <typename T>
inline vec4<T> & vec<T, 4>::operator=(const T & v) {
    x = v; y = v; z = v; w = v;
    return *this;
}

template <typename T>
template <int t_n>
inline vec4<T> & vec<T, 4>::operator=(const vec<T, t_n> & v) {
    if constexpr (t_n >= 1) x = v.x; if constexpr (t_n < 1) x = T(0);
    if constexpr (t_n >= 2) y = v.y; if constexpr (t_n < 2) y = T(0);
    if constexpr (t_n >= 3) z = v.z; if constexpr (t_n < 3) z = T(0);
    if constexpr (t_n >= 4) w = v.w; if constexpr (t_n < 4) w = T(0);
    return *this;
}



//------------------------------------------------------------------------------
// Access



template <typename T>
inline T & vec<T, 4>::operator[](int i) {
    return *(&x + i);
}

template <typename T>
inline const T & vec<T, 4>::operator[](int i) const {
    return *(&x + i);
}

template <typename T>
template <int t_i>
inline T & vec<T, 4>::at() {
    static_assert(t_i >= 0 && t_i <= 3, "index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
    if constexpr (t_i == 2) return z;
    if constexpr (t_i == 3) return w;
}

template <typename T>
template <int t_i>
constexpr const T & vec<T, 4>::at() const {
    static_assert(t_i >= 0 && t_i <= 3, "index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
    if constexpr (t_i == 2) return z;
    if constexpr (t_i == 3) return w;
}

template <typename T>
inline vec2<T> & vec<T, 4>::xy() {
    return *reinterpret_cast<vec2<T> *>(&x);
}

template <typename T>
inline vec2<T> & vec<T, 4>::rg() {
    return *reinterpret_cast<vec2<T> *>(&r);
}

template <typename T>
inline vec2<T> & vec<T, 4>::st() {
    return *reinterpret_cast<vec2<T> *>(&s);
}

template <typename T>
inline vec2<T> & vec<T, 4>::yz() {
    return *reinterpret_cast<vec2<T> *>(&y);
}

template <typename T>
inline vec2<T> & vec<T, 4>::gb() {
    return *reinterpret_cast<vec2<T> *>(&g);
}

template <typename T>
inline vec2<T> & vec<T, 4>::tp() {
    return *reinterpret_cast<vec2<T> *>(&t);
}

template <typename T>
inline vec2<T> & vec<T, 4>::zw() {
    return *reinterpret_cast<vec2<T> *>(&z);
}

template <typename T>
inline vec2<T> & vec<T, 4>::ba() {
    return *reinterpret_cast<vec2<T> *>(&b);
}

template <typename T>
inline vec2<T> & vec<T, 4>::pq() {
    return *reinterpret_cast<vec2<T> *>(&p);
}

template <typename T>
inline vec3<T> & vec<T, 4>::xyz() {
    return *reinterpret_cast<vec3<T> *>(&x);
}

template <typename T>
inline vec3<T> & vec<T, 4>::rgb() {
    return *reinterpret_cast<vec3<T> *>(&r);
}

template <typename T>
inline vec3<T> & vec<T, 4>::stp() {
    return *reinterpret_cast<vec3<T> *>(&s);
}

template <typename T>
inline vec3<T> & vec<T, 4>::yzw() {
    return *reinterpret_cast<vec3<T> *>(&y);
}

template <typename T>
inline vec3<T> & vec<T, 4>::gba() {
    return *reinterpret_cast<vec3<T> *>(&g);
}

template <typename T>
inline vec3<T> & vec<T, 4>::tpq() {
    return *reinterpret_cast<vec3<T> *>(&t);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::xy() const {
    return *reinterpret_cast<const vec2<T> *>(&x);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::rg() const {
    return *reinterpret_cast<const vec2<T> *>(&r);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::st() const {
    return *reinterpret_cast<const vec2<T> *>(&s);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::yz() const {
    return *reinterpret_cast<const vec2<T> *>(&y);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::gb() const {
    return *reinterpret_cast<const vec2<T> *>(&g);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::tp() const {
    return *reinterpret_cast<const vec2<T> *>(&t);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::zw() const {
    return *reinterpret_cast<const vec2<T> *>(&z);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::ba() const {
    return *reinterpret_cast<const vec2<T> *>(&b);
}

template <typename T>
inline const vec2<T> & vec<T, 4>::pq() const {
    return *reinterpret_cast<const vec2<T> *>(&p);
}

template <typename T>
inline const vec3<T> & vec<T, 4>::xyz() const {
    return *reinterpret_cast<const vec3<T> *>(&x);
}

template <typename T>
inline const vec3<T> & vec<T, 4>::yzw() const {
    return *reinterpret_cast<const vec3<T> *>(&y);
}

template <typename T>
inline const vec3<T> & vec<T, 4>::rgb() const {
    return *reinterpret_cast<const vec3<T> *>(&r);
}

template <typename T>
inline const vec3<T> & vec<T, 4>::gba() const {
    return *reinterpret_cast<const vec3<T> *>(&g);
}

template <typename T>
inline const vec3<T> & vec<T, 4>::stp() const {
    return *reinterpret_cast<const vec3<T> *>(&s);
}

template <typename T>
inline const vec3<T> & vec<T, 4>::tpq() const {
    return *reinterpret_cast<const vec3<T> *>(&t);
}



//======================================================================================================================
// SPAN IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



//------------------------------------------------------------------------------
// Constructors



template <typename T, int t_n>
constexpr span<T, t_n>::span() :
    min(),
    max()
{}

template <typename T, int t_n>
constexpr span<T, t_n>::span(const span<T, t_n> & s) :
    min(s.min),
    max(s.max)
{}

template <typename T, int t_n>
constexpr span<T, t_n>::span(span<T, t_n> && s) :
    min(s.min),
    max(s.max)
{}

template <typename T, int t_n>
template <typename U, int u_n>
constexpr span<T, t_n>::span(const span<U, u_n> & s) :
    min(s.min),
    max(s.max)
{}

template <typename T, int t_n>
constexpr span<T, t_n>::span(const vec<T, t_n> & v1, const vec<T, t_n> & v2) :
    min(v1),
    max(v2)
{}

template <typename T, int t_n>
constexpr span<T, t_n>::span(const T & v1, const T & v2) :
    min(v1),
    max(v2)
{}



//------------------------------------------------------------------------------
// Assignment



template <typename T, int t_n>
inline span<T, t_n> & span<T, t_n>::operator=(const span<T, t_n> & s) {
    min = s.min;
    max = s.max;
    return *this;
}

template <typename T, int t_n>
inline span<T, t_n> & span<T, t_n>::operator=(span<T, t_n> && s) {
    min = s.min;
    max = s.max;
    return *this;
}

template <typename T, int t_n>
template <int u_n>
inline span<T, t_n> & span<T, t_n>::operator=(const span<T, u_n> & s) {
    min = s.min;
    max = s.max;
    return *this;
}



//======================================================================================================================
// FUNCTION IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



//------------------------------------------------------------------------------
// Arithmetic Assignment



//--- pre increment ---

template <typename T, int t_n>
inline vec<T, t_n> & operator++(vec<T, t_n> & v) {
    if constexpr (t_n >= 1) ++v.x;
    if constexpr (t_n >= 2) ++v.y;
    if constexpr (t_n >= 3) ++v.z;
    if constexpr (t_n >= 4) ++v.w;
    return v;
}

//--- post increment ---

template <typename T, int t_n>
inline vec<T, t_n> operator++(vec<T, t_n> & v, int) {
    if constexpr (t_n == 1) return vec1<T>(v.x++);
    if constexpr (t_n == 2) return vec2<T>(v.x++, v.y++);
    if constexpr (t_n == 3) return vec3<T>(v.x++, v.y++, v.z++);
    if constexpr (t_n == 4) return vec4<T>(v.x++, v.y++, v.z++, v.w++);
}

//--- pre decrement ---

template <typename T, int t_n>
inline vec<T, t_n> & operator--(vec<T, t_n> & v) {
    if constexpr (t_n >= 1) --v.x;
    if constexpr (t_n >= 2) --v.y;
    if constexpr (t_n >= 3) --v.z;
    if constexpr (t_n >= 4) --v.w;
    return v;
}

//--- post decrement ---

template <typename T, int t_n>
inline vec<T, t_n> operator--(vec<T, t_n> & v, int) {
    if constexpr (t_n == 1) return vec1<T>(v.x--);
    if constexpr (t_n == 2) return vec2<T>(v.x--, v.y--);
    if constexpr (t_n == 3) return vec3<T>(v.x--, v.y--, v.z--);
    if constexpr (t_n == 4) return vec4<T>(v.x--, v.y--, v.z--, v.w--);
}

//--- add assign ---

template <typename T, int t_n>
inline vec<T, t_n> & operator+=(vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n >= 1) v1.x += v2.x;
    if constexpr (t_n >= 2) v1.y += v2.y;
    if constexpr (t_n >= 3) v1.z += v2.z;
    if constexpr (t_n >= 4) v1.w += v2.w;
    return v1;
}

template <typename T, int t_n>
inline vec<T, t_n> & operator+=(vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n >= 1) v1.x += v2;
    if constexpr (t_n >= 2) v1.y += v2;
    if constexpr (t_n >= 3) v1.z += v2;
    if constexpr (t_n >= 4) v1.w += v2;
    return v1;
}

//--- subtract assign ---

template <typename T, int t_n>
inline vec<T, t_n> & operator-=(vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n >= 1) v1.x -= v2.x;
    if constexpr (t_n >= 2) v1.y -= v2.y;
    if constexpr (t_n >= 3) v1.z -= v2.z;
    if constexpr (t_n >= 4) v1.w -= v2.w;
    return v1;
}

template <typename T, int t_n>
inline vec<T, t_n> & operator-=(vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n >= 1) v1.x -= v2;
    if constexpr (t_n >= 2) v1.y -= v2;
    if constexpr (t_n >= 3) v1.z -= v2;
    if constexpr (t_n >= 4) v1.w -= v2;
    return v1;
}

//--- multiply assign ---

template <typename T, int t_n>
inline vec<T, t_n> & operator*=(vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n >= 1) v1.x *= v2.x;
    if constexpr (t_n >= 2) v1.y *= v2.y;
    if constexpr (t_n >= 3) v1.z *= v2.z;
    if constexpr (t_n >= 4) v1.w *= v2.w;
    return v1;
}

template <typename T, int t_n>
inline vec<T, t_n> & operator*=(vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n >= 1) v1.x *= v2;
    if constexpr (t_n >= 2) v1.y *= v2;
    if constexpr (t_n >= 3) v1.z *= v2;
    if constexpr (t_n >= 4) v1.w *= v2;
    return v1;
}

//--- divide assign ---

template <typename T, int t_n>
inline vec<T, t_n> & operator/=(vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n >= 1) v1.x /= v2.x;
    if constexpr (t_n >= 2) v1.y /= v2.y;
    if constexpr (t_n >= 3) v1.z /= v2.z;
    if constexpr (t_n >= 4) v1.w /= v2.w;
    return v1;
}

template <typename T, int t_n>
inline vec<T, t_n> & operator/=(vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n > 1 && std::is_floating_point_v<T>) return v1 *= T(1.0) / v2;
    if constexpr (t_n >= 1) v1.x /= v2;
    if constexpr (t_n >= 2) v1.y /= v2;
    if constexpr (t_n >= 3) v1.z /= v2;
    if constexpr (t_n >= 4) v1.w /= v2;
    return v1;
}

//--- modulus assign ---

template <typename T, int t_n>
inline vec<T, t_n> & operator%=(vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n >= 1) v1.x = mod(v1.x, v2.x);
    if constexpr (t_n >= 2) v1.y = mod(v1.y, v2.y);
    if constexpr (t_n >= 3) v1.z = mod(v1.z, v2.z);
    if constexpr (t_n >= 4) v1.w = mod(v1.w, v2.w);
    return v1;
}

template <typename T, int t_n>
inline vec<T, t_n> & operator%=(vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n >= 1) v1.x = mod(v1.x, v2);
    if constexpr (t_n >= 2) v1.y = mod(v1.y, v2);
    if constexpr (t_n >= 3) v1.z = mod(v1.z, v2);
    if constexpr (t_n >= 4) v1.w = mod(v1.w, v2);
    return v1;
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- positive ---

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator+(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return vec1<T>(+v.x);
    if constexpr (t_n == 2) return vec2<T>(+v.x, +v.y);
    if constexpr (t_n == 3) return vec3<T>(+v.x, +v.y, +v.z);
    if constexpr (t_n == 4) return vec4<T>(+v.x, +v.y, +v.z, +v.w);
}

//--- negative ---

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator-(const vec<T, t_n> & v) {
    if constexpr (std::is_unsigned_v<T>) return v;
    if constexpr (!std::is_unsigned_v<T>) {
        if constexpr (t_n == 1) return vec1<T>(-v.x);
        if constexpr (t_n == 2) return vec2<T>(-v.x, -v.y);
        if constexpr (t_n == 3) return vec3<T>(-v.x, -v.y, -v.z);
        if constexpr (t_n == 4) return vec4<T>(-v.x, -v.y, -v.z, -v.w);
    }
}

//--- add ---

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator+(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1.x + v2.x);
    if constexpr (t_n == 2) return vec2<T>(v1.x + v2.x, v1.y + v2.y);
    if constexpr (t_n == 3) return vec3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
    if constexpr (t_n == 4) return vec4<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator+(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1.x + v2);
    if constexpr (t_n == 2) return vec2<T>(v1.x + v2, v1.y + v2);
    if constexpr (t_n == 3) return vec3<T>(v1.x + v2, v1.y + v2, v1.z + v2);
    if constexpr (t_n == 4) return vec4<T>(v1.x + v2, v1.y + v2, v1.z + v2, v1.w + v2);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator+(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1 + v2.x);
    if constexpr (t_n == 2) return vec2<T>(v1 + v2.x, v1 + v2.y);
    if constexpr (t_n == 3) return vec3<T>(v1 + v2.x, v1 + v2.y, v1 + v2.z);
    if constexpr (t_n == 4) return vec4<T>(v1 + v2.x, v1 + v2.y, v1 + v2.z, v1 + v2.w);
}

//--- subtract ---

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator-(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1.x - v2.x);
    if constexpr (t_n == 2) return vec2<T>(v1.x - v2.x, v1.y - v2.y);
    if constexpr (t_n == 3) return vec3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    if constexpr (t_n == 4) return vec4<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator-(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1.x - v2);
    if constexpr (t_n == 2) return vec2<T>(v1.x - v2, v1.y - v2);
    if constexpr (t_n == 3) return vec3<T>(v1.x - v2, v1.y - v2, v1.z - v2);
    if constexpr (t_n == 4) return vec4<T>(v1.x - v2, v1.y - v2, v1.z - v2, v1.w - v2);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator-(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1 - v2.x);
    if constexpr (t_n == 2) return vec2<T>(v1 - v2.x, v1 - v2.y);
    if constexpr (t_n == 3) return vec3<T>(v1 - v2.x, v1 - v2.y, v1 - v2.z);
    if constexpr (t_n == 4) return vec4<T>(v1 - v2.x, v1 - v2.y, v1 - v2.z, v1 - v2.w);
}

//--- multiply ---

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator*(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1.x * v2.x);
    if constexpr (t_n == 2) return vec2<T>(v1.x * v2.x, v1.y * v2.y);
    if constexpr (t_n == 3) return vec3<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
    if constexpr (t_n == 4) return vec4<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator*(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1.x * v2);
    if constexpr (t_n == 2) return vec2<T>(v1.x * v2, v1.y * v2);
    if constexpr (t_n == 3) return vec3<T>(v1.x * v2, v1.y * v2, v1.z * v2);
    if constexpr (t_n == 4) return vec4<T>(v1.x * v2, v1.y * v2, v1.z * v2, v1.w * v2);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator*(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1 * v2.x);
    if constexpr (t_n == 2) return vec2<T>(v1 * v2.x, v1 * v2.y);
    if constexpr (t_n == 3) return vec3<T>(v1 * v2.x, v1 * v2.y, v1 * v2.z);
    if constexpr (t_n == 4) return vec4<T>(v1 * v2.x, v1 * v2.y, v1 * v2.z, v1 * v2.w);
}

//--- divide ---

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator/(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1.x / v2.x);
    if constexpr (t_n == 2) return vec2<T>(v1.x / v2.x, v1.y / v2.y);
    if constexpr (t_n == 3) return vec3<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
    if constexpr (t_n == 4) return vec4<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator/(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n > 1 && std::is_floating_point_v<T>) {
        return v1 * (T(1.0) / v2);
    }
    if constexpr (t_n == 1) return vec1<T>(v1.x / v2);
    if constexpr (t_n == 2) return vec2<T>(v1.x / v2, v1.y / v2);
    if constexpr (t_n == 3) return vec3<T>(v1.x / v2, v1.y / v2, v1.z / v2);
    if constexpr (t_n == 4) return vec4<T>(v1.x / v2, v1.y / v2, v1.z / v2, v1.w / v2);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator/(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(v1 / v2.x);
    if constexpr (t_n == 2) return vec2<T>(v1 / v2.x, v1 / v2.y);
    if constexpr (t_n == 3) return vec3<T>(v1 / v2.x, v1 / v2.y, v1 / v2.z);
    if constexpr (t_n == 4) return vec4<T>(v1 / v2.x, v1 / v2.y, v1 / v2.z, v1 / v2.w);
}

//--- modulus ---

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator%(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(mod(v1.x, v2.x));
    if constexpr (t_n == 2) return vec2<T>(mod(v1.x, v2.x), mod(v1.y, v2.y));
    if constexpr (t_n == 3) return vec3<T>(mod(v1.x, v2.x), mod(v1.y, v2.y), mod(v1.z, v2.z));
    if constexpr (t_n == 4) return vec4<T>(mod(v1.x, v2.x), mod(v1.y, v2.y), mod(v1.z, v2.z), mod(v1.w, v2.w));
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator%(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return vec1<T>(mod(v1.x, v2));
    if constexpr (t_n == 2) return vec2<T>(mod(v1.x, v2), mod(v1.y, v2));
    if constexpr (t_n == 3) return vec3<T>(mod(v1.x, v2), mod(v1.y, v2), mod(v1.z, v2));
    if constexpr (t_n == 4) return vec4<T>(mod(v1.x, v2), mod(v1.y, v2), mod(v1.z, v2), mod(v1.w, v2));
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator%(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(mod(v1, v2.x));
    if constexpr (t_n == 2) return vec2<T>(mod(v1, v2.x), mod(v1, v2.y));
    if constexpr (t_n == 3) return vec3<T>(mod(v1, v2.x), mod(v1, v2.y), mod(v1, v2.z));
    if constexpr (t_n == 4) return vec4<T>(mod(v1, v2.x), mod(v1, v2.y), mod(v1, v2.z), mod(v1, v2.w));
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T, int t_n>
Q_CX_ABLE bool operator==(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return v1.x == v2.x;
    if constexpr (t_n == 2) return v1.x == v2.x && v1.y == v2.y;
    if constexpr (t_n == 3) return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
    if constexpr (t_n == 4) return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator==(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x == v2);
    if constexpr (t_n == 2) return bvec2(v1.x == v2, v1.y == v2);
    if constexpr (t_n == 3) return bvec3(v1.x == v2, v1.y == v2, v1.z == v2);
    if constexpr (t_n == 4) return bvec4(v1.x == v2, v1.y == v2, v1.z == v2, v1.w == v2);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator==(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1 == v2.x);
    if constexpr (t_n == 2) return bvec2(v1 == v2.x, v1 == v2.y);
    if constexpr (t_n == 3) return bvec3(v1 == v2.x, v1 == v2.y, v1 == v2.z);
    if constexpr (t_n == 4) return bvec4(v1 == v2.x, v1 == v2.y, v1 == v2.z, v1 == v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE bool operator==(const span<T, t_n> & s1, const span<T, t_n> & s2) {
    return s1.min == s2.min && s1.max == s2.max;
}

//--- not equal to ---

template <typename T, int t_n>
Q_CX_ABLE bool operator!=(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return v1.x != v2.x;
    if constexpr (t_n == 2) return v1.x != v2.x || v1.y != v2.y;
    if constexpr (t_n == 3) return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
    if constexpr (t_n == 4) return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z || v1.w != v2.w;
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator!=(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x != v2);
    if constexpr (t_n == 2) return bvec2(v1.x != v2, v1.y != v2);
    if constexpr (t_n == 3) return bvec3(v1.x != v2, v1.y != v2, v1.z != v2);
    if constexpr (t_n == 4) return bvec4(v1.x != v2, v1.y != v2, v1.z != v2, v1.w != v2);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator!=(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1 != v2.x);
    if constexpr (t_n == 2) return bvec2(v1 != v2.x, v1 != v2.y);
    if constexpr (t_n == 3) return bvec3(v1 != v2.x, v1 != v2.y, v1 != v2.z);
    if constexpr (t_n == 4) return bvec4(v1 != v2.x, v1 != v2.y, v1 != v2.z, v1 != v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE bool operator!=(const span<T, t_n> & s1, const span<T, t_n> & s2) {
    return s1.min != s2.min || s1.max != s2.max;
}

//--- less than ---

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator<(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x < v2.x);
    if constexpr (t_n == 2) return bvec2(v1.x < v2.x, v1.y < v2.y);
    if constexpr (t_n == 3) return bvec3(v1.x < v2.x, v1.y < v2.y, v1.z < v2.z);
    if constexpr (t_n == 4) return bvec4(v1.x < v2.x, v1.y < v2.y, v1.z < v2.z, v1.w < v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator<(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x < v2);
    if constexpr (t_n == 2) return bvec2(v1.x < v2, v1.y < v2);
    if constexpr (t_n == 3) return bvec3(v1.x < v2, v1.y < v2, v1.z < v2);
    if constexpr (t_n == 4) return bvec4(v1.x < v2, v1.y < v2, v1.z < v2, v1.w < v2);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator<(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1 < v2.x);
    if constexpr (t_n == 2) return bvec2(v1 < v2.x, v1 < v2.y);
    if constexpr (t_n == 3) return bvec3(v1 < v2.x, v1 < v2.y, v1 < v2.z);
    if constexpr (t_n == 4) return bvec4(v1 < v2.x, v1 < v2.y, v1 < v2.z, v1 < v2.w);
}

//--- greater than ---

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator>(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x > v2.x);
    if constexpr (t_n == 2) return bvec2(v1.x > v2.x, v1.y > v2.y);
    if constexpr (t_n == 3) return bvec3(v1.x > v2.x, v1.y > v2.y, v1.z > v2.z);
    if constexpr (t_n == 4) return bvec4(v1.x > v2.x, v1.y > v2.y, v1.z > v2.z, v1.w > v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator>(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x > v2);
    if constexpr (t_n == 2) return bvec2(v1.x > v2, v1.y > v2);
    if constexpr (t_n == 3) return bvec3(v1.x > v2, v1.y > v2, v1.z > v2);
    if constexpr (t_n == 4) return bvec4(v1.x > v2, v1.y > v2, v1.z > v2, v1.w > v2);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator>(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1 > v2.x);
    if constexpr (t_n == 2) return bvec2(v1 > v2.x, v1 > v2.y);
    if constexpr (t_n == 3) return bvec3(v1 > v2.x, v1 > v2.y, v1 > v2.z);
    if constexpr (t_n == 4) return bvec4(v1 > v2.x, v1 > v2.y, v1 > v2.z, v1 > v2.w);
}

//--- less than or equal to ---

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator<=(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x <= v2.x);
    if constexpr (t_n == 2) return bvec2(v1.x <= v2.x, v1.y <= v2.y);
    if constexpr (t_n == 3) return bvec3(v1.x <= v2.x, v1.y <= v2.y, v1.z <= v2.z);
    if constexpr (t_n == 4) return bvec4(v1.x <= v2.x, v1.y <= v2.y, v1.z <= v2.z, v1.w <= v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator<=(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x <= v2);
    if constexpr (t_n == 2) return bvec2(v1.x <= v2, v1.y <= v2);
    if constexpr (t_n == 3) return bvec3(v1.x <= v2, v1.y <= v2, v1.z <= v2);
    if constexpr (t_n == 4) return bvec4(v1.x <= v2, v1.y <= v2, v1.z <= v2, v1.w <= v2);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator<=(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1 <= v2.x);
    if constexpr (t_n == 2) return bvec2(v1 <= v2.x, v1 <= v2.y);
    if constexpr (t_n == 3) return bvec3(v1 <= v2.x, v1 <= v2.y, v1 <= v2.z);
    if constexpr (t_n == 4) return bvec4(v1 <= v2.x, v1 <= v2.y, v1 <= v2.z, v1 <= v2.w);
}

//--- greater than or equal to ---

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator>=(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x >= v2.x);
    if constexpr (t_n == 2) return bvec2(v1.x >= v2.x, v1.y >= v2.y);
    if constexpr (t_n == 3) return bvec3(v1.x >= v2.x, v1.y >= v2.y, v1.z >= v2.z);
    if constexpr (t_n == 4) return bvec4(v1.x >= v2.x, v1.y >= v2.y, v1.z >= v2.z, v1.w >= v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator>=(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x >= v2);
    if constexpr (t_n == 2) return bvec2(v1.x >= v2, v1.y >= v2);
    if constexpr (t_n == 3) return bvec3(v1.x >= v2, v1.y >= v2, v1.z >= v2);
    if constexpr (t_n == 4) return bvec4(v1.x >= v2, v1.y >= v2, v1.z >= v2, v1.w >= v2);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator>=(const T & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1 >= v2.x);
    if constexpr (t_n == 2) return bvec2(v1 >= v2.x, v1 >= v2.y);
    if constexpr (t_n == 3) return bvec3(v1 >= v2.x, v1 >= v2.y, v1 >= v2.z);
    if constexpr (t_n == 4) return bvec4(v1 >= v2.x, v1 >= v2.y, v1 >= v2.z, v1 >= v2.w);
}



//------------------------------------------------------------------------------
// Logic Operators



template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator&&(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x && v2.x);
    if constexpr (t_n == 2) return bvec2(v1.x && v2.x, v1.y && v2.y);
    if constexpr (t_n == 3) return bvec3(v1.x && v2.x, v1.y && v2.y, v1.z && v2.z);
    if constexpr (t_n == 4) return bvec4(v1.x && v2.x, v1.y && v2.y, v1.z && v2.z, v1.w && v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator||(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return bvec1(v1.x || v2.x);
    if constexpr (t_n == 2) return bvec2(v1.x || v2.x, v1.y || v2.y);
    if constexpr (t_n == 3) return bvec3(v1.x || v2.x, v1.y || v2.y, v1.z || v2.z);
    if constexpr (t_n == 4) return bvec4(v1.x || v2.x, v1.y || v2.y, v1.z || v2.z, v1.w || v2.w);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator!(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return bvec1(!v.x);
    if constexpr (t_n == 2) return bvec2(!v.x, !v.y);
    if constexpr (t_n == 3) return bvec3(!v.x, !v.y, !v.z);
    if constexpr (t_n == 4) return bvec4(!v.x, !v.y, !v.z, !v.w);
}



//------------------------------------------------------------------------------
// Condensation



template <typename T, int t_n>
Q_CX_ABLE T sum(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return v.x;
    if constexpr (t_n == 2) return v.x + v.y;
    if constexpr (t_n == 3) return v.x + v.y + v.z;
    if constexpr (t_n == 4) return v.x + v.y + v.z + v.w;
}

template <typename T, int t_n>
Q_CX_ABLE T product(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return v.x;
    if constexpr (t_n == 2) return v.x * v.y;
    if constexpr (t_n == 3) return v.x * v.y * v.z;
    if constexpr (t_n == 4) return v.x * v.y * v.z * v.w;
}

template <typename T, int t_n>
Q_CX_ABLE bool conjunct(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return v.x;
    if constexpr (t_n == 2) return v.x && v.y;
    if constexpr (t_n == 3) return v.x && v.y && v.z;
    if constexpr (t_n == 4) return v.x && v.y && v.z && v.w;
}

template <typename T, int t_n>
Q_CX_ABLE bool disjunct(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return v.x;
    if constexpr (t_n == 2) return v.x || v.y;
    if constexpr (t_n == 3) return v.x || v.y || v.z;
    if constexpr (t_n == 4) return v.x || v.y || v.z || v.w;
}



//------------------------------------------------------------------------------
// Other



template <typename T, int t_n>
Q_CX_ABLE const T & min(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return v.x;
    if constexpr (t_n == 2) return min(v.x, v.y);
    if constexpr (t_n == 3) return min(v.x, v.y, v.z);
    if constexpr (t_n == 4) return min(v.x, v.y, v.z, v.w);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> min(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(min(v1.x, v2.x));
    if constexpr (t_n == 2) return vec2<T>(min(v1.x, v2.x), min(v1.y, v2.y));
    if constexpr (t_n == 3) return vec3<T>(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z));
    if constexpr (t_n == 4) return vec4<T>(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z), min(v1.w, v2.w));
}

template <typename T, int t_n, typename... Ts>
Q_CX_ABLE vec<T, t_n> min(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<Ts, t_n> &... rest) {
    return min(min(v1, v2), rest...);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> min(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return vec1<T>(min(v1.x, v2));
    if constexpr (t_n == 2) return vec2<T>(min(v1.x, v2), min(v1.y, v2));
    if constexpr (t_n == 3) return vec3<T>(min(v1.x, v2), min(v1.y, v2), min(v1.z, v2));
    if constexpr (t_n == 4) return vec4<T>(min(v1.x, v2), min(v1.y, v2), min(v1.z, v2), min(v1.w, v2));
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> min(const T & v1, const vec<T, t_n> & v2) {
    return min(v2, v1);
}

template <typename T, int t_n>
Q_CX_ABLE const T & max(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return v.x;
    if constexpr (t_n == 2) return max(v.x, v.y);
    if constexpr (t_n == 3) return max(v.x, v.y, v.z);
    if constexpr (t_n == 4) return max(v.x, v.y, v.z, v.w);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> max(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 1) return vec1<T>(max(v1.x, v2.x));
    if constexpr (t_n == 2) return vec2<T>(max(v1.x, v2.x), max(v1.y, v2.y));
    if constexpr (t_n == 3) return vec3<T>(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z));
    if constexpr (t_n == 4) return vec4<T>(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z), max(v1.w, v2.w));
}

template <typename T, int t_n, typename... Ts>
Q_CX_ABLE vec<T, t_n> max(const vec<T, t_n> & v1, const vec<T, t_n> & v2, const vec<Ts, t_n> &... rest) {
    return max(max(v1, v2), rest...);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> max(const vec<T, t_n> & v1, const T & v2) {
    if constexpr (t_n == 1) return vec1<T>(max(v1.x, v2));
    if constexpr (t_n == 2) return vec2<T>(max(v1.x, v2), max(v1.y, v2));
    if constexpr (t_n == 3) return vec3<T>(max(v1.x, v2), max(v1.y, v2), max(v1.z, v2));
    if constexpr (t_n == 4) return vec4<T>(max(v1.x, v2), max(v1.y, v2), max(v1.z, v2), max(v1.w, v2));
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> max(const T & v1, const vec<T, t_n> & v2) {
    return max(v2, v1);
}

template <typename T, int t_n>
Q_CX_ABLE std::pair<const T &, const T &> minmax(const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return minmax(v.x);
    if constexpr (t_n == 2) return minmax(v.x, v.y);
    if constexpr (t_n == 3) return minmax(v.x, v.y, v.z);
    if constexpr (t_n == 4) return minmax(v.x, v.y, v.z, v.w);
}



}