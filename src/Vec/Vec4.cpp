#ifndef VEC4_CPP
# define VEC4_CPP

#include "Vec4.h"
#include <algorithm>
#include <cmath>

namespace librender
{

	template <typename T>
	T TVec4<T>::dot(TVec4<T> vec)
	{
		return (this->x * vec.x + this->y * vec.y + this->z * vec.z + this->w * vec.w);
	}

	template <typename T>
	T TVec4<T>::angle(TVec4<T> vec)
	{
		return (acos(dot(vec) / (length() * vec.length())));
	}

	template <typename T>
	T TVec4<T>::length()
	{
		return (sqrt(dot(*this)));
	}

	template <typename T>
	void TVec4<T>::normalize()
	{
		*this = *this / this->length();
	}

	template <typename T>
	void TVec4<T>::min(T val)
	{
		this->x = std::min(val, this->x);
		this->y = std::min(val, this->y);
		this->z = std::min(val, this->z);
		this->w = std::min(val, this->w);
	}

	template <typename T>
	void TVec4<T>::max(T val)
	{
		this->x = std::max(val, this->x);
		this->y = std::max(val, this->y);
		this->z = std::max(val, this->z);
		this->w = std::max(val, this->w);
	}

	template <typename T>
	void TVec4<T>::clamp(T min, T max)
	{
		this->max(min);
		this->min(max);
	}

	template <typename T>
	TVec3<T> TVec4<T>::xyz()
	{
		return (TVec3<T>(this->x, this->y, this->z));
	}

	template <typename T>
	TVec3<T> TVec4<T>::rgb()
	{
		return (TVec3<T>(this->r, this->g, this->b));
	}

	template <typename T>
	TVec2<T> TVec4<T>::xy()
	{
		return (TVec2<T>(this->x, this->y));
	}

	template <typename T>
	TVec2<T> TVec4<T>::zw()
	{
		return (TVec2<T>(this->z, this->w));
	}

	template <typename T>
	T &TVec4<T>::operator [] (int idx)
	{
		return (reinterpret_cast<T*>(this)[idx]);
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator + (T val)
	{
		return (TVec4(this->x + val, this->y + val, this->z + val, this->w + val));
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator - (T val)
	{
		return (TVec4(this->x - val, this->y - val, this->z - val, this->w - val));
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator * (T val)
	{
		return (TVec4(this->x * val, this->y * val, this->z * val, this->w * val));
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator / (T val)
	{
		return (TVec4(this->x / val, this->y / val, this->z / val, this->w / val));
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator + (TVec4<T> vec)
	{
		return (TVec4(this->x + vec.x, this->y + vec.y, this->z + vec.z, this->w + vec.w));
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator - (TVec4<T> vec)
	{
		return (TVec4(this->x - vec.x, this->y - vec.y, this->z - vec.z, this->w - vec.w));
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator * (TVec4<T> vec)
	{
		return (TVec4(this->x * vec.x, this->y * vec.y, this->z * vec.z, this->w * vec.w));
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator / (TVec4<T> vec)
	{
		return (TVec4(this->x / vec.x, this->y / vec.y, this->z / vec.z, this->w / vec.w));
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator += (T val)
	{
		return (*this = *this + val);
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator -= (T val)
	{
		return (*this = *this - val);
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator *= (T val)
	{
		return (*this = *this * val);
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator /= (T val)
	{
		return (*this = *this / val);
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator += (TVec4<T> vec)
	{
		return (*this = *this + vec);
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator -= (TVec4<T> vec)
	{
		return (*this = *this - vec);
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator *= (TVec4<T> vec)
	{
		return (*this = *this * vec);
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator /= (TVec4<T> vec)
	{
		return (*this = *this / vec);
	}

	template <typename T>
	bool TVec4<T>::operator == (TVec4<T> vec)
	{
		return (this->x == vec.x && this->y == vec.y && this->z == vec.z && this->w == vec.w);
	}

	template <typename T>
	bool TVec4<T>::operator != (TVec4<T> vec)
	{
		return (!(*this == vec));
	}

}

#endif
