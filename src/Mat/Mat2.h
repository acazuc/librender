#ifndef MAT2_H
# define MAT2_H

# include "../Vec/Vec2.h"

namespace librender
{

	template <typename T> class TMat2
	{

	public:
		TVec2<T> data[2];
		TMat2(TVec2<T> vec);
		TMat2(T val);
		TMat2() {};
		TVec2<T> &operator [] (int i);
		TMat2<T> operator * (TMat2<T> mat);

	};

	template <typename T>
	TVec2<T> operator * (TMat2<T> mat, TVec2<T> vec);
	template <typename T>
	TVec2<T> operator * (TVec2<T> vec, TMat2<T> mat);

	typedef TMat2<float> Mat2;

}

# include "Mat2.cpp"

#endif