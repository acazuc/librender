#ifndef MAT3_H
# define MAT3_H

# include "../Vec/Vec3.h"

namespace librender
{

	template <typename T> class TMat3
	{

	public:
		TVec3<T> data[3];
		TMat3<T>(TVec3<T> vec);
		TMat3<T>(T val);
		TMat3<T>() {};
		static TMat3<T> rotateX(TMat3<T> mat, T angle);
		static TMat3<T> rotateY(TMat3<T> mat, T angle);
		static TMat3<T> rotateZ(TMat3<T> mat, T angle);
		TVec3<T> &operator [] (int i);
		TMat3<T> operator * (TMat3<T> mat);

	};

	template <typename T>
	TVec3<T> operator * (TMat3<T> mat, TVec3<T> vec);
	template <typename T>
	TVec3<T> operator * (TVec3<T> vec, TMat3<T> mat);

	typedef TMat3<float> Mat3;

}

# include "Mat3.cpp"

#endif