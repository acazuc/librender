#ifndef VEC2_CPP
# define VEC2_CPP

#include "Vec2.h"
#include <algorithm>
#include <cmath>

namespace librender
{

	template <typename T>
	T &TVec2<T>::operator [] (int idx)
	{
		return reinterpret_cast<T*>(this)[idx];
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator - ()
	{
		return TVec2<T>(-this->x, -this->y);
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator += (T val)
	{
		return *this = *this + val;
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator -= (T val)
	{
		return *this = *this - val;
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator *= (T val)
	{
		return *this = *this * val;
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator /= (T val)
	{
		return *this = *this / val;
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator += (TVec2<T> vec)
	{
		return *this = *this + vec;
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator -= (TVec2<T> vec)
	{
		return *this = *this - vec;
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator *= (TVec2<T> vec)
	{
		return *this = *this * vec;
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator /= (TVec2<T> vec)
	{
		return *this = *this / vec;
	}

	template <typename T>
	bool TVec2<T>::operator == (TVec2<T> vec)
	{
		return this->x == vec.x && this->y == vec.y;
	}

	template <typename T>
	bool TVec2<T>::operator != (TVec2<T> vec)
	{
		return !(*this == vec);
	}

	template <typename T>
	TVec2<T> operator + (TVec2<T> vec1, TVec2<T> vec2)
	{
		return TVec2<T>(vec1.x + vec2.x, vec1.y + vec2.y);
	}

	template <typename T>
	TVec2<T> operator + (TVec2<T> vec, T val)
	{
		return TVec2<T>(vec.x + val, vec.y + val);
	}

	template <typename T>
	TVec2<T> operator + (T val, TVec2<T> vec)
	{
		return TVec2<T>(val + vec.x, val + vec.y);
	}

	template <typename T>
	TVec2<T> operator - (TVec2<T> vec1, TVec2<T> vec2)
	{
		return TVec2<T>(vec1.x - vec2.x, vec1.y - vec2.y);
	}

	template <typename T>
	TVec2<T> operator - (TVec2<T> vec, T val)
	{
		return TVec2<T>(vec.x - val, vec.y - val);
	}

	template <typename T>
	TVec2<T> operator - (T val, TVec2<T> vec)
	{
		return TVec2<T>(val - vec.x, val - vec.y);
	}

	template <typename T>
	TVec2<T> operator * (TVec2<T> vec1, TVec2<T> vec2)
	{
		return TVec2<T>(vec1.x * vec2.x, vec1.y * vec2.y);
	}

	template <typename T>
	TVec2<T> operator * (TVec2<T> vec, T val)
	{
		return TVec2<T>(vec.x * val, vec.y * val);
	}

	template <typename T>
	TVec2<T> operator * (T val, TVec2<T> vec)
	{
		return TVec2<T>(val * vec.x, val * vec.y);
	}

	template <typename T>
	TVec2<T> operator / (TVec2<T> vec1, TVec2<T> vec2)
	{
		return TVec2<T>(vec1.x / vec2.x, vec1.y / vec2.y);
	}

	template <typename T>
	TVec2<T> operator / (TVec2<T> vec, T val)
	{
		return TVec2<T>(vec.x / val, vec.y / val);
	}

	template <typename T>
	TVec2<T> operator / (T val, TVec2<T> vec)
	{
		return TVec2<T>(val / vec.x, val / vec.y);
	}

	template <typename T>
	TVec2<T> min(TVec2<T> vec1, TVec2<T> vec2)
	{
		return TVec2<T>(std::min(vec1.x, vec2.x), std::min(vec1.y, vec2.y));
	}

	template <typename T>
	TVec2<T> min(TVec2<T> vec, T val)
	{
		return TVec2<T>(std::min(val, vec.x), std::min(val, vec.y));
	}

	template <typename T>
	TVec2<T> min(T val, TVec2<T> vec)
	{
		return TVec2<T>(std::min(val, vec.x), std::min(val, vec.y));
	}

	template <typename T>
	TVec2<T> max(TVec2<T> vec1, TVec2<T> vec2)
	{
		return TVec2<T>(std::max(vec1.x, vec2.x), std::max(vec1.y, vec2.y));
	}

	template <typename T>
	TVec2<T> max(TVec2<T> vec, T val)
	{
		return TVec2<T>(std::max(val, vec.x), std::max(val, vec.y));
	}

	template <typename T>
	TVec2<T> max(T val, TVec2<T> vec)
	{
		return TVec2<T>(std::max(val, vec.x), std::max(val, vec.y));
	}

	template <typename T>
	TVec2<T> clamp(TVec2<T> vec, T min, T max)
	{
		return max(min, min(max));
	}

	template <typename T>
	TVec2<T> clamp(TVec2<T> vec, TVec2<T> min, TVec2<T> max)
	{
		return max(min, min(max));
	}

	template <typename T>
	TVec2<T> mix(TVec2<T> vec1, TVec2<T> vec2, T a)
	{
		return vec1 * (1 - a) + vec2 * a;
	}

	template <typename T>
	TVec2<T> mod(TVec2<T> vec, T val)
	{
		return TVec2<T>(std::fmod(vec.x, val), std::fmod(vec.y, val));
	}

	template <typename T>
	TVec2<T> floor(TVec2<T> vec)
	{
		return TVec2<T>(std::floor(vec.x), std::floor(vec.y));
	}

	template <typename T>
	TVec2<T> round(TVec2<T> vec)
	{
		return TVec2<T>(std::round(vec.x), std::round(vec.y));
	}

	template <typename T>
	TVec2<T> ceil(TVec2<T> vec)
	{
		return TVec2<T>(std::ceil(vec.x), std::ceil(vec.y));
	}

	template <typename T>
	TVec2<T> fract(TVec2<T> vec)
	{
		return vec - floor(vec);
	}

	template<typename T>
	TVec2<T> normalize(TVec2<T> vec)
	{
		return vec / length(vec);
	}

	template<typename T>
	TVec2<T> reflect(TVec2<T> vec1, TVec2<T> vec2)
	{
		return vec1 - vec2 * 2 * dot(vec1, vec2);
	}

	template<typename T>
	T dot(TVec2<T> vec1, TVec2<T> vec2)
	{
		return vec1.x * vec2.x + vec1.y;
	}

	template<typename T>
	T angle(TVec2<T> vec1, TVec2<T> vec2)
	{
		return acos(dot(vec1, vec2) / length(vec1) / length(vec2));
	}

	template<typename T>
	T length(TVec2<T> vec)
	{
		return sqrt(dot(vec, vec));
	}

}

#endif
