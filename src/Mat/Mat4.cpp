#ifndef MAT4_CPP
# define MAT4_CPP

#include "Mat4.h"
#include <cmath>

namespace librender
{

	template <typename T>
	TMat4<T>::TMat4(TVec4<T> vec)
	{
		this->data[0] = TVec4<T>(vec.x, 0, 0, 0);
		this->data[1] = TVec4<T>(0, vec.y, 0, 0);
		this->data[2] = TVec4<T>(0, 0, vec.z, 0);
		this->data[3] = TVec4<T>(0, 0, 0, vec.w);
	}

	template <typename T>
	TMat4<T>::TMat4(T value)
	{
		this->data[0] = TVec4<T>(value, 0, 0, 0);
		this->data[1] = TVec4<T>(0, value, 0, 0);
		this->data[2] = TVec4<T>(0, 0, value, 0);
		this->data[3] = TVec4<T>(0, 0, 0, value);
	}

	template <typename T>
	TVec4<T> &TMat4<T>::operator [] (int i)
	{
		return (this->data[i]);
	}

	template <typename T>
	TMat4<T> TMat4<T>::rotate(TMat4<T> mat, T angle, TVec3<T> axis)
	{
		T c = cos(angle);
		T s = sin(angle);
		TVec3<T> t(axis * (1 - c));
		TVec3<T> vx(t * axis.x);
		TVec3<T> u(axis * s);
		T yy = axis.y * t.y;
		T yz = axis.y * t.z;
		T zz = axis.z * t.z;
		axis.normalize();
		TMat4<T> rotate;
		rotate[0][0] = vx.x + c;
		rotate[0][1] = vx.y + u.z;
		rotate[0][2] = vx.z - u.y;
		rotate[1][0] = vx.y - u.x;
		rotate[1][1] = yy + c;
		rotate[1][2] = yz + u.z;
		rotate[2][0] = vx.z + u.y;
		rotate[2][1] = yz - u.x;
		rotate[2][2] = zz + c;
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
		T c = cos(angle);
		T s = sin(angle);
		TMat4<T> rotate;
		rotate[0] = TVec4<T>(1,  0, 0, 0);
		rotate[1] = TVec4<T>(0,  c, s, 0);
		rotate[2] = TVec4<T>(0, -s, c, 0);
		rotate[3] = TVec4<T>(0,  0, 0, 1);
		return (mat * rotate);
	}

	template <typename T>
	TMat4<T> TMat4<T>::rotateY(TMat4<T> mat, T angle)
	{
		T c = cos(angle);
		T s = sin(angle);
		TMat4<T> rotate;
		rotate[0] = TVec4<T>(c, 0, -s, 0);
		rotate[1] = TVec4<T>(0, 1,  0, 0);
		rotate[2] = TVec4<T>(s, 0,  c, 0);
		rotate[3] = TVec4<T>(0, 0,  0, 1);
		return (mat * rotate);
	}

	template <typename T>
	TMat4<T> TMat4<T>::rotateZ(TMat4<T> mat, T angle)
	{
		T c = cos(angle);
		T s = sin(angle);
		TMat4<T> rotate;
		rotate[0] = TVec4<T>( c, s, 0, 0);
		rotate[1] = TVec4<T>(-s, c, 0, 0);
		rotate[2] = TVec4<T>( 0, 0, 1, 0);
		rotate[3] = TVec4<T>( 0, 0, 0, 1);
		return (mat * rotate);
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
		T f = 1 / tan(fov / 2);
		TMat4<T> mat(TVec4<T>(f / aspect, f, (zfar + znear) / (znear - zfar), 0));
		mat[2][3] = -1;
		mat[3][2] = (2 * zfar * znear) / (znear - zfar);
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
		mat[0] = TVec4<T>(s[0], u[0], f[0], 0);
		mat[1] = TVec4<T>(s[1], u[1], f[1], 0);
		mat[2] = TVec4<T>(s[2], u[2], f[2], 0);
		mat[3] = TVec4<T>(0   , 0   , 0   , 1);
		return (translate(mat, TVec3<T>(-eye)));
	}

	template <typename T>
	TMat4<T> TMat4<T>::ortho(T left, T right, T bottom, T top, T near, T far)
	{
		TMat4<T> mat(TVec4<T>(2 / (right - left), 2 / (top - bottom), -2 / (far - near), 1));
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
