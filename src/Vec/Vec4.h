#ifndef VEC4_H
# define VEC4_H

# include "./Vec3.h"
# include "./Vec2.h"

namespace librender
{

	template <typename T> class TVec4
	{

	public:
		union {T x, r;};
		union {T y, g;};
		union {T z, b;};
		union {T w, a;};
		TVec4(TVec2<T> xy, TVec2<T> zw);
		TVec4(TVec2<T> xy, T z, T w);
		TVec4(T x, TVec2<T> yz, T w);
		TVec4(T x, T y, TVec2<T> zw);
		TVec4(TVec3<T> xyz, T w);
		TVec4(T x, TVec3<T> yzw);
		TVec4(T x, T y, T z, T w);
		TVec4(T xyzw);
		TVec4();
		TVec3<T> xyz();
		TVec3<T> rgb();
		TVec2<T> xy();
		TVec2<T> zw();
		T &operator [] (int idx);
		TVec4<T> operator - ();
		TVec4<T> operator += (T val);
		TVec4<T> operator -= (T val);
		TVec4<T> operator *= (T val);
		TVec4<T> operator /= (T val);
		TVec4<T> operator += (TVec4<T> vec);
		TVec4<T> operator -= (TVec4<T> vec);
		TVec4<T> operator *= (TVec4<T> vec);
		TVec4<T> operator /= (TVec4<T> vec);
		bool operator == (TVec4<T> vec);
		bool operator != (TVec4<T> vec);

	};

	template <typename T>
	TVec4<T> operator + (TVec4<T> vec1, TVec4<T> vec2);
	template <typename T>
	TVec4<T> operator + (TVec4<T> vec, T val);
	template <typename T>
	TVec4<T> operator + (T val, TVec4<T> vec);
	template <typename T>
	TVec4<T> operator - (TVec4<T> vec1, TVec4<T> vec2);
	template <typename T>
	TVec4<T> operator - (TVec4<T> vec, T val);
	template <typename T>
	TVec4<T> operator - (T val, TVec4<T> vec);
	template <typename T>
	TVec4<T> operator * (TVec4<T> vec1, TVec4<T> vec2);
	template <typename T>
	TVec4<T> operator * (TVec4<T> vec, T val);
	template <typename T>
	TVec4<T> operator * (T val, TVec4<T> vec);
	template <typename T>
	TVec4<T> operator / (TVec4<T> vec1, TVec4<T> vec2);
	template <typename T>
	TVec4<T> operator / (TVec4<T> vec, T val);
	template <typename T>
	TVec4<T> operator / (T val, TVec4<T> vec);

	template <typename T>
	TVec4<T> min(TVec4<T> vec1, TVec4<T> vec2);
	template <typename T>
	TVec4<T> min(TVec4<T> vec, T val);
	template <typename T>
	TVec4<T> min(T val, TVec4<T> vec);

	template <typename T>
	TVec4<T> max(TVec4<T> vec1, TVec4<T> vec2);
	template <typename T>
	TVec4<T> max(TVec4<T> vec, T val);
	template <typename T>
	TVec4<T> max(T val, TVec4<T> vec);

	template <typename T>
	TVec4<T> clamp(TVec4<T> vec, T vmin, T vmax);
	template <typename T>
	TVec4<T> clamp(TVec4<T> vec, TVec4<T> vmin, TVec4<T> vmax);

	template <typename T>
	TVec4<T> mix(TVec4<T> vec1, TVec4<T> vec2, T per);
	template <typename T>
	TVec4<T> mod(TVec4<T> vec1, TVec4<T> vec2);
	template <typename T>
	TVec4<T> mod(TVec4<T> vec, T val);
	template <typename T>
	TVec4<T> floor(TVec4<T> vec);
	template <typename T>
	TVec4<T> round(TVec4<T> vec);
	template <typename T>
	TVec4<T> ceil(TVec4<T> vec);
	template <typename T>
	TVec4<T> fract(TVec4<T> vec);

	template<typename T>
	TVec4<T> normalize(TVec4<T> vec);
	template<typename T>
	TVec4<T> reflect(TVec4<T> vec1, TVec4<T> vec2);
	template<typename T>
	T dot(TVec4<T> vec1, TVec4<T> vec2);
	template<typename T>
	T angle(TVec4<T> vec1, TVec4<T> vec2);
	template<typename T>
	T length(TVec4<T> vec);

	typedef TVec4<float> Vec4;

}

# include "Vec4.cpp"

#endif
