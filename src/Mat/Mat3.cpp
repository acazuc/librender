#ifndef MAT3_CPP
# define MAT3_CPP

#include "Mat3.h"
#include <cmath>

namespace librender
{

	template <typename T>
	TMat3<T>::TMat3(TVec3<T> vec)
	{
		this->data[0] = TVec3<T>(vec.x, 0, 0);
		this->data[1] = TVec3<T>(0, vec.y, 0);
		this->data[2] = TVec3<T>(0, 0, vec.z);
	}

	template <typename T>
	TMat3<T>::TMat3(T value)
	{
		this->data[0] = TVec3<T>(value, 0, 0);
		this->data[1] = TVec3<T>(0, value, 0);
		this->data[2] = TVec3<T>(0, 0, value);
	}

	template <typename T>
	TVec3<T> &TMat3<T>::operator [] (int i)
	{
		return (this->data[i]);
	}

	template <typename T>
	TMat3<T> TMat3<T>::rotateX(TMat3<T> mat, T angle)
	{
		T c = cos(angle);
		T s = sin(angle);
		TMat3<T> rotate;
		rotate[0] = TVec3<T>(1,  0, 0);
		rotate[1] = TVec3<T>(0,  c, s);
		rotate[2] = TVec3<T>(0, -s, c);
		return (mat * rotate);
	}

	template <typename T>
	TMat3<T> TMat3<T>::rotateY(TMat3<T> mat, T angle)
	{
		T c = cos(angle);
		T s = sin(angle);
		TMat3<T> rotate;
		rotate[0] = TVec3<T>(c, 0, -s);
		rotate[1] = TVec3<T>(0, 1,  0);
		rotate[2] = TVec3<T>(s, 0,  c);
		return (mat * rotate);
	}

	template <typename T>
	TMat3<T> TMat3<T>::rotateZ(TMat3<T> mat, T angle)
	{
		T c = cos(angle);
		T s = sin(angle);
		TMat3<T> rotate;
		rotate[0] = TVec3<T>( c, s, 0);
		rotate[1] = TVec3<T>(-s, c, 0);
		rotate[2] = TVec3<T>( 0, 0, 1);
		return (mat * rotate);
	}

	template <typename T>
	TMat3<T> TMat3<T>::operator * (TMat3<T> mat)
	{
		TMat3<T> result;
		for (int i = 0; i < 3; ++i)
			result[i] = (*this)[0] * mat[i][0] + (*this)[1] * mat[i][1] + (*this)[2] * mat[i][2];
		return (result);
	}

	template <typename T>
	TVec3<T> operator * (TMat3<T> mat, TVec3<T> vec)
	{
		TVec3<T> result;
		for (int i = 0; i < 3; ++i)
			result[i] = vec.x * mat[0][i] + vec.y * mat[1][i] + vec.z * mat[2][i];
		return (result);
	}

	template <typename T>
	TVec3<T> operator * (TVec3<T> vec, TMat3<T> mat)
	{
		TVec3<T> result;
		for (int i = 0; i < 3; ++i)
			result[i] = vec.x * mat[i].x + vec.y * mat[i].y + vec.z * mat[i].z;
		return (result);
	}

}

#endif
