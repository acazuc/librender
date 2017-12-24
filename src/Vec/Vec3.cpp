#ifndef VEC3_CPP
# define VEC3_CPP

#include "Vec3.h"
#include <algorithm>
#include <cmath>

namespace librender
{

	template <typename T>
	TVec3<T> TVec3<T>::reflect(TVec3<T> vec)
	{
		return (*this - vec * 2 * this->dot(vec));
	}

	template <typename T>
	TVec3<T> TVec3<T>::cross(TVec3<T> vec)
	{
		return (TVec3<T>(this->y * vec.z - this->z * vec.y, this->z * vec.x - this->x * vec.z, this->x * vec.y - this->y * vec.x));
	}

	template <typename T>
	T TVec3<T>::dot(TVec3<T> vec)
	{
		return (this->x * vec.x + this->y * vec.y + this->z * vec.z);
	}

	template <typename T>
	T TVec3<T>::angle(TVec3<T> vec)
	{
		return (acos(dot(vec) / (length() * vec.length())));
	}

	template <typename T>
	T TVec3<T>::length()
	{
		return (sqrt(dot(*this)));
	}

	template <typename T>
	void TVec3<T>::normalize()
	{
		*this /= this->length();
	}

	template <typename T>
	void TVec3<T>::min(T val)
	{
		this->x = std::min(val, this->x);
		this->y = std::min(val, this->y);
		this->z = std::min(val, this->z);
	}

	template <typename T>
	void TVec3<T>::max(T val)
	{
		this->x = std::max(val, this->x);
		this->y = std::max(val, this->y);
		this->z = std::max(val, this->z);
	}

	template <typename T>
	void TVec3<T>::clamp(T min, T max)
	{
		this->max(min);
		this->min(max);
	}

	template <typename T>
	T &TVec3<T>::operator [] (int idx)
	{
		return (reinterpret_cast<T*>(this)[idx]);
	}

	template <typename T>
	TVec3<T> TVec3<T>::operator - ()
	{
		return (TVec3<T>(-this->x, -this->y, -this->z));
	}

	template <typename T>
	TVec3<T> TVec3<T>::operator + (T val)
	{
		return (TVec3<T>(this->x + val, this->y + val, this->z + val));
	}

	template <typename T>
	TVec3<T> TVec3<T>::operator - (T val)
	{
		return (TVec3<T>(this->x - val, this->y - val, this->z - val));
	}

	template <typename T>
	TVec3<T> TVec3<T>::operator * (T val)
	{
		return (TVec3<T>(this->x * val, this->y * val, this->z * val));
	}

	template <typename T>
	TVec3<T> TVec3<T>::operator / (T val)
	{
		return (TVec3<T>(this->x / val, this->y / val, this->z / val));
	}

	template <typename T>
	TVec3<T> TVec3<T>::operator + (TVec3<T> vec)
	{
		return (TVec3<T>(this->x + vec.x, this->y + vec.y, this->z + vec.z));
	}

	template <typename T>
	TVec3<T> TVec3<T>::operator - (TVec3<T> vec)
	{
		return (TVec3<T>(this->x - vec.x, this->y - vec.y, this->z - vec.z));
	}

	template <typename T>
	TVec3<T> TVec3<T>::operator * (TVec3<T> vec)
	{
		return (TVec3<T>(this->x * vec.x, this->y * vec.y, this->z * vec.z));
	}

	template <typename T>
	TVec3<T> TVec3<T>::operator / (TVec3<T> vec)
	{
		return (TVec3<T>(this->x / vec.x, this->y / vec.y, this->z / vec.z));
	}

	template <typename T>
	TVec3<T> TVec3<T>::operator += (T val)
	{
		return (*this = *this + val);
	}

	template <typename T>
	TVec3<T> TVec3<T>::operator -= (T val)
	{
		return (*this = *this - val);
	}

	template <typename T>
	TVec3<T> TVec3<T>::operator *= (T val)
	{
		return (*this = *this * val);
	}

	template <typename T>
	TVec3<T> TVec3<T>::operator /= (T val)
	{
		return (*this = *this / val);
	}

	template <typename T>
	TVec3<T> TVec3<T>::operator += (TVec3<T> vec)
	{
		return (*this = *this + vec);
	}

	template <typename T>
	TVec3<T> TVec3<T>::operator -= (TVec3<T> vec)
	{
		return (*this = *this - vec);
	}

	template <typename T>
	TVec3<T> TVec3<T>::operator *= (TVec3<T> vec)
	{
		return (*this = *this * vec);
	}

	template <typename T>
	TVec3<T> TVec3<T>::operator /= (TVec3<T> vec)
	{
		return (*this = *this / vec);
	}

	template <typename T>
	bool TVec3<T>::operator == (TVec3<T> vec)
	{
		return (this->x == vec.x && this->y == vec.y && this->z == vec.z);
	}

	template <typename T>
	bool TVec3<T>::operator != (TVec3<T> vec)
	{
		return (!(*this == vec));
	}

}

#endif
