#ifndef VEC3_H
# define VEC3_H

# include "Vec2.h"

namespace librender
{

	template <typename T = float> class TVec3
	{

	public:
		union {T x, r;};
		union {T y, g;};
		union {T z, b;};
		TVec3<T>(TVec2<T> vec, T z) : x(vec.x), y(vec.y), z(z) {};
		TVec3<T>(T x, T y, T z) : x(x), y(y), z(z) {};
		TVec3<T>(T xyz) : x(xyz), y(xyz), z(xyz) {};
		TVec3<T>() : x(0), y(0), z(0) {};
		TVec3<T> reflect(TVec3<T> vec);
		TVec3<T> cross(TVec3<T> vec);
		T dot(TVec3<T> vec);
		T angle(TVec3<T> vec);
		T length();
		void normalize();
		void min(T val);
		void max(T val);
		void clamp(T min, T max);
		T &operator [] (int idx);
		TVec3<T> operator - ();
		TVec3<T> operator + (T val);
		TVec3<T> operator - (T val);
		TVec3<T> operator * (T val);
		TVec3<T> operator / (T val);
		TVec3<T> operator + (TVec3<T> vec);
		TVec3<T> operator - (TVec3<T> vec);
		TVec3<T> operator * (TVec3<T> vec);
		TVec3<T> operator / (TVec3<T> vec);
		TVec3<T> operator += (T val);
		TVec3<T> operator -= (T val);
		TVec3<T> operator *= (T val);
		TVec3<T> operator /= (T val);
		TVec3<T> operator += (TVec3<T> vec);
		TVec3<T> operator -= (TVec3<T> vec);
		TVec3<T> operator *= (TVec3<T> vec);
		TVec3<T> operator /= (TVec3<T> vec);
		bool operator == (TVec3<T> vec);
		bool operator != (TVec3<T> vec);

	};

	typedef TVec3<float> Vec3;

}

# include "Vec3.cpp"

#endif
