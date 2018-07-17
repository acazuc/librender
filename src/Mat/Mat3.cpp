#ifndef MAT3_CPP
# define MAT3_CPP

#include "Mat3.h"
#include <cmath>

namespace librender
{

	template <typename T>
	TMat3<T>::TMat3(TVec3<T> vec)
	{
		this->data[0] = TVec3<T>(T(vec.x), T(0), T(0));
		this->data[1] = TVec3<T>(T(0), T(vec.y), T(0));
		this->data[2] = TVec3<T>(T(0), T(0), T(vec.z));
	}

	template <typename T>
	TMat3<T>::TMat3(T value)
	{
		this->data[0] = TVec3<T>(T(value), T(0), T(0));
		this->data[1] = TVec3<T>(T(0), T(value), T(0));
		this->data[2] = TVec3<T>(T(0), T(0), T(value));
	}

	template <typename T>
	TMat3<T> TMat3<T>::rotate(TMat3<T> mat, T angle, TVec3<T> axis)
	{
		T c(cos(angle));
		T s(sin(angle));
		TVec3<T> t(axis * T(T(1) - c));
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
		TMat3<T> result;
		result[0] = mat[0] * rotate[0][0] + mat[1] * rotate[0][1] + mat[2] * rotate[0][2];
		result[1] = mat[0] * rotate[1][0] + mat[1] * rotate[1][1] + mat[2] * rotate[1][2];
		result[2] = mat[0] * rotate[2][0] + mat[1] * rotate[2][1] + mat[2] * rotate[2][2];
		return result;
	}

	template <typename T>
	TMat3<T> TMat3<T>::rotateX(TMat3<T> mat, T angle)
	{
		T c(cos(angle));
		T s(sin(angle));
		TMat3<T> rotate;
		rotate[0] = TVec3<T>(T(1), T( 0), T(0));
		rotate[1] = TVec3<T>(T(0), T( c), T(s));
		rotate[2] = TVec3<T>(T(0), T(-s), T(c));
		TMat3<T> result;
		result[0] = mat[0];
		result[1] = mat[0] * rotate[1][0] + mat[1] * rotate[1][1] + mat[2] * rotate[1][2];
		result[2] = mat[0] * rotate[2][0] + mat[1] * rotate[2][1] + mat[2] * rotate[2][2];
		return result;
	}

	template <typename T>
	TMat3<T> TMat3<T>::rotateY(TMat3<T> mat, T angle)
	{
		T c(cos(angle));
		T s(sin(angle));
		TMat3<T> rotate;
		rotate[0] = TVec3<T>(T(c), T(0), T(-s));
		rotate[1] = TVec3<T>(T(0), T(1), T( 0));
		rotate[2] = TVec3<T>(T(s), T(0), T( c));
		TMat3<T> result;
		result[0] = mat[0] * rotate[0][0] + mat[1] * rotate[0][1] + mat[2] * rotate[0][2];
		result[1] = mat[1];
		result[2] = mat[0] * rotate[2][0] + mat[1] * rotate[2][1] + mat[2] * rotate[2][2];
		return result;
	}

	template <typename T>
	TMat3<T> TMat3<T>::rotateZ(TMat3<T> mat, T angle)
	{
		T c(cos(angle));
		T s(sin(angle));
		TMat3<T> rotate;
		rotate[0] = TVec3<T>(T( c), T(s), T(0));
		rotate[1] = TVec3<T>(T(-s), T(c), T(0));
		rotate[2] = TVec3<T>(T( 0), T(0), T(1));
		TMat3<T> result;
		result[0] = mat[0] * rotate[0][0] + mat[1] * rotate[0][1] + mat[2] * rotate[0][2];
		result[1] = mat[0] * rotate[1][0] + mat[1] * rotate[1][1] + mat[2] * rotate[1][2];
		result[2] = mat[2];
		return result;
	}

	template <typename T>
	TVec3<T> &TMat3<T>::operator [] (int i)
	{
		return this->data[i];
	}

	template <typename T>
	TMat3<T> operator * (TMat3<T> mat1, TMat3<T> mat2)
	{
		TMat3<T> result;
		for (int i = 0; i < 3; ++i)
			result[i] = mat1[0] * mat2[i][0] + mat1[1] * mat2[i][1] + mat1[2] * mat2[i][2];
		return result;
	}

	template <typename T>
	TVec3<T> operator * (TMat3<T> mat, TVec3<T> vec)
	{
		TVec3<T> result;
		for (int i = 0; i < 3; ++i)
			result[i] = vec.x * mat[0][i] + vec.y * mat[1][i] + vec.z * mat[2][i];
		return result;
	}

	template <typename T>
	TVec3<T> operator * (TVec3<T> vec, TMat3<T> mat)
	{
		TVec3<T> result;
		for (int i = 0; i < 3; ++i)
			result[i] = vec.x * mat[i].x + vec.y * mat[i].y + vec.z * mat[i].z;
		return result;
	}

}

#endif
