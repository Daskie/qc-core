namespace qc {

//======================================================================================================================
// VEC2 IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================

//------------------------------------------------------------------------------
// Constructors

template <typename T>
constexpr vec<T, 2>::vec() noexcept :
    x(T(0)), y(T(0))
{}

template <typename T>
constexpr vec<T, 2>::vec(T v) noexcept :
    x(v), y(v)
{}

template <typename T>
template <typename U>
constexpr vec<T, 2>::vec(const U & v) noexcept :
    x(T(v)), y(T(v))
{}

template <typename T>
template <typename U>
constexpr vec<T, 2>::vec(const vec2<U> & v) noexcept :
    x(T(v.x)), y(T(v.y))
{}

template <typename T>
template <typename U>
constexpr vec<T, 2>::vec(const vec3<U> & v) noexcept :
    x(T(v.x)), y(T(v.y))
{}

template <typename T>
template <typename U>
constexpr vec<T, 2>::vec(const vec4<U> & v) noexcept :
    x(T(v.x)), y(T(v.y))
{}

template <typename T>
constexpr vec<T, 2>::vec(T v1, T v2) noexcept :
    x(v1), y(v2)
{}

//------------------------------------------------------------------------------
// Assignment

template <typename T>
inline vec2<T> & vec<T, 2>::operator=(T v) noexcept {
    x = v; y = v;
    return *this;
}

template <typename T>
template <int t_n>
inline vec2<T> & vec<T, 2>::operator=(const vec<T, t_n> & v) noexcept {
    if constexpr (t_n >= 1) x = v.x; else x = T(0);
    if constexpr (t_n >= 2) y = v.y; else y = T(0);
    return *this;
}

//------------------------------------------------------------------------------
// Access

template <typename T>
template <int t_i>
inline T & vec<T, 2>::at() noexcept {
    static_assert(t_i >= 0 && t_i <= 1, "Index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
}

template <typename T>
template <int t_i>
constexpr T vec<T, 2>::at() const noexcept {
    static_assert(t_i >= 0 && t_i <= 1, "Index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
}

template <typename T>
inline T & vec<T, 2>::operator[](int i) {
    return *(&x + i);
}

template <typename T>
inline T vec<T, 2>::operator[](int i) const {
    return *(&x + i);
}

//======================================================================================================================
// VEC3 IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================

//------------------------------------------------------------------------------
// Constructors

template <typename T>
constexpr vec<T, 3>::vec() noexcept :
    x(T(0)), y(T(0)), z(T(0))
{}

template <typename T>
constexpr vec<T, 3>::vec(T v) noexcept :
    x(v), y(v), z(v)
{}

template <typename T>
template <typename U>
constexpr vec<T, 3>::vec(const U & v) noexcept :
    x(T(v)), y(T(v)), z(T(v))
{}

template <typename T>
template <typename U>
constexpr vec<T, 3>::vec(const vec2<U> & v) noexcept :
    x(T(v.x)), y(T(v.y)), z()
{}

template <typename T>
template <typename U>
constexpr vec<T, 3>::vec(const vec3<U> & v) noexcept :
    x(T(v.x)), y(T(v.y)), z(T(v.z))
{}

template <typename T>
template <typename U>
constexpr vec<T, 3>::vec(const vec4<U> & v) noexcept :
    x(T(v.x)), y(T(v.y)), z(T(v.z))
{}

template <typename T>
constexpr vec<T, 3>::vec(T v1, T v2, T v3) noexcept :
    x(v1), y(v2), z(v3)
{}

template <typename T>
Q_CONSTEX vec<T, 3>::vec(const vec2<T> & v1, T v2) noexcept :
    x(v1.x), y(v1.y), z(v2)
{}

template <typename T>
Q_CX_ABLE vec<T, 3>::vec(T v1, const vec2<T> & v2) noexcept :
    x(v1), y(v2.x), z(v2.y)
{}

//------------------------------------------------------------------------------
// Assignment

template <typename T>
inline vec3<T> & vec<T, 3>::operator=(T v) noexcept {
    x = v; y = v; z = v;
    return *this;
}

template <typename T>
template <int t_n>
inline vec3<T> & vec<T, 3>::operator=(const vec<T, t_n> & v) noexcept {
    if constexpr (t_n >= 1) x = v.x; else x = T(0);
    if constexpr (t_n >= 2) y = v.y; else y = T(0);
    if constexpr (t_n >= 3) z = v.z; else z = T(0);
    return *this;
}

//------------------------------------------------------------------------------
// Access

template <typename T>
template <int t_i>
inline T & vec<T, 3>::at() noexcept {
    static_assert(t_i >= 0 && t_i <= 2, "Index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
    if constexpr (t_i == 2) return z;
}

template <typename T>
template <int t_i>
constexpr T vec<T, 3>::at() const noexcept {
    static_assert(t_i >= 0 && t_i <= 2, "Index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
    if constexpr (t_i == 2) return z;
}

template <typename T>
inline T & vec<T, 3>::operator[](int i) {
    return *(&x + i);
}

template <typename T>
inline T vec<T, 3>::operator[](int i) const {
    return *(&x + i);
}

template <typename T>
inline vec2<T> & vec<T, 3>::xy() noexcept {
    return reinterpret_cast<vec2<T> &>(x);
}

template <typename T>
Q_CX_ABLE const vec2<T> & vec<T, 3>::xy() const noexcept {
    return reinterpret_cast<const vec2<T> &>(x);
}

template <typename T>
inline vec2<T> & vec<T, 3>::yz() noexcept {
    return reinterpret_cast<vec2<T> &>(y);
}

template <typename T>
Q_CX_ABLE const vec2<T> & vec<T, 3>::yz() const noexcept {
    return reinterpret_cast<const vec2<T> &>(y);
}

//======================================================================================================================
// VEC4 IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================

//------------------------------------------------------------------------------
// Constructors

template <typename T>
constexpr vec<T, 4>::vec() noexcept :
    x(T(0)), y(T(0)), z(T(0)), w(T(0))
{}

template <typename T>
constexpr vec<T, 4>::vec(T v) noexcept :
    x(v), y(v), z(v), w(v)
{}

template <typename T>
template <typename U>
constexpr vec<T, 4>::vec(const U & v) noexcept :
    x(T(v)), y(T(v)), z(T(v)), w(T(v))
{}

template <typename T>
template <typename U>
constexpr vec<T, 4>::vec(const vec2<U> & v) noexcept :
    x(T(v.x)), y(T(v.y)), z(), w()
{}

template <typename T>
template <typename U>
constexpr vec<T, 4>::vec(const vec3<U> & v) noexcept :
    x(T(v.x)), y(T(v.y)), z(T(v.z)), w()
{}

template <typename T>
template <typename U>
constexpr vec<T, 4>::vec(const vec4<U> & v) noexcept :
    x(T(v.x)), y(T(v.y)), z(T(v.z)), w(T(v.w))
{}

template <typename T>
constexpr vec<T, 4>::vec(T v1, T v2, T v3, T v4) noexcept :
    x(v1), y(v2), z(v3), w(v4)
{}

template <typename T>
Q_CONSTEX vec<T, 4>::vec(const vec2<T> & v1, T v2, T v3) noexcept :
    x(v1.x), y(v1.y), z(v2), w(v3)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(T v1, const vec2<T> & v2, T v3) noexcept :
    x(v1), y(v2.x), z(v2.y), w(v3)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(T v1, T v2, const vec2<T> & v3) noexcept :
    x(v1), y(v2), z(v3.x), w(v3.y)
{}

template <typename T>
Q_CONSTEX vec<T, 4>::vec(const vec2<T> & v1, const vec2<T> & v2) noexcept :
    x(v1.x), y(v1.y), z(v2.x), w(v2.y)
{}

template <typename T>
Q_CONSTEX vec<T, 4>::vec(const vec3<T> & v1, T v2) noexcept :
    x(v1.x), y(v1.y), z(v1.z), w(v2)
{}

template <typename T>
Q_CX_ABLE vec<T, 4>::vec(T v1, const vec3<T> & v2) noexcept :
    x(v1), y(v2.x), z(v2.y), w(v2.z)
{}

//------------------------------------------------------------------------------
// Assignment

template <typename T>
inline vec4<T> & vec<T, 4>::operator=(T v) noexcept {
    x = v; y = v; z = v; w = v;
    return *this;
}

template <typename T>
template <int t_n>
inline vec4<T> & vec<T, 4>::operator=(const vec<T, t_n> & v) noexcept {
    if constexpr (t_n >= 1) x = v.x; else x = T(0);
    if constexpr (t_n >= 2) y = v.y; else y = T(0);
    if constexpr (t_n >= 3) z = v.z; else z = T(0);
    if constexpr (t_n >= 4) w = v.w; else w = T(0);
    return *this;
}

//------------------------------------------------------------------------------
// Access

template <typename T>
template <int t_i>
inline T & vec<T, 4>::at() noexcept {
    static_assert(t_i >= 0 && t_i <= 3, "Index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
    if constexpr (t_i == 2) return z;
    if constexpr (t_i == 3) return w;
}

template <typename T>
template <int t_i>
constexpr T vec<T, 4>::at() const noexcept {
    static_assert(t_i >= 0 && t_i <= 3, "Index out of bounds");
    if constexpr (t_i == 0) return x;
    if constexpr (t_i == 1) return y;
    if constexpr (t_i == 2) return z;
    if constexpr (t_i == 3) return w;
}

template <typename T>
inline T & vec<T, 4>::operator[](int i) {
    return *(&x + i);
}

template <typename T>
inline T vec<T, 4>::operator[](int i) const {
    return *(&x + i);
}

template <typename T>
inline vec2<T> & vec<T, 4>::xy() noexcept {
    return reinterpret_cast<vec2<T> &>(x);
}

template <typename T>
Q_CX_ABLE const vec2<T> & vec<T, 4>::xy() const noexcept {
    return reinterpret_cast<const vec2<T> &>(x);
}

template <typename T>
inline vec2<T> & vec<T, 4>::yz() noexcept {
    return reinterpret_cast<vec2<T> &>(y);
}

template <typename T>
Q_CX_ABLE const vec2<T> & vec<T, 4>::yz() const noexcept {
    return reinterpret_cast<const vec2<T> &>(y);
}

template <typename T>
inline vec2<T> & vec<T, 4>::zw() noexcept {
    return reinterpret_cast<vec2<T> &>(z);
}

template <typename T>
Q_CX_ABLE const vec2<T> & vec<T, 4>::zw() const noexcept {
    return reinterpret_cast<const vec2<T> &>(z);
}

template <typename T>
inline vec3<T> & vec<T, 4>::xyz() noexcept {
    return reinterpret_cast<vec3<T> &>(x);
}

template <typename T>
Q_CX_ABLE const vec3<T> & vec<T, 4>::xyz() const noexcept {
    return reinterpret_cast<const vec3<T> &>(x);
}

template <typename T>
inline vec3<T> & vec<T, 4>::yzw() noexcept {
    return reinterpret_cast<vec3<T> &>(y);
}

template <typename T>
Q_CX_ABLE const vec3<T> & vec<T, 4>::yzw() const noexcept {
    return reinterpret_cast<const vec3<T> &>(y);
}

//======================================================================================================================
// SPAN IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================

//------------------------------------------------------------------------------
// Constructors

template <typename T, int t_n>
constexpr span<T, t_n>::span() noexcept :
    min(),
    max()
{}

namespace detail {
    template <typename T, int t_n, typename U, int t_m> constexpr span_value_t<T, t_n> get_span_val(const span_value_t<U, t_m> & v) {
        if constexpr (t_n == 1 && t_m > 1) return span_value_t<T, t_n>(v.x);
        else return span_value_t<T, t_n>(v);
    }
}

template <typename T, int t_n>
template <typename U, int t_m>
constexpr span<T, t_n>::span(const span<U, t_m> & v) noexcept :
    min(detail::get_span_val<T, t_n, U, t_m>(v.min)),
    max(detail::get_span_val<T, t_n, U, t_m>(v.max))
{}

template <typename T, int t_n>
constexpr span<T, t_n>::span(const V & v1, const V & v2) noexcept :
    min(v1),
    max(v2)
{}

template <typename T, int t_n>
template <typename>
constexpr span<T, t_n>::span(T v1, T v2) noexcept :
    min(v1),
    max(v2)
{}

template <typename T, int t_n>
template <typename>
Q_CONSTEX span<T, t_n>::span(const span1<T> & v1, const span1<T> & v2) noexcept :
    min(v1.min, v2.min),
    max(v1.max, v2.max)
{}

template <typename T, int t_n>
template <typename>
Q_CONSTEX span<T, t_n>::span(const span1<T> & v1, const span1<T> & v2, const span1<T> & v3) noexcept :
    min(v1.min, v2.min, v3.min),
    max(v1.max, v2.max, v3.max)
{}

template <typename T, int t_n>
template <typename>
Q_CX_ABLE span<T, t_n>::span(const span2<T> & v1, const span1<T> & v2) noexcept :
    min(v1.min, v2.min),
    max(v1.max, v2.max)
{}

template <typename T, int t_n>
template <typename>
Q_CX_ABLE span<T, t_n>::span(const span1<T> & v1, const span2<T> & v2) noexcept :
    min(v1.min, v2.min),
    max(v1.max, v2.max)
{}

template <typename T, int t_n>
template <typename>
Q_CONSTEX span<T, t_n>::span(const span1<T> & v1, const span1<T> & v2, const span1<T> & v3, const span1<T> & v4) noexcept :
    min(v1.min, v2.min, v3.min, v4.min),
    max(v1.max, v2.max, v3.max, v4.max)
{}

template <typename T, int t_n>
template <typename>
Q_CX_ABLE span<T, t_n>::span(const span2<T> & v1, const span1<T> & v2, const span1<T> & v3) noexcept :
    min(v1.min, v2.min, v3.min),
    max(v1.max, v2.max, v3.max)
{}

template <typename T, int t_n>
template <typename>
Q_CX_ABLE span<T, t_n>::span(const span1<T> & v1, const span2<T> & v2, const span1<T> & v3) noexcept :
    min(v1.min, v2.min, v3.min),
    max(v1.max, v2.max, v3.max)
{}

template <typename T, int t_n>
template <typename>
Q_CX_ABLE span<T, t_n>::span(const span1<T> & v1, const span1<T> & v2, const span2<T> & v3) noexcept :
    min(v1.min, v2.min, v3.min),
    max(v1.max, v2.max, v3.max)
{}

template <typename T, int t_n>
template <typename>
Q_CX_ABLE span<T, t_n>::span(const span2<T> & v1, const span2<T> & v2) noexcept :
    min(v1.min, v2.min),
    max(v1.max, v2.max)
{}

template <typename T, int t_n>
template <typename>
Q_CX_ABLE span<T, t_n>::span(const span3<T> & v1, const span1<T> & v2) noexcept :
    min(v1.min, v2.min),
    max(v1.max, v2.max)
{}

template <typename T, int t_n>
template <typename>
Q_CX_ABLE span<T, t_n>::span(const span1<T> & v1, const span3<T> & v2) noexcept :
    min(v1.min, v2.min),
    max(v1.max, v2.max)
{}

//------------------------------------------------------------------------------
// Assignment

template <typename T, int t_n>
template <int t_m>
inline span<T, t_n> & span<T, t_n>::operator=(const span<T, t_m> & v) noexcept {
    min = v.min;
    max = v.max;
    return *this;
}

//------------------------------------------------------------------------------
// Other

template <typename T, int t_n>
template <typename>
Q_CONSTEX span1<T> span<T, t_n>::x() const noexcept {
    return {min.x, max.x};
}

template <typename T, int t_n>
template <typename>
Q_CONSTEX span1<T> span<T, t_n>::y() const noexcept {
    return {min.y, max.y};
}

template <typename T, int t_n>
template <typename>
Q_CONSTEX span1<T> span<T, t_n>::z() const noexcept {
    return {min.z, max.z};
}

template <typename T, int t_n>
template <typename>
Q_CONSTEX span1<T> span<T, t_n>::w() const noexcept {
    return {min.w, max.w};
}

template <typename T, int t_n>
template <typename>
Q_CX_ABLE span2<T> span<T, t_n>::xy() const noexcept {
    return {min.xy(), max.xy()};
}

template <typename T, int t_n>
template <typename>
Q_CX_ABLE span2<T> span<T, t_n>::yz() const noexcept {
    return {min.yz(), max.yz()};
}

template <typename T, int t_n>
template <typename>
Q_CX_ABLE span2<T> span<T, t_n>::zw() const noexcept {
    return {min.zw(), max.zw()};
}

template <typename T, int t_n>
template <typename>
Q_CX_ABLE span3<T> span<T, t_n>::xyz() const noexcept {
    return {min.xyz(), max.xyz()};
}

template <typename T, int t_n>
template <typename>
Q_CX_ABLE span3<T> span<T, t_n>::yzw() const noexcept {
    return {min.yzw(), max.yzw()};
}

template <typename T, int t_n>
Q_CX_ABLE auto span<T, t_n>::size() const noexcept -> V {
    return max - min;
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
    vec<T, t_n> temp(v);
    ++v;
    return temp;
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
    vec<T, t_n> temp(v);
    --v;
    return temp;
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
inline vec<T, t_n> & operator+=(vec<T, t_n> & v1, T v2) {
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
inline vec<T, t_n> & operator-=(vec<T, t_n> & v1, T v2) {
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
inline vec<T, t_n> & operator*=(vec<T, t_n> & v1, T v2) {
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
inline vec<T, t_n> & operator/=(vec<T, t_n> & v1, T v2) {
    if constexpr (t_n > 1 && is_floating_point_v<T>) return v1 *= T(1.0) / v2;
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
inline vec<T, t_n> & operator%=(vec<T, t_n> & v1, T v2) {
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
    return v;
}

//--- negative ---

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator-(const vec<T, t_n> & v) {
    if constexpr (is_unsigned_v<T>) return v;
    if constexpr (!is_unsigned_v<T>) {
        if constexpr (t_n == 2) return {-v.x, -v.y};
        if constexpr (t_n == 3) return {-v.x, -v.y, -v.z};
        if constexpr (t_n == 4) return {-v.x, -v.y, -v.z, -v.w};
    }
}

//--- add ---

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator+(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {T(v1.x + v2.x), T(v1.y + v2.y)};
    if constexpr (t_n == 3) return {T(v1.x + v2.x), T(v1.y + v2.y), T(v1.z + v2.z)};
    if constexpr (t_n == 4) return {T(v1.x + v2.x), T(v1.y + v2.y), T(v1.z + v2.z), T(v1.w + v2.w)};
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator+(const vec<T, t_n> & v1, T v2) {
    if constexpr (t_n == 2) return {T(v1.x + v2), T(v1.y + v2)};
    if constexpr (t_n == 3) return {T(v1.x + v2), T(v1.y + v2), T(v1.z + v2)};
    if constexpr (t_n == 4) return {T(v1.x + v2), T(v1.y + v2), T(v1.z + v2), T(v1.w + v2)};
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator+(T v1, const vec<T, t_n> & v2) {
    return v2 + v1;
}

template <typename T, int t_n>
Q_CX_ABLE span<T, t_n> operator+(const span<T, t_n> & v1, const detail::span_value_t<T, t_n> & v2) {
    if constexpr (t_n == 1) return {T(v1.min + v2), T(v1.max + v2)};
    else return {v1.min + v2, v1.max + v2};
}

template <typename T, int t_n>
Q_CX_ABLE span<T, t_n> operator+(const detail::span_value_t<T, t_n> & v1, const span<T, t_n> & v2) {
    return v2 + v1;
}

//--- subtract ---

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator-(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {T(v1.x - v2.x), T(v1.y - v2.y)};
    if constexpr (t_n == 3) return {T(v1.x - v2.x), T(v1.y - v2.y), T(v1.z - v2.z)};
    if constexpr (t_n == 4) return {T(v1.x - v2.x), T(v1.y - v2.y), T(v1.z - v2.z), T(v1.w - v2.w)};
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator-(const vec<T, t_n> & v1, T v2) {
    if constexpr (t_n == 2) return {T(v1.x - v2), T(v1.y - v2)};
    if constexpr (t_n == 3) return {T(v1.x - v2), T(v1.y - v2), T(v1.z - v2)};
    if constexpr (t_n == 4) return {T(v1.x - v2), T(v1.y - v2), T(v1.z - v2), T(v1.w - v2)};
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator-(T v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {T(v1 - v2.x), T(v1 - v2.y)};
    if constexpr (t_n == 3) return {T(v1 - v2.x), T(v1 - v2.y), T(v1 - v2.z)};
    if constexpr (t_n == 4) return {T(v1 - v2.x), T(v1 - v2.y), T(v1 - v2.z), T(v1 - v2.w)};
}

template <typename T, int t_n>
Q_CX_ABLE span<T, t_n> operator-(const span<T, t_n> & v1, const detail::span_value_t<T, t_n> & v2) {
    if constexpr (t_n == 1) return {T(v1.min - v2), T(v1.max - v2)};
    else return {v1.min - v2, v1.max - v2};
}

template <typename T, int t_n>
Q_CX_ABLE span<T, t_n> operator-(const detail::span_value_t<T, t_n> & v1, const span<T, t_n> & v2) {
    if constexpr (t_n == 1) return {T(v1 - v2.min), T(v1 - v2.max)};
    else return {v1 - v2.min, v1 - v2.max};
}

//--- multiply ---

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator*(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {T(v1.x * v2.x), T(v1.y * v2.y)};
    if constexpr (t_n == 3) return {T(v1.x * v2.x), T(v1.y * v2.y), T(v1.z * v2.z)};
    if constexpr (t_n == 4) return {T(v1.x * v2.x), T(v1.y * v2.y), T(v1.z * v2.z), T(v1.w * v2.w)};
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator*(const vec<T, t_n> & v1, T v2) {
    if constexpr (t_n == 2) return {T(v1.x * v2), T(v1.y * v2)};
    if constexpr (t_n == 3) return {T(v1.x * v2), T(v1.y * v2), T(v1.z * v2)};
    if constexpr (t_n == 4) return {T(v1.x * v2), T(v1.y * v2), T(v1.z * v2), T(v1.w * v2)};
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator*(T v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {T(v1 * v2.x), T(v1 * v2.y)};
    if constexpr (t_n == 3) return {T(v1 * v2.x), T(v1 * v2.y), T(v1 * v2.z)};
    if constexpr (t_n == 4) return {T(v1 * v2.x), T(v1 * v2.y), T(v1 * v2.z), T(v1 * v2.w)};
}

template <typename T, int t_n>
Q_CX_ABLE span<T, t_n> operator*(const span<T, t_n> & v1, const detail::span_value_t<T, t_n> & v2) {
    if constexpr (t_n == 1) return {T(v1.min * v2), T(v1.max * v2)};
    else return {v1.min * v2, v1.max * v2};
}

template <typename T, int t_n>
Q_CX_ABLE span<T, t_n> operator*(const detail::span_value_t<T, t_n> & v1, const span<T, t_n> & v2) {
    return v2 * v1;
}

//--- divide ---

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator/(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {T(v1.x / v2.x), T(v1.y / v2.y)};
    if constexpr (t_n == 3) return {T(v1.x / v2.x), T(v1.y / v2.y), T(v1.z / v2.z)};
    if constexpr (t_n == 4) return {T(v1.x / v2.x), T(v1.y / v2.y), T(v1.z / v2.z), T(v1.w / v2.w)};
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator/(const vec<T, t_n> & v1, T v2) {
    if constexpr (is_floating_point_v<T>) {
        return v1 * (T(1.0) / v2);
    }
    if constexpr (t_n == 2) return {T(v1.x / v2), T(v1.y / v2)};
    if constexpr (t_n == 3) return {T(v1.x / v2), T(v1.y / v2), T(v1.z / v2)};
    if constexpr (t_n == 4) return {T(v1.x / v2), T(v1.y / v2), T(v1.z / v2), T(v1.w / v2)};
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator/(T v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {T(v1 / v2.x), T(v1 / v2.y)};
    if constexpr (t_n == 3) return {T(v1 / v2.x), T(v1 / v2.y), T(v1 / v2.z)};
    if constexpr (t_n == 4) return {T(v1 / v2.x), T(v1 / v2.y), T(v1 / v2.z), T(v1 / v2.w)};
}

template <typename T, int t_n>
Q_CX_ABLE span<T, t_n> operator/(const span<T, t_n> & v1, const detail::span_value_t<T, t_n> & v2) {
    if constexpr (is_floating_point_v<T>) {
        return v1 * (T(1.0) / v2);
    }
    if constexpr (t_n == 1) return {T(v1.min / v2), T(v1.max / v2)};
    else return {v1.min / v2, v1.max / v2};
}

template <typename T, int t_n>
Q_CX_ABLE span<T, t_n> operator/(const detail::span_value_t<T, t_n> & v1, const span<T, t_n> & v2) {
    if constexpr (t_n == 1) return {T(v1 / v2.min), T(v1 / v2.max)};
    else return {v1 / v2.min, v1 / v2.max};
}

//--- modulus ---

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator%(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {mod(v1.x, v2.x), mod(v1.y, v2.y)};
    if constexpr (t_n == 3) return {mod(v1.x, v2.x), mod(v1.y, v2.y), mod(v1.z, v2.z)};
    if constexpr (t_n == 4) return {mod(v1.x, v2.x), mod(v1.y, v2.y), mod(v1.z, v2.z), mod(v1.w, v2.w)};
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator%(const vec<T, t_n> & v1, T v2) {
    if constexpr (t_n == 2) return {mod(v1.x, v2), mod(v1.y, v2)};
    if constexpr (t_n == 3) return {mod(v1.x, v2), mod(v1.y, v2), mod(v1.z, v2)};
    if constexpr (t_n == 4) return {mod(v1.x, v2), mod(v1.y, v2), mod(v1.z, v2), mod(v1.w, v2)};
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> operator%(T v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {mod(v1, v2.x), mod(v1, v2.y)};
    if constexpr (t_n == 3) return {mod(v1, v2.x), mod(v1, v2.y), mod(v1, v2.z)};
    if constexpr (t_n == 4) return {mod(v1, v2.x), mod(v1, v2.y), mod(v1, v2.z), mod(v1, v2.w)};
}

//------------------------------------------------------------------------------
// Comparison Operators

//--- equal to ---

template <typename T, int t_n>
Q_CX_ABLE bool operator==(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return v1.x == v2.x && v1.y == v2.y;
    if constexpr (t_n == 3) return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
    if constexpr (t_n == 4) return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator==(const vec<T, t_n> & v1, T v2) {
    if constexpr (t_n == 2) return {v1.x == v2, v1.y == v2};
    if constexpr (t_n == 3) return {v1.x == v2, v1.y == v2, v1.z == v2};
    if constexpr (t_n == 4) return {v1.x == v2, v1.y == v2, v1.z == v2, v1.w == v2};
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator==(T v1, const vec<T, t_n> & v2) {
    return v2 == v1;
}

template <typename T, int t_n>
Q_CX_ABLE bool operator==(const span<T, t_n> & v1, const span<T, t_n> & v2) {
    return v1.min == v2.min && v1.max == v2.max;
}

//--- not equal to ---

template <typename T, int t_n>
Q_CX_ABLE bool operator!=(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    return !(v1 == v2);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator!=(const vec<T, t_n> & v1, T v2) {
    return !(v1 == v2);
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator!=(T v1, const vec<T, t_n> & v2) {
    return !(v1 == v2);
}

template <typename T, int t_n>
Q_CX_ABLE bool operator!=(const span<T, t_n> & v1, const span<T, t_n> & v2) {
    return !(v1 == v2);
}

//--- less than ---

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator<(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {v1.x < v2.x, v1.y < v2.y};
    if constexpr (t_n == 3) return {v1.x < v2.x, v1.y < v2.y, v1.z < v2.z};
    if constexpr (t_n == 4) return {v1.x < v2.x, v1.y < v2.y, v1.z < v2.z, v1.w < v2.w};
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator<(const vec<T, t_n> & v1, T v2) {
    if constexpr (t_n == 2) return {v1.x < v2, v1.y < v2};
    if constexpr (t_n == 3) return {v1.x < v2, v1.y < v2, v1.z < v2};
    if constexpr (t_n == 4) return {v1.x < v2, v1.y < v2, v1.z < v2, v1.w < v2};
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator<(T v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {v1 < v2.x, v1 < v2.y};
    if constexpr (t_n == 3) return {v1 < v2.x, v1 < v2.y, v1 < v2.z};
    if constexpr (t_n == 4) return {v1 < v2.x, v1 < v2.y, v1 < v2.z, v1 < v2.w};
}

//--- greater than ---

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator>(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {v1.x > v2.x, v1.y > v2.y};
    if constexpr (t_n == 3) return {v1.x > v2.x, v1.y > v2.y, v1.z > v2.z};
    if constexpr (t_n == 4) return {v1.x > v2.x, v1.y > v2.y, v1.z > v2.z, v1.w > v2.w};
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator>(const vec<T, t_n> & v1, T v2) {
    if constexpr (t_n == 2) return {v1.x > v2, v1.y > v2};
    if constexpr (t_n == 3) return {v1.x > v2, v1.y > v2, v1.z > v2};
    if constexpr (t_n == 4) return {v1.x > v2, v1.y > v2, v1.z > v2, v1.w > v2};
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator>(T v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {v1 > v2.x, v1 > v2.y};
    if constexpr (t_n == 3) return {v1 > v2.x, v1 > v2.y, v1 > v2.z};
    if constexpr (t_n == 4) return {v1 > v2.x, v1 > v2.y, v1 > v2.z, v1 > v2.w};
}

//--- less than or equal to ---

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator<=(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {v1.x <= v2.x, v1.y <= v2.y};
    if constexpr (t_n == 3) return {v1.x <= v2.x, v1.y <= v2.y, v1.z <= v2.z};
    if constexpr (t_n == 4) return {v1.x <= v2.x, v1.y <= v2.y, v1.z <= v2.z, v1.w <= v2.w};
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator<=(const vec<T, t_n> & v1, T v2) {
    if constexpr (t_n == 2) return {v1.x <= v2, v1.y <= v2};
    if constexpr (t_n == 3) return {v1.x <= v2, v1.y <= v2, v1.z <= v2};
    if constexpr (t_n == 4) return {v1.x <= v2, v1.y <= v2, v1.z <= v2, v1.w <= v2};
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator<=(T v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {v1 <= v2.x, v1 <= v2.y};
    if constexpr (t_n == 3) return {v1 <= v2.x, v1 <= v2.y, v1 <= v2.z};
    if constexpr (t_n == 4) return {v1 <= v2.x, v1 <= v2.y, v1 <= v2.z, v1 <= v2.w};
}

//--- greater than or equal to ---

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator>=(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {v1.x >= v2.x, v1.y >= v2.y};
    if constexpr (t_n == 3) return {v1.x >= v2.x, v1.y >= v2.y, v1.z >= v2.z};
    if constexpr (t_n == 4) return {v1.x >= v2.x, v1.y >= v2.y, v1.z >= v2.z, v1.w >= v2.w};
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator>=(const vec<T, t_n> & v1, T v2) {
    if constexpr (t_n == 2) return {v1.x >= v2, v1.y >= v2};
    if constexpr (t_n == 3) return {v1.x >= v2, v1.y >= v2, v1.z >= v2};
    if constexpr (t_n == 4) return {v1.x >= v2, v1.y >= v2, v1.z >= v2, v1.w >= v2};
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator>=(T v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {v1 >= v2.x, v1 >= v2.y};
    if constexpr (t_n == 3) return {v1 >= v2.x, v1 >= v2.y, v1 >= v2.z};
    if constexpr (t_n == 4) return {v1 >= v2.x, v1 >= v2.y, v1 >= v2.z, v1 >= v2.w};
}

//------------------------------------------------------------------------------
// Logic Operators

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator&&(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {v1.x && v2.x, v1.y && v2.y};
    if constexpr (t_n == 3) return {v1.x && v2.x, v1.y && v2.y, v1.z && v2.z};
    if constexpr (t_n == 4) return {v1.x && v2.x, v1.y && v2.y, v1.z && v2.z, v1.w && v2.w};
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator||(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {v1.x || v2.x, v1.y || v2.y};
    if constexpr (t_n == 3) return {v1.x || v2.x, v1.y || v2.y, v1.z || v2.z};
    if constexpr (t_n == 4) return {v1.x || v2.x, v1.y || v2.y, v1.z || v2.z, v1.w || v2.w};
}

template <typename T, int t_n>
Q_CX_ABLE bvec<t_n> operator!(const vec<T, t_n> & v) {
    if constexpr (t_n == 2) return {!v.x, !v.y};
    if constexpr (t_n == 3) return {!v.x, !v.y, !v.z};
    if constexpr (t_n == 4) return {!v.x, !v.y, !v.z, !v.w};
}

//------------------------------------------------------------------------------
// Condensation

template <typename T, int t_n>
Q_CX_ABLE T sum(const vec<T, t_n> & v) {
    if constexpr (t_n == 2) return v.x + v.y;
    if constexpr (t_n == 3) return v.x + v.y + v.z;
    if constexpr (t_n == 4) return v.x + v.y + v.z + v.w;
}

template <typename T, int t_n>
Q_CX_ABLE T product(const vec<T, t_n> & v) {
    if constexpr (t_n == 2) return v.x * v.y;
    if constexpr (t_n == 3) return v.x * v.y * v.z;
    if constexpr (t_n == 4) return v.x * v.y * v.z * v.w;
}

template <typename T, int t_n>
Q_CX_ABLE bool all(const vec<T, t_n> & v) {
    if constexpr (t_n == 2) return v.x && v.y;
    if constexpr (t_n == 3) return v.x && v.y && v.z;
    if constexpr (t_n == 4) return v.x && v.y && v.z && v.w;
}

template <typename T, int t_n>
Q_CX_ABLE bool any(const vec<T, t_n> & v) {
    if constexpr (t_n == 2) return v.x || v.y;
    if constexpr (t_n == 3) return v.x || v.y || v.z;
    if constexpr (t_n == 4) return v.x || v.y || v.z || v.w;
}

//------------------------------------------------------------------------------
// Other

template <typename T, int t_n>
Q_CX_ABLE T min(const vec<T, t_n> & v) {
    if constexpr (t_n == 2) return min(v.x, v.y);
    if constexpr (t_n == 3) return min(v.x, v.y, v.z);
    if constexpr (t_n == 4) return min(v.x, v.y, v.z, v.w);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> min(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {min(v1.x, v2.x), min(v1.y, v2.y)};
    if constexpr (t_n == 3) return {min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z)};
    if constexpr (t_n == 4) return {min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z), min(v1.w, v2.w)};
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> min(const vec<T, t_n> & v1, T v2) {
    if constexpr (t_n == 2) return {min(v1.x, v2), min(v1.y, v2)};
    if constexpr (t_n == 3) return {min(v1.x, v2), min(v1.y, v2), min(v1.z, v2)};
    if constexpr (t_n == 4) return {min(v1.x, v2), min(v1.y, v2), min(v1.z, v2), min(v1.w, v2)};
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> min(T v1, const vec<T, t_n> & v2) {
    return min(v2, v1);
}

template <typename T, int t_n>
Q_CX_ABLE T max(const vec<T, t_n> & v) {
    if constexpr (t_n == 2) return max(v.x, v.y);
    if constexpr (t_n == 3) return max(v.x, v.y, v.z);
    if constexpr (t_n == 4) return max(v.x, v.y, v.z, v.w);
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> max(const vec<T, t_n> & v1, const vec<T, t_n> & v2) {
    if constexpr (t_n == 2) return {max(v1.x, v2.x), max(v1.y, v2.y)};
    if constexpr (t_n == 3) return {max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z)};
    if constexpr (t_n == 4) return {max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z), max(v1.w, v2.w)};
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> max(const vec<T, t_n> & v1, T v2) {
    if constexpr (t_n == 2) return {max(v1.x, v2), max(v1.y, v2)};
    if constexpr (t_n == 3) return {max(v1.x, v2), max(v1.y, v2), max(v1.z, v2)};
    if constexpr (t_n == 4) return {max(v1.x, v2), max(v1.y, v2), max(v1.z, v2), max(v1.w, v2)};
}

template <typename T, int t_n>
Q_CX_ABLE vec<T, t_n> max(T v1, const vec<T, t_n> & v2) {
    return max(v2, v1);
}

template <typename T, int t_n>
inline vec<T, t_n> & minify(vec<T, t_n> & min, const vec<T, t_n> & v) {
    if constexpr (t_n >= 1) minify(min.x, v.x);
    if constexpr (t_n >= 2) minify(min.y, v.y);
    if constexpr (t_n >= 3) minify(min.z, v.z);
    if constexpr (t_n >= 4) minify(min.w, v.w);
    return min;
}

template <typename T, int t_n>
inline vec<T, t_n> & minify(vec<T, t_n> & min, T v) {
    if constexpr (t_n >= 1) minify(min.x, v);
    if constexpr (t_n >= 2) minify(min.y, v);
    if constexpr (t_n >= 3) minify(min.z, v);
    if constexpr (t_n >= 4) minify(min.w, v);
    return min;
}

template <typename T, int t_n>
inline vec<T, t_n> & maxify(vec<T, t_n> & max, const vec<T, t_n> & v) {
    if constexpr (t_n >= 1) maxify(max.x, v.x);
    if constexpr (t_n >= 2) maxify(max.y, v.y);
    if constexpr (t_n >= 3) maxify(max.z, v.z);
    if constexpr (t_n >= 4) maxify(max.w, v.w);
    return max;
}

template <typename T, int t_n>
inline vec<T, t_n> & maxify(vec<T, t_n> & max, T v) {
    if constexpr (t_n >= 1) maxify(max.x, v);
    if constexpr (t_n >= 2) maxify(max.y, v);
    if constexpr (t_n >= 3) maxify(max.z, v);
    if constexpr (t_n >= 4) maxify(max.w, v);
    return max;
}

}
