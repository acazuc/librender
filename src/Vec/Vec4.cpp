#ifndef VEC4_CPP
# define VEC4_CPP

#include "Vec4.h"
#include <cmath>

namespace librender
{

	template <typename T>
	TVec4<T>::TVec4(TVec2<T> xy, TVec2<T> zw)
	: x(xy.x)
	, y(xy.y)
	, z(zw.x)
	, w(zw.y)
	{
		//Empty
	}

	template <typename T>
	TVec4<T>::TVec4(TVec2<T> xy, T z, T w)
	: x(xy.x)
	, y(xy.y)
	, z(z)
	, w(w)
	{
		//Empty
	}

	template <typename T>
	TVec4<T>::TVec4(T x, TVec2<T> yz, T w)
	: x(x)
	, y(yz.x)
	, z(yz.y)
	, w(w)
	{
		//Empty
	}

	template <typename T>
	TVec4<T>::TVec4(T x, T y, TVec2<T> zw)
	: x(x)
	, y(y)
	, z(zw.x)
	, w(zw.y)
	{
		//Empty
	}

	template <typename T>
	TVec4<T>::TVec4(TVec3<T> xyz, T w)
	: x(xyz.x)
	, y(xyz.y)
	, z(xyz.z)
	, w(w)
	{
		//Empty
	}

	template <typename T>
	TVec4<T>::TVec4(T x, TVec3<T> yzw)
	: x(x)
	, y(yzw.x)
	, z(yzw.y)
	, w(yzw.z)
	{
		//Empty
	}

	template <typename T>
	TVec4<T>::TVec4(T x, T y, T z, T w)
	: x(x)
	, y(y)
	, z(z)
	, w(w)
	{
		//Empty
	}

	template <typename T>
	TVec4<T>::TVec4(T xyzw)
	: x(xyzw)
	, y(xyzw)
	, z(xyzw)
	, w(xyzw)
	{
		//Empty
	}

	template <typename T>
	TVec4<T>::TVec4()
	{
		//Empty
	}

	template <typename T>
	TVec3<T> TVec4<T>::xyz()
	{
		return TVec3<T>(this->x, this->y, this->z);
	}

	template <typename T>
	TVec3<T> TVec4<T>::rgb()
	{
		return TVec3<T>(this->r, this->g, this->b);
	}

	template <typename T>
	TVec2<T> TVec4<T>::xy()
	{
		return TVec2<T>(this->x, this->y);
	}

	template <typename T>
	TVec2<T> TVec4<T>::zw()
	{
		return TVec2<T>(this->z, this->w);
	}

	template <typename T>
	T &TVec4<T>::operator [] (int idx)
	{
		return reinterpret_cast<T*>(this)[idx];
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator - ()
	{
		return TVec4<T>(-this->x, -this->y, -this->z, -this->w);
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator += (T val)
	{
		return *this = *this + val;
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator -= (T val)
	{
		return *this = *this - val;
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator *= (T val)
	{
		return *this = *this * val;
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator /= (T val)
	{
		return *this = *this / val;
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator += (TVec4<T> vec)
	{
		return *this = *this + vec;
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator -= (TVec4<T> vec)
	{
		return *this = *this - vec;
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator *= (TVec4<T> vec)
	{
		return *this = *this * vec;
	}

	template <typename T>
	TVec4<T> TVec4<T>::operator /= (TVec4<T> vec)
	{
		return *this = *this / vec;
	}

	template <typename T>
	bool TVec4<T>::operator == (TVec4<T> vec)
	{
		return this->x == vec.x && this->y == vec.y && this->z == vec.z && this->w == vec.w;
	}

	template <typename T>
	bool TVec4<T>::operator != (TVec4<T> vec)
	{
		return !(*this == vec);
	}

	template <typename T>
	TVec4<T> operator + (TVec4<T> vec1, TVec4<T> vec2)
	{
		return TVec4<T>(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w + vec2.w);
	}

	template <typename T>
	TVec4<T> operator + (TVec4<T> vec, T val)
	{
		return TVec4<T>(vec.x + val, vec.y + val, vec.z + val, vec.w + val);
	}

	template <typename T>
	TVec4<T> operator + (T val, TVec4<T> vec)
	{
		return TVec4<T>(val + vec.x, val + vec.y, val + vec.z, val + vec.w);
	}

	template <typename T>
	TVec4<T> operator - (TVec4<T> vec1, TVec4<T> vec2)
	{
		return TVec4<T>(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);
	}

	template <typename T>
	TVec4<T> operator - (TVec4<T> vec, T val)
	{
		return TVec4<T>(vec.x - val, vec.y - val, vec.z - val, vec.w - val);
	}

	template <typename T>
	TVec4<T> operator - (T val, TVec4<T> vec)
	{
		return TVec4<T>(val - vec.x, val - vec.y, val - vec.z, val - vec.w);
	}

	template <typename T>
	TVec4<T> operator * (TVec4<T> vec1, TVec4<T> vec2)
	{
		return TVec4<T>(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z, vec1.w * vec2.w);
	}

	template <typename T>
	TVec4<T> operator * (TVec4<T> vec, T val)
	{
		return TVec4<T>(vec.x * val, vec.y * val, vec.z * val, vec.w * val);
	}

	template <typename T>
	TVec4<T> operator * (T val, TVec4<T> vec)
	{
		return TVec4<T>(val * vec.x, val * vec.y, val * vec.z, val * vec.w);
	}

	template <typename T>
	TVec4<T> operator / (TVec4<T> vec1, TVec4<T> vec2)
	{
		return TVec4<T>(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z, vec1.w / vec2.w);
	}

	template <typename T>
	TVec4<T> operator / (TVec4<T> vec, T val)
	{
		return TVec4<T>(vec.x / val, vec.y / val, vec.z / val, vec.w / val);
	}

	template <typename T>
	TVec4<T> operator / (T val, TVec4<T> vec)
	{
		return TVec4<T>(val / vec.x, val / vec.y, val / vec.z, val / vec.w);
	}

	template <typename T>
	TVec4<T> min(TVec4<T> vec1, TVec4<T> vec2)
	{
		return TVec4<T>(vec1.x < vec2.x ? vec1.x : vec2.x, vec1.y < vec2.y ? vec1.y : vec2.y, vec1.z < vec2.z ? vec1.z : vec2.z, vec1.w < vec2.w ? vec1.w : vec2.w);
	}

	template <typename T>
	TVec4<T> min(TVec4<T> vec, T val)
	{
		return TVec4<T>(val < vec.x ? val : vec.x, val < vec.y ? val : vec.y, val < vec.z ? val : vec.z, val < vec.w ? val : vec.w);
	}

	template <typename T>
	TVec4<T> min(T val, TVec4<T> vec)
	{
		return TVec4<T>(val < vec.x ? val : vec.x, val < vec.y ? val : vec.y, val < vec.z ? val : vec.z, val < vec.w ? val : vec.w);
	}

	template <typename T>
	TVec4<T> max(TVec4<T> vec1, TVec4<T> vec2)
	{
		return TVec4<T>(vec1.x > vec2.x ? vec1.x : vec2.x, vec1.y > vec2.y ? vec1.y : vec2.y, vec1.z > vec2.z ? vec1.z : vec2.z, vec1.w > vec2.w ? vec1.w : vec2.w);
	}

	template <typename T>
	TVec4<T> max(TVec4<T> vec, T val)
	{
		return TVec4<T>(val > vec.x ? val : vec.x, val > vec.y ? val : vec.y, val > vec.z ? val : vec.z, val > vec.w ? val : vec.w);
	}

	template <typename T>
	TVec4<T> max(T val, TVec4<T> vec)
	{
		return TVec4<T>(val > vec.x ? val : vec.x, val > vec.y ? val : vec.y, val > vec.z ? val : vec.z, val > vec.w ? val : vec.w);
	}

	template <typename T>
	TVec4<T> clamp(TVec4<T> vec, T vmin, T vmax)
	{
		return max(min(vec, vmax), vmin);
	}

	template <typename T>
	TVec4<T> clamp(TVec4<T> vec, TVec4<T> vmin, TVec4<T> vmax)
	{
		return max(min(vec, vmax), vmin);
	}

	template <typename T>
	TVec4<T> mix(TVec4<T> vec1, TVec4<T> vec2, T a)
	{
		return vec1 * (T(1) - a) + vec2 * a;
	}

	template <typename T>
	TVec4<T> mod(TVec4<T> vec1, TVec4<T> vec2)
	{
		return TVec4<T>(std::fmod(vec1.x, vec2.x), std::fmod(vec1.y, vec2.y), std::fmod(vec1.z, vec2.z), std::fmod(vec1.w, vec2.w));
	}

	template <typename T>
	TVec4<T> mod(TVec4<T> vec, T val)
	{
		return TVec4<T>(std::fmod(vec.x, val), std::fmod(vec.y, val), std::fmod(vec.z, val), std::fmod(vec.w, val));
	}

	template <typename T>
	TVec4<T> floor(TVec4<T> vec)
	{
		return TVec4<T>(std::floor(vec.x), std::floor(vec.y), std::floor(vec.z), std::floor(vec.w));
	}

	template <typename T>
	TVec4<T> round(TVec4<T> vec)
	{
		return TVec4<T>(std::round(vec.x), std::round(vec.y), std::round(vec.z), std::round(vec.w));
	}

	template <typename T>
	TVec4<T> ceil(TVec4<T> vec)
	{
		return TVec4<T>(std::ceil(vec.x), std::ceil(vec.y), std::ceil(vec.z), std::ceil(vec.w));
	}

	template <typename T>
	TVec4<T> fract(TVec4<T> vec)
	{
		return vec - floor(vec);
	}

	template<typename T>
	TVec4<T> normalize(TVec4<T> vec)
	{
		return vec / length(vec);
	}

	template<typename T>
	TVec4<T> reflect(TVec4<T> vec1, TVec4<T> vec2)
	{
		return vec1 - vec2 * T(2) * dot(vec1, vec2);
	}

	template<typename T>
	T dot(TVec4<T> vec1, TVec4<T> vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w;
	}

	template<typename T>
	T angle(TVec4<T> vec1, TVec4<T> vec2)
	{
		return acos(dot(vec1, vec2) / length(vec1) / length(vec2));
	}

	template<typename T>
	T length(TVec4<T> vec)
	{
		return std::sqrt(dot(vec, vec));
	}

}

#endif
