#ifndef MAT2_CPP
# define MAT2_CPP

#include "Mat2.h"

namespace librender
{

	template <typename T>
	TMat2<T>::TMat2(TVec2<T> vec)
	{
		this->data[0] = TVec2<T>(vec.x, 0);
		this->data[1] = TVec2<T>(0, vec.y);
	}

	template <typename T>
	TMat2<T>::TMat2(T value)
	{
		this->data[0] = TVec2<T>(value, 0);
		this->data[1] = TVec2<T>(0, value);
	}

	template <typename T>
	TVec2<T> &TMat2<T>::operator [] (int i)
	{
		return (this->data[i]);
	}

	template <typename T>
	TMat2<T> TMat2<T>::operator * (TMat2<T> mat)
	{
		TMat2<T> result;
		for (int i = 0; i < 2; ++i)
			result[i] = (*this)[0] * mat[i][0] + (*this)[1] * mat[i][1];
		return (result);
	}

	template <typename T>
	TVec2<T> operator * (TMat2<T> mat, TVec2<T> vec)
	{
		TVec2<T> result;
		for (int i = 0; i < 2; ++i)
			result[i] = vec.x * mat[0][i] + vec.y * mat[1][i];
		return (result);
	}

	template <typename T>
	TVec2<T> operator * (TVec2<T> vec, TMat2<T> mat)
	{
		TVec2<T> result;
		for (int i = 0; i < 2; ++i)
			result[i] = vec.x * mat[i].x + vec.y * mat[i].y;
		return (result);
	}

}

#endif
