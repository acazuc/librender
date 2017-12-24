#ifndef VEC2_H
# define VEC2_H

namespace librender
{

	template <typename T = float> class TVec2
	{

	public:
		union {T x, u;};
		union {T y, v;};
		TVec2<T>(T x, T y) : x(x), y(y) {};
		TVec2<T>(T xy) : x(xy), y(xy) {};
		TVec2<T>() : x(0), y(0) {};
		T dot(TVec2<T> vec);
		T angle(TVec2<T> vec);
		T length();
		void normalize();
		void min(T val);
		void max(T val);
		void clamp(T min, T max);
		T &operator [] (int idx);
		TVec2<T> operator + (T val);
		TVec2<T> operator - (T val);
		TVec2<T> operator * (T val);
		TVec2<T> operator / (T val);
		TVec2<T> operator + (TVec2<T> vec);
		TVec2<T> operator - (TVec2<T> vec);
		TVec2<T> operator * (TVec2<T> vec);
		TVec2<T> operator / (TVec2<T> vec);
		TVec2<T> operator += (T val);
		TVec2<T> operator -= (T val);
		TVec2<T> operator *= (T val);
		TVec2<T> operator /= (T val);
		TVec2<T> operator += (TVec2<T> vec);
		TVec2<T> operator -= (TVec2<T> vec);
		TVec2<T> operator *= (TVec2<T> vec);
		TVec2<T> operator /= (TVec2<T> vec);
		bool operator == (TVec2<T> vec);
		bool operator != (TVec2<T> vec);

	};

	typedef TVec2<float> Vec2;

}

# include "Vec2.cpp"

#endif
