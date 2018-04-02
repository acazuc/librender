#ifndef QUATERNION_H
# define QUATERNION_H

# include "Mat/Mat4.h"
# include "Mat/Mat3.h"

namespace librender
{

	template <typename T> class TQuaternion
	{

	public:
		struct {T x, y, z, w;};
		TQuaternion(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {};
		TQuaternion(T xyz, T w) : x(xyz), y(xyz), z(xyz), w(w) {};
		TQuaternion(T xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {};
		TQuaternion() : x(0), y(0), z(0), w(0) {};
		TMat3<T> to_mat3();
		TMat4<T> to_mat4();

	};

	typedef TQuaternion<float> Quaternion;

}

# include "Quaternion.cpp"

#endif
