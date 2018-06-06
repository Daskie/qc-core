#pragma once



#include "Matrix.hpp"
#include "VectorFunc.hpp"



namespace qc {



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



}



#include "MatrixFunc.tpp"