#ifndef VEC4_H
# define VEC4_H

# include "Vec3.h"
# include "Vec2.h"

namespace librender
{

	template <typename T = float> class TVec4
	{

	public:
		union {T x, r;};
		union {T y, g;};
		union {T z, b;};
		union {T w, a;};
		TVec4(TVec2<T> vec1, TVec2<T> vec2) : x(vec1.x), y(vec1.y), z(vec2.x), w(vec2.y) {};
		TVec4(TVec2<T> vec1, T z, T w) : x(vec1.x), y(vec1.y), z(z), w(w) {};
		TVec4(TVec3<T> vec, T w) : x(vec.x), y(vec.y), z(vec.z), w(w) {};
		TVec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {};
		TVec4(T xyz, T w) : x(xyz), y(xyz), z(xyz), w(w) {};
		TVec4(T xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {};
		TVec4() : x(0), y(0), z(0), w(0) {};
		T dot(TVec4 vec);
		T angle(TVec4 vec);
		T length();
		void normalize();
		void min(T val);
		void max(T val);
		void clamp(T min, T max);
		TVec3<T> xyz();
		TVec3<T> rgb();
		TVec2<T> xy();
		TVec2<T> zw();
		T &operator [] (int idx);
		TVec4 operator + (T val);
		TVec4 operator - (T val);
		TVec4 operator * (T val);
		TVec4 operator / (T val);
		TVec4 operator + (TVec4<T> vec);
		TVec4 operator - (TVec4<T> vec);
		TVec4 operator * (TVec4<T> vec);
		TVec4 operator / (TVec4<T> vec);
		TVec4 operator += (T val);
		TVec4 operator -= (T val);
		TVec4 operator *= (T val);
		TVec4 operator /= (T val);
		TVec4 operator += (TVec4<T> vec);
		TVec4 operator -= (TVec4<T> vec);
		TVec4 operator *= (TVec4<T> vec);
		TVec4 operator /= (TVec4<T> vec);
		bool operator == (TVec4<T> vec);
		bool operator != (TVec4<T> vec);

	};

	typedef TVec4<float> Vec4;

}

# include "Vec4.cpp"

#endif
