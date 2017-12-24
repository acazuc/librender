#ifndef VEC3_H
# define VEC3_H

# include "Vec2.h"

namespace librender
{

	class Vec3
	{

	public:
		union {float x, r;};
		union {float y, g;};
		union {float z, b;};
		Vec3(Vec2 vec, float z) : x(vec.x), y(vec.y), z(z) {};
		Vec3(float x, float y, float z) : x(x), y(y), z(z) {};
		Vec3(float xyz) : x(xyz), y(xyz), z(xyz) {};
		Vec3() : x(0), y(0), z(0) {};
		Vec3 reflect(Vec3 vec);
		Vec3 cross(Vec3 vec);
		float dot(Vec3 vec);
		float angle(Vec3 vec);
		float length();
		void normalize();
		void min(float val);
		void max(float val);
		void clamp(float min, float max);
		float &operator [] (int idx);
		Vec3 operator - ();
		Vec3 operator + (float val);
		Vec3 operator - (float val);
		Vec3 operator * (float val);
		Vec3 operator / (float val);
		Vec3 operator + (Vec3 vec);
		Vec3 operator - (Vec3 vec);
		Vec3 operator * (Vec3 vec);
		Vec3 operator / (Vec3 vec);
		Vec3 operator += (float val);
		Vec3 operator -= (float val);
		Vec3 operator *= (float val);
		Vec3 operator /= (float val);
		Vec3 operator += (Vec3 vec);
		Vec3 operator -= (Vec3 vec);
		Vec3 operator *= (Vec3 vec);
		Vec3 operator /= (Vec3 vec);

	};

}

#endif
