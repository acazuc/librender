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
	T &TVec3<T>::operator [] (int idx)
	{
		return (reinterpret_cast<T*>(this)[idx]);
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

	template <typename T>
	TVec3<T> operator + (TVec3<T> vec, T val)
	{
		return (TVec3<T>(vec.x + val, vec.y + val, vec.z + val));
	}

	template <typename T>
	TVec3<T> operator + (T val, TVec3<T> vec)
	{
		return (TVec3<T>(val + vec.x, val + vec.y, val + vec.z));
	}

	template <typename T>
	TVec3<T> operator - (TVec3<T> vec, T val)
	{
		return (TVec3<T>(vec.x - val, vec.y - val, vec.z - val));
	}

	template <typename T>
	TVec3<T> operator - (T val, TVec3<T> vec)
	{
		return (TVec3<T>(val - vec.x, val - vec.y, val - vec.z));
	}

	template <typename T>
	TVec3<T> operator * (TVec3<T> vec, T val)
	{
		return (TVec3<T>(vec.x * val, vec.y * val, vec.z * val));
	}

	template <typename T>
	TVec3<T> operator * (T val, TVec3<T> vec)
	{
		return (TVec3<T>(val * vec.x, val * vec.y, val * vec.z));
	}

	template <typename T>
	TVec3<T> operator / (TVec3<T> vec, T val)
	{
		return (TVec3<T>(vec.x / val, vec.y / val, vec.z / val));
	}

	template <typename T>
	TVec3<T> operator / (T val, TVec3<T> vec)
	{
		return (TVec3<T>(val / vec.x, val / vec.y, val / vec.z));
	}

	template <typename T>
	TVec3<T> min(TVec3<T> vec1, TVec3<T> vec2)
	{
		return (TVec3<T>(std::min(vec1.x, vec2.x), std::min(vec1.y, vec2.y), std::min(vec1.z, vec2.z)));
	}

	template <typename T>
	TVec3<T> min(TVec3<T> vec, T val)
	{
		return (TVec3<T>(std::min(val, vec.x), std::min(val, vec.y), std::min(val, vec.z)));
	}

	template <typename T>
	TVec3<T> min(T val, TVec3<T> vec)
	{
		return (TVec3<T>(std::min(val, vec.x), std::min(val, vec.y), std::min(val, vec.z)));
	}

	template <typename T>
	TVec3<T> max(TVec3<T> vec1, TVec3<T> vec2)
	{
		return (TVec3<T>(std::max(vec1.x, vec2.x), std::max(vec1.y, vec2.y), std::max(vec1.z, vec2.z)));
	}

	template <typename T>
	TVec3<T> max(TVec3<T> vec, T val)
	{
		return (TVec3<T>(std::max(val, vec.x), std::max(val, vec.y), std::max(val, vec.z)));
	}

	template <typename T>
	TVec3<T> max(T val, TVec3<T> vec)
	{
		return (TVec3<T>(std::max(val, vec.x), std::max(val, vec.y), std::max(val, vec.z)));
	}

	template <typename T>
	TVec3<T> clamp(TVec3<T> vec, T min, T max)
	{
		return (max(min, min(max)));
	}

	template <typename T>
	TVec3<T> mod(TVec3<T> vec, T val)
	{
		return (TVec3<T>(std::fmod(vec.x, val), std::fmod(vec.y, val), std::fmod(vec.z, val)));
	}

	template <typename T>
	TVec3<T> floor(TVec3<T> vec)
	{
		return (TVec3<T>(std::floor(vec.x), std::floor(vec.y), std::floor(vec.z)));
	}

	template <typename T>
	TVec3<T> round(TVec3<T> vec)
	{
		return (TVec3<T>(std::round(vec.x), std::round(vec.y), std::round(vec.z)));
	}

	template <typename T>
	TVec3<T> ceil(TVec3<T> vec)
	{
		return (TVec3<T>(std::ceil(vec.x), std::ceil(vec.y), std::ceil(vec.z)));
	}

	template <typename T>
	TVec3<T> fract(TVec3<T> vec)
	{
		return (vec - floor(vec));
	}

}

#endif
