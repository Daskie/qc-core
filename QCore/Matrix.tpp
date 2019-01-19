namespace qc {



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT1 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr mat<T, 1>::mat() :
    c1(T(1.0))
{}

template <typename T>
constexpr mat<T, 1>::mat(const mat1<T> & m) :
    c1(m.c1)
{}

template <typename T>
constexpr mat<T, 1>::mat(mat1<T> && m) :
    c1(std::move(m.c1))
{}

template <typename T>
template <typename U>
constexpr mat<T, 1>::mat(const mat1<U> & m) :
    c1(m.c1)
{}

template <typename T>
template <typename U>
constexpr mat<T, 1>::mat(const mat2<U> & m) :
    c1(m.c1)
{}

template <typename T>
template <typename U>
constexpr mat<T, 1>::mat(const mat3<U> & m) :
    c1(m.c1)
{}

template <typename T>
template <typename U>
constexpr mat<T, 1>::mat(const mat4<U> & m) :
    c1(m.c1)
{}

template <typename T>
constexpr mat<T, 1>::mat(
    T x1
) :
    c1(x1)
{}

template <typename T>
constexpr mat<T, 1>::mat(
    const vec1<T> & c1
) :
    c1(c1)
{}



//------------------------------------------------------------------------------
// Assignment



template <typename T>
inline mat1<T> & mat<T, 1>::operator=(const mat1<T> & m) {
    c1 = m.c1;

    return *this;
}

template <typename T>
inline mat1<T> & mat<T, 1>::operator=(mat1<T> && m) {
    c1 = std::move(m.c1);

    return *this;
}

template <typename T>
template <typename U, int t_n>
inline mat1<T> & mat<T, 1>::operator=(const mat<U, t_n> & m) {
    if constexpr (t_n >= 1) c1 = m.c1; else c1 = vec1<T>(T(1.0));
    
    return *this;
}



//------------------------------------------------------------------------------
// Access



template <typename T>
inline vec1<T> & mat<T, 1>::col(int i) {
    return *(&c1 + i);
}

template <typename T>
inline const vec1<T> & mat<T, 1>::col(int i) const {
    return *(&c1 + i);
}

template <typename T>
inline vec1<T> mat<T, 1>::row(int i) const {
    return vec1<T>(c1[i]);
}

template <typename T>
template <int t_i>
constexpr const vec1<T> & mat<T, 1>::col() const {
    if constexpr (t_i == 0) return c1;
}

template <typename T>
template <int t_i>
constexpr vec1<T> mat<T, 1>::row() const {
    return vec1<T>(c1.at<t_i>());
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT2 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr mat<T, 2>::mat() :
    c1(T(1.0), T(0.0)),
    c2(T(0.0), T(1.0))
{}

template <typename T>
constexpr mat<T, 2>::mat(const mat2<T> & m) :
    c1(m.c1),
    c2(m.c2)
{}

template <typename T>
constexpr mat<T, 2>::mat(mat2<T> && m) :
    c1(std::move(m.c1)),
    c2(std::move(m.c2))
{}

template <typename T>
template <typename U>
constexpr mat<T, 2>::mat(const mat1<U> & m) :
    c1(m.c1),
    c2(T(0.0), T(1.0))
{}

template <typename T>
template <typename U>
constexpr mat<T, 2>::mat(const mat2<U> & m) :
    c1(m.c1),
    c2(m.c2)
{}

template <typename T>
template <typename U>
constexpr mat<T, 2>::mat(const mat3<U> & m) :
    c1(m.c1),
    c2(m.c2)
{}

template <typename T>
template <typename U>
constexpr mat<T, 2>::mat(const mat4<U> & m) :
    c1(m.c1),
    c2(m.c2)
{}

template <typename T>
constexpr mat<T, 2>::mat(
    T x1, T y1,
    T x2, T y2
) :
    c1(x1, y1),
    c2(x2, y2)
{}

template <typename T>
constexpr mat<T, 2>::mat(
    const vec2<T> & c1,
    const vec2<T> & c2
) :
    c1(c1),
    c2(c2)
{}



//------------------------------------------------------------------------------
// Assignment



template <typename T>
inline mat2<T> & mat<T, 2>::operator=(const mat2<T> & m) {
    c1 = m.c1;
    c2 = m.c2;

    return *this;
}

template <typename T>
inline mat2<T> & mat<T, 2>::operator=(mat2<T> && m) {
    c1 = std::move(m.c1);
    c2 = std::move(m.c2);

    return *this;
}

template <typename T>
template <typename U, int t_n>
inline mat2<T> & mat<T, 2>::operator=(const mat<U, t_n> & m) {
    if constexpr (t_n >= 1) c1 = m.c1; else c1 = vec2<T>(T(1.0), T(0.0));
    if constexpr (t_n >= 2) c2 = m.c2; else c2 = vec2<T>(T(0.0), T(1.0));
    
    return *this;
}



//------------------------------------------------------------------------------
// Access



template <typename T>
inline vec2<T> & mat<T, 2>::col(int i) {
    return *(&c1 + i);
}

template <typename T>
inline const vec2<T> & mat<T, 2>::col(int i) const {
    return *(&c1 + i);
}

template <typename T>
inline vec2<T> mat<T, 2>::row(int i) const {
    return vec2<T>(c1[i], c2[i]);
}

template <typename T>
template <int t_i>
constexpr const vec2<T> & mat<T, 2>::col() const {
    if constexpr (t_i == 0) return c1;
    if constexpr (t_i == 1) return c2;
}

template <typename T>
template <int t_i>
constexpr vec2<T> mat<T, 2>::row() const {
    return vec2<T>(c1.at<t_i>(), c2.at<t_i>());
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT3 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr mat<T, 3>::mat() :
    c1(T(1.0), T(0.0), T(0.0)),
    c2(T(0.0), T(1.0), T(0.0)),
    c3(T(0.0), T(0.0), T(1.0))
{}

template <typename T>
constexpr mat<T, 3>::mat(const mat3<T> & m) :
    c1(m.c1),
    c2(m.c2),
    c3(m.c3)
{}

template <typename T>
constexpr mat<T, 3>::mat(mat3<T> && m) :
    c1(std::move(m.c1)),
    c2(std::move(m.c2)),
    c3(std::move(m.c3))
{}

template <typename T>
template <typename U>
constexpr mat<T, 3>::mat(const mat1<U> & m) :
    c1(m.c1),
    c2(T(0.0), T(1.0), T(0.0)),
    c3(T(0.0), T(0.0), T(1.0))
{}

template <typename T>
template <typename U>
constexpr mat<T, 3>::mat(const mat2<U> & m) :
    c1(m.c1),
    c2(m.c2),
    c3(T(0.0), T(0.0), T(1.0))
{}

template <typename T>
template <typename U>
constexpr mat<T, 3>::mat(const mat3<U> & m) :
    c1(m.c1),
    c2(m.c2),
    c3(m.c3)
{}

template <typename T>
template <typename U>
constexpr mat<T, 3>::mat(const mat4<U> & m) :
    c1(m.c1),
    c2(m.c2),
    c3(m.c3)
{}

template <typename T>
constexpr mat<T, 3>::mat(
    T x1, T y1, T z1,
    T x2, T y2, T z2,
    T x3, T y3, T z3
) :
    c1(x1, y1, z1),
    c2(x2, y2, z2),
    c3(x3, y3, z3)
{}

template <typename T>
constexpr mat<T, 3>::mat(
    const vec3<T> & c1,
    const vec3<T> & c2,
    const vec3<T> & c3
) :
    c1(c1),
    c2(c2),
    c3(c3)
{}



//------------------------------------------------------------------------------
// Assignment



template <typename T>
inline mat3<T> & mat<T, 3>::operator=(const mat3<T> & m) {
    c1 = m.c1;
    c2 = m.c2;
    c3 = m.c3;

    return *this;
}

template <typename T>
inline mat3<T> & mat<T, 3>::operator=(mat3<T> && m) {
    c1 = std::move(m.c1);
    c2 = std::move(m.c2);
    c3 = std::move(m.c3);

    return *this;
}

template <typename T>
template <typename U, int t_n>
inline mat3<T> & mat<T, 3>::operator=(const mat<U, t_n> & m) {
    if constexpr (t_n >= 1) c1 = m.c1; else c1 = vec3<T>(T(1.0), T(0.0), T(0.0));
    if constexpr (t_n >= 2) c2 = m.c2; else c2 = vec3<T>(T(0.0), T(1.0), T(0.0));
    if constexpr (t_n >= 3) c3 = m.c3; else c3 = vec3<T>(T(0.0), T(0.0), T(1.0));

    return *this;
}



//------------------------------------------------------------------------------
// Access



template <typename T>
inline vec3<T> & mat<T, 3>::col(int i) {
    return *(&c1 + i);
}

template <typename T>
inline const vec3<T> & mat<T, 3>::col(int i) const {
    return *(&c1 + i);
}

template <typename T>
inline vec3<T> mat<T, 3>::row(int i) const {
    return vec3<T>(c1[i], c2[i], c3[i]);
}

template <typename T>
template <int t_i>
constexpr const vec3<T> & mat<T, 3>::col() const {
    if constexpr (t_i == 0) return c1;
    if constexpr (t_i == 1) return c2;
    if constexpr (t_i == 2) return c3;
}

template <typename T>
template <int t_i>
constexpr vec3<T> mat<T, 3>::row() const {
    return vec3<T>(c1.at<t_i>(), c2.at<t_i>(), c3.at<t_i>());
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT4 IMPLEMENTATION -------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Constructors



template <typename T>
constexpr mat<T, 4>::mat() :
    c1(T(1.0), T(0.0), T(0.0), T(0.0)),
    c2(T(0.0), T(1.0), T(0.0), T(0.0)),
    c3(T(0.0), T(0.0), T(1.0), T(0.0)),
    c4(T(0.0), T(0.0), T(0.0), T(1.0))
{}

template <typename T>
constexpr mat<T, 4>::mat(const mat4<T> & m) :
    c1(m.c1),
    c2(m.c2),
    c3(m.c3),
    c4(m.c4)
{}

template <typename T>
constexpr mat<T, 4>::mat(mat4<T> && m) :
    c1(std::move(m.c1)),
    c2(std::move(m.c2)),
    c3(std::move(m.c3)),
    c4(std::move(m.c4))
{}

template <typename T>
template <typename U>
constexpr mat<T, 4>::mat(const mat1<U> & m) :
    c1(m.c1),
    c2(T(0.0), T(1.0), T(0.0), T(0.0)),
    c3(T(0.0), T(0.0), T(1.0), T(0.0)),
    c4(T(0.0), T(0.0), T(0.0), T(1.0))
{}

template <typename T>
template <typename U>
constexpr mat<T, 4>::mat(const mat2<U> & m) :
    c1(m.c1),
    c2(m.c2),
    c3(T(0.0), T(0.0), T(1.0), T(0.0)),
    c4(T(0.0), T(0.0), T(0.0), T(1.0))
{}

template <typename T>
template <typename U>
constexpr mat<T, 4>::mat(const mat3<U> & m) :
    c1(m.c1),
    c2(m.c2),
    c3(m.c3),
    c4(T(0.0), T(0.0), T(0.0), T(1.0))
{}

template <typename T>
template <typename U>
constexpr mat<T, 4>::mat(const mat4<U> & m) :
    c1(m.c1),
    c2(m.c2),
    c3(m.c3),
    c4(m.c4)
{}

template <typename T>
constexpr mat<T, 4>::mat(
    T x1, T y1, T z1, T w1,
    T x2, T y2, T z2, T w2,
    T x3, T y3, T z3, T w3,
    T x4, T y4, T z4, T w4
) :
    c1(x1, y1, z1, w1),
    c2(x2, y2, z2, w2),
    c3(x3, y3, z3, w3),
    c4(x4, y4, z4, w4)
{}

template <typename T>
constexpr mat<T, 4>::mat(
    const vec4<T> & c1,
    const vec4<T> & c2,
    const vec4<T> & c3,
    const vec4<T> & c4
) :
    c1(c1),
    c2(c2),
    c3(c3),
    c4(c4)
{}



//------------------------------------------------------------------------------
// Assignment



template <typename T>
inline mat4<T> & mat<T, 4>::operator=(const mat4<T> & m) {
    c1 = m.c1;
    c2 = m.c2;
    c3 = m.c3;
    c4 = m.c4;

    return *this;
}

template <typename T>
inline mat4<T> & mat<T, 4>::operator=(mat4<T> && m) {
    c1 = std::move(m.c1);
    c2 = std::move(m.c2);
    c3 = std::move(m.c3);
    c4 = std::move(m.c4);

    return *this;
}

template <typename T>
template <typename U, int t_n>
inline mat4<T> & mat<T, 4>::operator=(const mat<U, t_n> & m) {
    if constexpr (t_n >= 1) c1 = m.c1; else c1 = vec4<T>(T(1.0), T(0.0), T(0.0), T(0.0));
    if constexpr (t_n >= 2) c2 = m.c2; else c2 = vec4<T>(T(0.0), T(1.0), T(0.0), T(0.0));
    if constexpr (t_n >= 3) c3 = m.c3; else c3 = vec4<T>(T(0.0), T(0.0), T(1.0), T(0.0));
    if constexpr (t_n >= 4) c4 = m.c4; else c4 = vec4<T>(T(0.0), T(0.0), T(0.0), T(1.0));

    return *this;
}



//------------------------------------------------------------------------------
// Access



template <typename T>
inline vec4<T> & mat<T, 4>::col(int i) {
    return *(&c1 + i);
}

template <typename T>
inline const vec4<T> & mat<T, 4>::col(int i) const {
    return *(&c1 + i);
}

template <typename T>
inline vec4<T> mat<T, 4>::row(int i) const {
    return vec4<T>(c1[i], c2[i], c3[i], c4[i]);
}

template <typename T>
template <int t_i>
constexpr const vec4<T> & mat<T, 4>::col() const {
    if constexpr (t_i == 0) return c1;
    if constexpr (t_i == 1) return c2;
    if constexpr (t_i == 2) return c3;
    if constexpr (t_i == 3) return c4;
}

template <typename T>
template <int t_i>
constexpr vec4<T> mat<T, 4>::row() const {
    return vec4<T>(c1.at<t_i>(), c2.at<t_i>(), c3.at<t_i>(), c4.at<t_i>());
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAT FUNCTIONS IMPLEMENTATION ----------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Arithmetic Assignment



//--- add assign ---

template <typename T, int t_n>
inline mat<T, t_n> & operator+=(mat<T, t_n> & m, T v) {
    if constexpr (t_n >= 1) m.c1 += v;
    if constexpr (t_n >= 2) m.c2 += v;
    if constexpr (t_n >= 3) m.c3 += v;
    if constexpr (t_n >= 4) m.c4 += v;

    return m;
}

template <typename T, int t_n>
inline mat<T, t_n> & operator+=(mat<T, t_n> & m1, const mat<T, t_n> & m2) {
    if constexpr (t_n >= 1) m1.c1 += m2.c1;
    if constexpr (t_n >= 2) m1.c2 += m2.c2;
    if constexpr (t_n >= 3) m1.c3 += m2.c3;
    if constexpr (t_n >= 4) m1.c4 += m2.c4;

    return m1;
}

//--- subtract assign ---

template <typename T, int t_n>
inline mat<T, t_n> & operator-=(mat<T, t_n> & m, T v) {
    if constexpr (t_n >= 1) m.c1 -= v;
    if constexpr (t_n >= 2) m.c2 -= v;
    if constexpr (t_n >= 3) m.c3 -= v;
    if constexpr (t_n >= 4) m.c4 -= v;

    return m;
}

template <typename T, int t_n>
inline mat<T, t_n> & operator-=(mat<T, t_n> & m1, const mat<T, t_n> & m2) {
    if constexpr (t_n >= 1) m1.c1 -= m2.c1;
    if constexpr (t_n >= 2) m1.c2 -= m2.c2;
    if constexpr (t_n >= 3) m1.c3 -= m2.c3;
    if constexpr (t_n >= 4) m1.c4 -= m2.c4;

    return m1;
}

//--- multiply assign ---

template <typename T, int t_n>
inline mat<T, t_n> & operator*=(mat<T, t_n> & m, T v) {
    if constexpr (t_n >= 1) m.c1 *= v;
    if constexpr (t_n >= 2) m.c2 *= v;
    if constexpr (t_n >= 3) m.c3 *= v;
    if constexpr (t_n >= 4) m.c4 *= v;

    return m;
}

template <typename T, int t_n>
inline mat<T, t_n> & operator*=(mat<T, t_n> & m1, const mat<T, t_n> & m2) {
    vec<T, t_n> temp;
    if constexpr (t_n >= 1) {
        temp = m1.row<0>();
        if constexpr (t_n >= 1) m1.c1.x = dot(temp, m2.col<0>());
        if constexpr (t_n >= 2) m1.c2.x = dot(temp, m2.col<1>());
        if constexpr (t_n >= 3) m1.c3.x = dot(temp, m2.col<2>());
        if constexpr (t_n >= 4) m1.c4.x = dot(temp, m2.col<3>());
    }
    if constexpr (t_n >= 2) {
        temp = (m1.row<1>());
        if constexpr (t_n >= 1) m1.c1.y = dot(temp, m2.col<0>());
        if constexpr (t_n >= 2) m1.c2.y = dot(temp, m2.col<1>());
        if constexpr (t_n >= 3) m1.c3.y = dot(temp, m2.col<2>());
        if constexpr (t_n >= 4) m1.c4.y = dot(temp, m2.col<3>());
    }
    if constexpr (t_n >= 3) {
        temp = (m1.row<2>());
        if constexpr (t_n >= 1) m1.c1.z = dot(temp, m2.col<0>());
        if constexpr (t_n >= 2) m1.c2.z = dot(temp, m2.col<1>());
        if constexpr (t_n >= 3) m1.c3.z = dot(temp, m2.col<2>());
        if constexpr (t_n >= 4) m1.c4.z = dot(temp, m2.col<3>());
    }
    if constexpr (t_n >= 4) {
        temp = (m1.row<3>());
        if constexpr (t_n >= 1) m1.c1.w = dot(temp, m2.col<0>());
        if constexpr (t_n >= 2) m1.c2.w = dot(temp, m2.col<1>());
        if constexpr (t_n >= 3) m1.c3.w = dot(temp, m2.col<2>());
        if constexpr (t_n >= 4) m1.c4.w = dot(temp, m2.col<3>());
    }

    return m1;
}

//--- divide assign ---

template <typename T, int t_n>
inline mat<T, t_n> & operator/=(mat<T, t_n> & m, T v) {
    return m *= T(1.0) / v;
}



//------------------------------------------------------------------------------
// Arithmetic Operators



//--- positive ---

template <typename T, int t_n>
inline mat<T, t_n> operator+(const mat<T, t_n> & m) {
    return m;
}

//--- negative ---

template <typename T, int t_n>
inline mat<T, t_n> operator-(const mat<T, t_n> & m) {
    if constexpr (t_n == 1) return mat1<T>(-m.c1);
    if constexpr (t_n == 2) return mat2<T>(-m.c1, -m.c2);
    if constexpr (t_n == 3) return mat3<T>(-m.c1, -m.c2, -m.c3);
    if constexpr (t_n == 4) return mat4<T>(-m.c1, -m.c2, -m.c3, -m.c4);
}

//--- add ---

template <typename T, int t_n>
inline mat<T, t_n> operator+(const mat<T, t_n> & m1, const mat<T, t_n> & m2) {
    if constexpr (t_n == 1) return mat1<T>(m1.c1 + m2.c1);
    if constexpr (t_n == 2) return mat2<T>(m1.c1 + m2.c1, m1.c2 + m2.c2);
    if constexpr (t_n == 3) return mat3<T>(m1.c1 + m2.c1, m1.c2 + m2.c2, m1.c3 + m2.c3);
    if constexpr (t_n == 4) return mat4<T>(m1.c1 + m2.c1, m1.c2 + m2.c2, m1.c3 + m2.c3, m1.c4 + m2.c4);
}

template <typename T, int t_n>
inline mat<T, t_n> operator+(const mat<T, t_n> & m, T v) {
    if constexpr (t_n == 1) return mat1<T>(m.c1 + v);
    if constexpr (t_n == 2) return mat2<T>(m.c1 + v, m.c2 + v);
    if constexpr (t_n == 3) return mat3<T>(m.c1 + v, m.c2 + v, m.c3 + v);
    if constexpr (t_n == 4) return mat4<T>(m.c1 + v, m.c2 + v, m.c3 + v, m.c4 + v);
}

template <typename T, int t_n>
inline mat<T, t_n> operator+(T v, const mat<T, t_n> & m) {
    return m + v;
}

//--- subtract ---

template <typename T, int t_n>
inline mat<T, t_n> operator-(const mat<T, t_n> & m1, const mat<T, t_n> & m2) {
    if constexpr (t_n == 1) return mat1<T>(m1.c1 - m2.c1);
    if constexpr (t_n == 2) return mat2<T>(m1.c1 - m2.c1, m1.c2 - m2.c2);
    if constexpr (t_n == 3) return mat3<T>(m1.c1 - m2.c1, m1.c2 - m2.c2, m1.c3 - m2.c3);
    if constexpr (t_n == 4) return mat4<T>(m1.c1 - m2.c1, m1.c2 - m2.c2, m1.c3 - m2.c3, m1.c4 - m2.c4);
}

template <typename T, int t_n>
inline mat<T, t_n> operator-(const mat<T, t_n> & m, T v) {
    if constexpr (t_n == 1) return mat1<T>(m.c1 - v);
    if constexpr (t_n == 2) return mat2<T>(m.c1 - v, m.c2 - v);
    if constexpr (t_n == 3) return mat3<T>(m.c1 - v, m.c2 - v, m.c3 - v);
    if constexpr (t_n == 4) return mat4<T>(m.c1 - v, m.c2 - v, m.c3 - v, m.c4 - v);
}

template <typename T, int t_n>
inline mat<T, t_n> operator-(T v, const mat<T, t_n> & m) {
    if constexpr (t_n == 1) return mat1<T>(v - m.c1);
    if constexpr (t_n == 2) return mat2<T>(v - m.c1, v - m.c2);
    if constexpr (t_n == 3) return mat3<T>(v - m.c1, v - m.c2, v - m.c3);
    if constexpr (t_n == 4) return mat4<T>(v - m.c1, v - m.c2, v - m.c3, v - m.c4);
}

//--- multiply ---

template <typename T, int t_n>
inline mat<T, t_n> operator*(const mat<T, t_n> & m1, const mat<T, t_n> & m2) {
    if constexpr (t_n == 1) return mat1<T>(
        m1.c1.x * m2.c1.x
    );
    if constexpr (t_n == 2) return mat2<T>(
        m1.c1.x * m2.c1.x + m1.c2.x * m2.c1.y,
        m1.c1.y * m2.c1.x + m1.c2.y * m2.c1.y,

        m1.c1.x * m2.c2.x + m1.c2.x * m2.c2.y,
        m1.c1.y * m2.c2.x + m1.c2.y * m2.c2.y
    );
    if constexpr (t_n == 3) return mat3<T>(
        m1.c1.x * m2.c1.x + m1.c2.x * m2.c1.y + m1.c3.x * m2.c1.z,
        m1.c1.y * m2.c1.x + m1.c2.y * m2.c1.y + m1.c3.y * m2.c1.z,
        m1.c1.z * m2.c1.x + m1.c2.z * m2.c1.y + m1.c3.z * m2.c1.z,

        m1.c1.x * m2.c2.x + m1.c2.x * m2.c2.y + m1.c3.x * m2.c2.z,
        m1.c1.y * m2.c2.x + m1.c2.y * m2.c2.y + m1.c3.y * m2.c2.z,
        m1.c1.z * m2.c2.x + m1.c2.z * m2.c2.y + m1.c3.z * m2.c2.z,

        m1.c1.x * m2.c3.x + m1.c2.x * m2.c3.y + m1.c3.x * m2.c3.z,
        m1.c1.y * m2.c3.x + m1.c2.y * m2.c3.y + m1.c3.y * m2.c3.z,
        m1.c1.z * m2.c3.x + m1.c2.z * m2.c3.y + m1.c3.z * m2.c3.z
    );
    if constexpr (t_n == 4) return mat4<T>(
        m1.c1.x * m2.c1.x + m1.c2.x * m2.c1.y + m1.c3.x * m2.c1.z + m1.c4.x * m2.c1.w,
        m1.c1.y * m2.c1.x + m1.c2.y * m2.c1.y + m1.c3.y * m2.c1.z + m1.c4.y * m2.c1.w,
        m1.c1.z * m2.c1.x + m1.c2.z * m2.c1.y + m1.c3.z * m2.c1.z + m1.c4.z * m2.c1.w,
        m1.c1.w * m2.c1.x + m1.c2.w * m2.c1.y + m1.c3.w * m2.c1.z + m1.c4.w * m2.c1.w,

        m1.c1.x * m2.c2.x + m1.c2.x * m2.c2.y + m1.c3.x * m2.c2.z + m1.c4.x * m2.c2.w,
        m1.c1.y * m2.c2.x + m1.c2.y * m2.c2.y + m1.c3.y * m2.c2.z + m1.c4.y * m2.c2.w,
        m1.c1.z * m2.c2.x + m1.c2.z * m2.c2.y + m1.c3.z * m2.c2.z + m1.c4.z * m2.c2.w,
        m1.c1.w * m2.c2.x + m1.c2.w * m2.c2.y + m1.c3.w * m2.c2.z + m1.c4.w * m2.c2.w,

        m1.c1.x * m2.c3.x + m1.c2.x * m2.c3.y + m1.c3.x * m2.c3.z + m1.c4.x * m2.c3.w,
        m1.c1.y * m2.c3.x + m1.c2.y * m2.c3.y + m1.c3.y * m2.c3.z + m1.c4.y * m2.c3.w,
        m1.c1.z * m2.c3.x + m1.c2.z * m2.c3.y + m1.c3.z * m2.c3.z + m1.c4.z * m2.c3.w,
        m1.c1.w * m2.c3.x + m1.c2.w * m2.c3.y + m1.c3.w * m2.c3.z + m1.c4.w * m2.c3.w,

        m1.c1.x * m2.c4.x + m1.c2.x * m2.c4.y + m1.c3.x * m2.c4.z + m1.c4.x * m2.c4.w,
        m1.c1.y * m2.c4.x + m1.c2.y * m2.c4.y + m1.c3.y * m2.c4.z + m1.c4.y * m2.c4.w,
        m1.c1.z * m2.c4.x + m1.c2.z * m2.c4.y + m1.c3.z * m2.c4.z + m1.c4.z * m2.c4.w,
        m1.c1.w * m2.c4.x + m1.c2.w * m2.c4.y + m1.c3.w * m2.c4.z + m1.c4.w * m2.c4.w
    );
}

template <typename T, int t_n>
inline mat<T, t_n> operator*(const mat<T, t_n> & m, T v) {
    if constexpr (t_n == 1) return mat1<T>(m.c1 * v);
    if constexpr (t_n == 2) return mat2<T>(m.c1 * v, m.c2 * v);
    if constexpr (t_n == 3) return mat3<T>(m.c1 * v, m.c2 * v, m.c3 * v);
    if constexpr (t_n == 4) return mat4<T>(m.c1 * v, m.c2 * v, m.c3 * v, m.c4 * v);
}

template <typename T, int t_n>
inline mat<T, t_n> operator*(T v, const mat<T, t_n> & m) {
    return m * v;
}

template <typename T, int t_n>
inline vec<T, t_n> operator*(const mat<T, t_n> & m, const vec<T, t_n> & v) {
    if constexpr (t_n == 1) return vec1<T>(
        m.c1.x * v.x
    );
    if constexpr (t_n == 2) return vec2<T>(
        m.c1.x * v.x + m.c2.x * v.y,
        m.c1.y * v.x + m.c2.y * v.y
    );
    if constexpr (t_n == 3) return vec3<T>(
        m.c1.x * v.x + m.c2.x * v.y + m.c3.x * v.z,
        m.c1.y * v.x + m.c2.y * v.y + m.c3.y * v.z,
        m.c1.z * v.x + m.c2.z * v.y + m.c3.z * v.z
    );
    if constexpr (t_n == 4) return vec4<T>(
        m.c1.x * v.x + m.c2.x * v.y + m.c3.x * v.z + m.c4.x * v.w,
        m.c1.y * v.x + m.c2.y * v.y + m.c3.y * v.z + m.c4.y * v.w,
        m.c1.z * v.x + m.c2.z * v.y + m.c3.z * v.z + m.c4.z * v.w,
        m.c1.w * v.x + m.c2.w * v.y + m.c3.w * v.z + m.c4.w * v.w
    );
}

//--- divide ---

template <typename T, int t_n>
inline mat<T, t_n> operator/(const mat<T, t_n> & m, T v) {
    return m * (T(1.0) / v);
}

template <typename T, int t_n>
inline mat<T, t_n> operator/(T v, const mat<T, t_n> & m) {
    if constexpr (t_n == 1) return mat1<T>(v / m.c1);
    if constexpr (t_n == 2) return mat2<T>(v / m.c1, v / m.c2);
    if constexpr (t_n == 3) return mat3<T>(v / m.c1, v / m.c2, v / m.c3);
    if constexpr (t_n == 4) return mat4<T>(v / m.c1, v / m.c2, v / m.c3, v / m.c4);
}



//------------------------------------------------------------------------------
// Comparison Operators



//--- equal to ---

template <typename T, int t_n>
inline bool operator==(const mat<T, t_n> & m1, const mat<T, t_n> & m2) {
    if constexpr (t_n == 1) return m1.c1 == m2.c1;
    if constexpr (t_n == 2) return m1.c1 == m2.c1 && m1.c2 == m2.c2;
    if constexpr (t_n == 3) return m1.c1 == m2.c1 && m1.c2 == m2.c2 && m1.c3 == m2.c3;
    if constexpr (t_n == 4) return m1.c1 == m2.c1 && m1.c2 == m2.c2 && m1.c3 == m2.c3 && m1.c4 == m2.c4;
}

//--- not equal to ---

template <typename T, int t_n>
inline bool operator!=(const mat<T, t_n> & m1, const mat<T, t_n> & m2) {
    return !(m1 == m2);
}



//------------------------------------------------------------------------------
// Constants



template <typename T, int t_n>
constexpr mat<T, t_n> fullMat(T v) {
    if constexpr (t_n == 1) return mat1<T>(vec1<T>(v));
    if constexpr (t_n == 2) return mat2<T>(vec2<T>(v), vec2<T>(v));
    if constexpr (t_n == 3) return mat3<T>(vec3<T>(v), vec3<T>(v), vec3<T>(v));
    if constexpr (t_n == 4) return mat4<T>(vec4<T>(v), vec4<T>(v), vec4<T>(v), vec4<T>(v));
}

template <typename T, int t_n>
constexpr mat<T, t_n> nullMat() {
    return fullMat<T, t_n>(T(0.0));
}



}