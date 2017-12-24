#ifndef MAT4_H
# define MAT4_H

# include "../Vec/Vec4.h"
# include "../Vec/Vec3.h"


namespace librender
{

	template <typename T> class TMat4
	{
	
	public:
		TVec4<T> data[4];
		TMat4(TVec4<T> vec);
		TMat4(T val);
		TMat4() {};
		static TMat4<T> rotate(TMat4<T> mat, T angle, TVec3<T> axis);
		static TMat4<T> rotateX(TMat4<T> mat, T angle);
		static TMat4<T> rotateY(TMat4<T> mat, T angle);
		static TMat4<T> rotateZ(TMat4<T> mat, T angle);
		static TMat4<T> translate(TMat4<T> mat, TVec3<T> vec);
		static TMat4<T> scale(TMat4<T> mat, TVec3<T> vec);
		static TMat4<T> perspective(T fov, T aspect, T znear, T zfar);
		static TMat4<T> lookAt(TVec3<T> eye, TVec3<T> center, TVec3<T> up);
		static TMat4<T> ortho(T left, T right, T bottom, T top, T near, T far);
		TVec4<T> &operator [] (int i);
		TMat4<T> operator * (TMat4<T> mat);
	
	};

	template <typename T>
	TVec4<T> operator * (TMat4<T> mat, TVec4<T> vec);
	template <typename T>
	TVec4<T> operator * (TVec4<T> vec, TMat4<T> mat);

	typedef TMat4<float> Mat4;

}

#include "Mat4.cpp"

#endif