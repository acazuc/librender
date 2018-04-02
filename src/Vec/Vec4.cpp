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
		*this /= this->length();
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
	TVec4<T> TVec4<T>::operator - ()
	{
		return (TVec4<T>(-this->x, -this->y, -this->z, -this->w));
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

	template <typename T>
	TVec4<T> operator + (TVec4<T> vec1, TVec4<T> vec2)
	{
		return (TVec4<T>(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w + vec2.w));
	}

	template <typename T>
	TVec4<T> operator + (TVec4<T> vec, T val)
	{
		return (TVec4<T>(vec.x + val, vec.y + val, vec.z + val, vec.w + val));
	}

	template <typename T>
	TVec4<T> operator + (T val, TVec4<T> vec)
	{
		return (TVec4<T>(val + vec.x, val + vec.y, val + vec.z, val + vec.w));
	}

	template <typename T>
	TVec4<T> operator - (TVec4<T> vec1, TVec4<T> vec2)
	{
		return (TVec4<T>(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w));
	}

	template <typename T>
	TVec4<T> operator - (TVec4<T> vec, T val)
	{
		return (TVec4<T>(vec.x - val, vec.y - val, vec.z - val, vec.w - val));
	}

	template <typename T>
	TVec4<T> operator - (T val, TVec4<T> vec)
	{
		return (TVec4<T>(val - vec.x, val - vec.y, val - vec.z, val - vec.w));
	}

	template <typename T>
	TVec4<T> operator * (TVec4<T> vec1, TVec4<T> vec2)
	{
		return (TVec4<T>(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z, vec1.w * vec2.w));
	}

	template <typename T>
	TVec4<T> operator * (TVec4<T> vec, T val)
	{
		return (TVec4<T>(vec.x * val, vec.y * val, vec.z * val, vec.w * val));
	}

	template <typename T>
	TVec4<T> operator * (T val, TVec4<T> vec)
	{
		return (TVec4<T>(val * vec.x, val * vec.y, val * vec.z, val * vec.w));
	}

	template <typename T>
	TVec4<T> operator / (TVec4<T> vec1, TVec4<T> vec2)
	{
		return (TVec4<T>(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z, vec1.w / vec2.w));
	}

	template <typename T>
	TVec4<T> operator / (TVec4<T> vec, T val)
	{
		return (TVec4<T>(vec.x / val, vec.y / val, vec.z / val, vec.w / val));
	}

	template <typename T>
	TVec4<T> operator / (T val, TVec4<T> vec)
	{
		return (TVec4<T>(val / vec.x, val / vec.y, val / vec.z, val / vec.w));
	}

	template <typename T>
	TVec4<T> min(TVec4<T> vec1, TVec4<T> vec2)
	{
		return (TVec4<T>(std::min(vec1.x, vec2.x), std::min(vec1.y, vec2.y), std::min(vec1.z, vec2.z), std::min(vec1.w, vec2.w)));
	}

	template <typename T>
	TVec4<T> min(TVec4<T> vec, T val)
	{
		return (TVec4<T>(std::min(val, vec.x), std::min(val, vec.y), std::min(val, vec.z), std::min(val, vec.w)));
	}

	template <typename T>
	TVec4<T> min(T val, TVec4<T> vec)
	{
		return (TVec4<T>(std::min(val, vec.x), std::min(val, vec.y), std::min(val, vec.z), std::min(val, vec.w)));
	}

	template <typename T>
	TVec4<T> max(TVec4<T> vec1, TVec4<T> vec2)
	{
		return (TVec4<T>(std::max(vec1.x, vec2.x), std::max(vec1.y, vec2.y), std::max(vec1.z, vec2.z), std::max(vec1.w, vec2.w)));
	}

	template <typename T>
	TVec4<T> max(TVec4<T> vec, T val)
	{
		return (TVec4<T>(std::max(val, vec.x), std::max(val, vec.y), std::max(val, vec.z), std::max(val, vec.w)));
	}

	template <typename T>
	TVec4<T> max(T val, TVec4<T> vec)
	{
		return (TVec4<T>(std::max(val, vec.x), std::max(val, vec.y), std::max(val, vec.z), std::max(val, vec.w)));
	}

	template <typename T>
	TVec4<T> mix(TVec4<T> vec1, TVec4<T> vec2, T a)
	{
		return (vec1 * (1 - a) + vec2 * a);
	}

	template <typename T>
	TVec4<T> clamp(TVec4<T> vec, T min, T max)
	{
		return (max(min, min(max)));
	}

	template <typename T>
	TVec4<T> mod(TVec4<T> vec, T val)
	{
		return (TVec4<T>(std::fmod(vec.x, val), std::fmod(vec.y, val), std::fmod(vec.z, val), std::fmod(vec.w, val)));
	}

	template <typename T>
	TVec4<T> floor(TVec4<T> vec)
	{
		return (TVec4<T>(std::floor(vec.x), std::floor(vec.y), std::floor(vec.z), std::floor(vec.w)));
	}

	template <typename T>
	TVec4<T> round(TVec4<T> vec)
	{
		return (TVec4<T>(std::round(vec.x), std::round(vec.y), std::round(vec.z), std::round(vec.w)));
	}

	template <typename T>
	TVec4<T> ceil(TVec4<T> vec)
	{
		return (TVec4<T>(std::ceil(vec.x), std::ceil(vec.y), std::ceil(vec.z), std::ceil(vec.w)));
	}

	template <typename T>
	TVec4<T> fract(TVec4<T> vec)
	{
		return (vec - floor(vec));
	}

}

#endif
