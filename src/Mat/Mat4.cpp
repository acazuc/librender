#ifndef MAT4_CPP
# define MAT4_CPP

#include "Mat4.h"
#include "Mat3.h"
#include <cmath>

namespace librender
{

	template <typename T>
	TMat4<T>::TMat4(TMat3<T> mat)
	{
		this->data[0] = TVec4<T>(mat[0], T(0));
		this->data[1] = TVec4<T>(mat[1], T(0));
		this->data[2] = TVec4<T>(mat[2], T(0));
		this->data[3] = TVec4<T>(T(0), T(0), T(0), T(1));
	}

	template <typename T>
	TMat4<T>::TMat4(TVec4<T> vec)
	{
		this->data[0] = TVec4<T>(T(vec.x), T(0), T(0), T(0));
		this->data[1] = TVec4<T>(T(0), T(vec.y), T(0), T(0));
		this->data[2] = TVec4<T>(T(0), T(0), T(vec.z), T(0));
		this->data[3] = TVec4<T>(T(0), T(0), T(0), T(vec.w));
	}

	template <typename T>
	TMat4<T>::TMat4(T value)
	{
		this->data[0] = TVec4<T>(T(value), T(0), T(0), T(0));
		this->data[1] = TVec4<T>(T(0), T(value), T(0), T(0));
		this->data[2] = TVec4<T>(T(0), T(0), T(value), T(0));
		this->data[3] = TVec4<T>(T(0), T(0), T(0), T(value));
	}

	template <typename T>
	TVec4<T> &TMat4<T>::operator [] (int i)
	{
		return (this->data[i]);
	}

	template <typename T>
	TMat4<T> TMat4<T>::rotate(TMat4<T> mat, T angle, TVec3<T> axis)
	{
		T c(cos(angle));
		T s(sin(angle));
		TVec3<T> t(axis * (T(1) - c));
		TVec3<T> vx(t * axis.x);
		TVec3<T> u(axis * s);
		T yy(axis.y * t.y);
		T yz(axis.y * t.z);
		T zz(axis.z * t.z);
		axis.normalize();
		TMat3<T> rotate;
		rotate[0][0] = T(vx.x + c);
		rotate[0][1] = T(vx.y + u.z);
		rotate[0][2] = T(vx.z - u.y);
		rotate[1][0] = T(vx.y - u.x);
		rotate[1][1] = T(yy + c);
		rotate[1][2] = T(yz + u.z);
		rotate[2][0] = T(vx.z + u.y);
		rotate[2][1] = T(yz - u.x);
		rotate[2][2] = T(zz + c);
		TMat4<T> result;
		result[0] = mat[0] * rotate[0][0] + mat[1] * rotate[0][1] + mat[2] * rotate[0][2];
		result[1] = mat[0] * rotate[1][0] + mat[1] * rotate[1][1] + mat[2] * rotate[1][2];
		result[2] = mat[0] * rotate[2][0] + mat[1] * rotate[2][1] + mat[2] * rotate[2][2];
		result[3] = mat[3];
		return (result);
	}

	template <typename T>
	TMat4<T> TMat4<T>::rotateX(TMat4<T> mat, T angle)
	{
		T c(cos(angle));
		T s(sin(angle));
		TMat4<T> rotate;
		rotate[0] = TVec4<T>(T(1), T( 0), T(0), T(0));
		rotate[1] = TVec4<T>(T(0), T( c), T(s), T(0));
		rotate[2] = TVec4<T>(T(0), T(-s), T(c), T(0));
		rotate[3] = TVec4<T>(T(0), T( 0), T(0), T(1));
		TMat4<T> result;
		result[0] = mat[0];
		result[1] = mat[0] * rotate[1][0] + mat[1] * rotate[1][1] + mat[2] * rotate[1][2];
		result[2] = mat[0] * rotate[2][0] + mat[1] * rotate[2][1] + mat[2] * rotate[2][2];
		result[3] = mat[3];
		return (result);
	}

	template <typename T>
	TMat4<T> TMat4<T>::rotateY(TMat4<T> mat, T angle)
	{
		T c(cos(angle));
		T s(sin(angle));
		TMat4<T> rotate;
		rotate[0] = TVec4<T>(T(c), T(0), T(-s), T(0));
		rotate[1] = TVec4<T>(T(0), T(1), T( 0), T(0));
		rotate[2] = TVec4<T>(T(s), T(0), T( c), T(0));
		rotate[3] = TVec4<T>(T(0), T(0), T( 0), T(1));
		TMat4<T> result;
		result[0] = mat[0] * rotate[0][0] + mat[1] * rotate[0][1] + mat[2] * rotate[0][2];
		result[1] = mat[1];
		result[2] = mat[0] * rotate[2][0] + mat[1] * rotate[2][1] + mat[2] * rotate[2][2];
		result[3] = mat[3];
		return (result);
	}

	template <typename T>
	TMat4<T> TMat4<T>::rotateZ(TMat4<T> mat, T angle)
	{
		T c(cos(angle));
		T s(sin(angle));
		TMat4<T> rotate;
		rotate[0] = TVec4<T>(T( c), T(s), T(0), T(0));
		rotate[1] = TVec4<T>(T(-s), T(c), T(0), T(0));
		rotate[2] = TVec4<T>(T( 0), T(0), T(1), T(0));
		rotate[3] = TVec4<T>(T( 0), T(0), T(0), T(1));
		TMat4<T> result;
		result[0] = mat[0] * rotate[0][0] + mat[1] * rotate[0][1] + mat[2] * rotate[0][2];
		result[1] = mat[0] * rotate[1][0] + mat[1] * rotate[1][1] + mat[2] * rotate[1][2];
		result[2] = mat[2] * rotate[2][2];
		result[3] = mat[3];
		return (result);
	}

	template <typename T>
	TMat4<T> TMat4<T>::translate(TMat4<T> mat, TVec3<T> vec)
	{
		TMat4<T> result(mat);
		result[3] = mat[0] * vec[0] + mat[1] * vec[1] + mat[2] * vec[2] + mat[3];
		return (result);
	}

	template <typename T>
	TMat4<T> TMat4<T>::scale(TMat4<T> mat, TVec3<T> vec)
	{
		TMat4<T> result;
		result[0] = mat[0] * vec[0];
		result[1] = mat[1] * vec[1];
		result[2] = mat[2] * vec[2];
		result[3] = mat[3];
		return (result);
	}

	template <typename T>
	TMat4<T> TMat4<T>::perspective(T fov, T aspect, T znear, T zfar)
	{
		T f(T(1) / tan(fov / T(2)));
		TMat4<T> mat(TVec4<T>(f / aspect, f, (zfar + znear) / (znear - zfar), T(0)));
		mat[2][3] = T(-1);
		mat[3][2] = (T(2) * zfar * znear) / (znear - zfar);
		return (mat);
	}

	template <typename T>
	TMat4<T> TMat4<T>::lookAt(TVec3<T> eye, TVec3<T> center, TVec3<T> up)
	{
		TVec3<T> f(center - eye);
		f.normalize();
		up.normalize();
		TVec3<T> s(f.cross(up));
		TVec3<T> ss(s);
		ss.normalize();
		TVec3<T> u(ss.cross(f));
		f = -f;
		TMat4<T> mat;
		mat[0] = TVec4<T>(T(s[0]), T(u[0]), T(f[0]), T(0));
		mat[1] = TVec4<T>(T(s[1]), T(u[1]), T(f[1]), T(0));
		mat[2] = TVec4<T>(T(s[2]), T(u[2]), T(f[2]), T(0));
		mat[3] = TVec4<T>(T(0)   , T(0)   , T(0)   , T(1));
		return (translate(mat, TVec3<T>(-eye)));
	}

	template <typename T>
	TMat4<T> TMat4<T>::ortho(T left, T right, T bottom, T top, T near, T far)
	{
		TMat4<T> mat(TVec4<T>(T(2) / (right - left), T(2) / (top - bottom), T(-2) / (far - near), T(1)));
		mat[3][0] = -(right + left) / (right - left);
		mat[3][1] = -(top + bottom) / (top - bottom);
		mat[3][2] = -(far + near) / (far - near);
		return (mat);
	}

	template <typename T>
	TMat4<T> TMat4<T>::operator * (TMat4<T> mat)
	{
		TMat4<T> result;
		for (int i = 0; i < 4; ++i)
			result[i] = (*this)[0] * mat[i][0] + (*this)[1] * mat[i][1] + (*this)[2] * mat[i][2] + (*this)[3] * mat[i][3];
		return (result);
	}

	template <typename T>
	TVec4<T> operator * (TMat4<T> mat, TVec4<T> vec)
	{
		TVec4<T> result;
		for (int i = 0; i < 4; ++i)
			result[i] = vec.x * mat[0][i] + vec.y * mat[1][i] + vec.z * mat[2][i] + vec.w * mat[3][i];
		return (result);
	}

	template <typename T>
	TVec4<T> operator * (TVec4<T> vec, TMat4<T> mat)
	{
		TVec4<T> result;
		for (int i = 0; i < 4; ++i)
			result[i] = vec.x * mat[i].x + vec.y * mat[i].y + vec.z * mat[i].z + vec.w * mat[i].w;
		return (result);
	}

}

#endif
