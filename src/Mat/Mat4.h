#ifndef MAT4_H
# define MAT4_H

# include "../Vec/Vec4.h"

namespace librender
{

	class Mat4
	{
	
		public:
			Vec4 data[4];
			Mat4(Vec4 vec);
			Mat4(float val);
			Mat4() {};
			static Mat4 rotate(Mat4 mat, float angle, Vec3 axis);
			static Mat4 rotateX(Mat4 mat, float angle);
			static Mat4 rotateY(Mat4 mat, float angle);
			static Mat4 rotateZ(Mat4 mat, float angle);
			static Mat4 translate(Mat4 mat, Vec3 vec);
			static Mat4 scale(Mat4 mat, Vec3 vec);
			static Mat4 perspective(float fov, float aspect, float znear, float zfar);
			static Mat4 lookAt(Vec3 eye, Vec3 center, Vec3 up);
			static Mat4 ortho(float left, float right, float bottom, float top, float near, float far);
			Vec4 &operator [] (int i);
			Mat4 operator * (Mat4 mat);
	
	};

	Vec4 operator * (Mat4 mat, Vec4 vec);
	Vec4 operator * (Vec4 vec, Mat4 mat);

}

#endif
