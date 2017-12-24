#ifndef VEC2_CPP
# define VEC2_CPP

#include "Vec2.h"
#include <algorithm>
#include <cmath>

namespace librender
{

	template <typename T>
	T TVec2<T>::dot(TVec2<T> uv)
	{
		return (this->x * uv.x + this->y * uv.y);
	}

	template <typename T>
	T TVec2<T>::angle(TVec2<T> vec)
	{
		return (acos(dot(vec) / (length() * vec.length())));
	}

	template <typename T>
	T TVec2<T>::length()
	{
		return (sqrt(dot(*this)));
	}

	template <typename T>
	void TVec2<T>::normalize()
	{
		*this = *this / this->length();
	}

	template <typename T>
	void TVec2<T>::min(T val)
	{
		this->x = std::min(val, this->x);
		this->y = std::min(val, this->y);
	}

	template <typename T>
	void TVec2<T>::max(T val)
	{
		this->x = std::max(val, this->x);
		this->y = std::max(val, this->y);
	}

	template <typename T>
	void TVec2<T>::clamp(T min, T max)
	{
		this->max(min);
		this->min(max);
	}

	template <typename T>
	T &TVec2<T>::operator [] (int idx)
	{
		return (reinterpret_cast<T*>(this)[idx]);
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator + (T val)
	{
		return (TVec2<T>(this->x + val, this->y + val));
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator - (T val)
	{
		return (TVec2<T>(this->x - val, this->y - val));
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator * (T val)
	{
		return (TVec2<T>(this->x * val, this->y * val));
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator / (T val)
	{
		return (TVec2<T>(this->x / val, this->y / val));
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator + (TVec2<T> vec)
	{
		return (TVec2<T>(this->x + vec.x, this->y + vec.y));
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator - (TVec2<T> vec)
	{
		return (TVec2<T>(this->x - vec.x, this->y - vec.y));
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator * (TVec2<T> vec)
	{
		return (TVec2<T>(this->x * vec.x, this->y * vec.y));
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator / (TVec2<T> vec)
	{
		return (TVec2<T>(this->x / vec.x, this->y / vec.y));
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator += (T val)
	{
		return (*this = *this + val);
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator -= (T val)
	{
		return (*this = *this - val);
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator *= (T val)
	{
		return (*this = *this * val);
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator /= (T val)
	{
		return (*this = *this / val);
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator += (TVec2<T> vec)
	{
		return (*this = *this + vec);
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator -= (TVec2<T> vec)
	{
		return (*this = *this - vec);
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator *= (TVec2<T> vec)
	{
		return (*this = *this * vec);
	}

	template <typename T>
	TVec2<T> TVec2<T>::operator /= (TVec2<T> vec)
	{
		return (*this = *this / vec);
	}

	template <typename T>
	bool TVec2<T>::operator == (TVec2<T> vec)
	{
		return (this->x == vec.x && this->y == vec.y);
	}

	template <typename T>
	bool TVec2<T>::operator != (TVec2<T> vec)
	{
		return (!(*this == vec));
	}

}

#endif
