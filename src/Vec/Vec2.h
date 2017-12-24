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

	template <typename T>
	TVec2<T> operator + (TVec2<T> vec, T val);
	template <typename T>
	TVec2<T> operator + (T val, TVec2<T> vec);
	template <typename T>
	TVec2<T> operator - (TVec2<T> vec, T val);
	template <typename T>
	TVec2<T> operator - (T val, TVec2<T> vec);
	template <typename T>
	TVec2<T> operator * (TVec2<T> vec, T val);
	template <typename T>
	TVec2<T> operator * (T val, TVec2<T> vec);
	template <typename T>
	TVec2<T> operator / (TVec2<T> vec, T val);
	template <typename T>
	TVec2<T> operator / (T val, TVec2<T> vec);

	template <typename T>
	TVec2<T> min(TVec2<T> vec1, TVec2<T> vec2);
	template <typename T>
	TVec2<T> min(TVec2<T> vec, T val);
	template <typename T>
	TVec2<T> min(T val, TVec2<T> vec);

	template <typename T>
	TVec2<T> max(TVec2<T> vec1, TVec2<T> vec2);
	template <typename T>
	TVec2<T> max(TVec2<T> vec, T val);
	template <typename T>
	TVec2<T> max(T val, TVec2<T> vec);

	template <typename T>
	TVec2<T> clamp(TVec2<T> vec, T min, T max);
	template <typename T>
	TVec2<T> mod(TVec2<T> vec, T val);
	template <typename T>
	TVec2<T> floor(TVec2<T> vec);
	template <typename T>
	TVec2<T> round(TVec2<T> vec);
	template <typename T>
	TVec2<T> ceil(TVec2<T> vec);
	template <typename T>
	TVec2<T> fract(TVec2<T> vec);
	
	typedef TVec2<float> Vec2;

}

# include "Vec2.cpp"

#endif
