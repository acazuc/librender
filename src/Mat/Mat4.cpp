#include "Mat4.h"
#include <cmath>

namespace librender
{

	Mat4::Mat4(Vec4 vec)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (i == j)
					this->data[i][j] = vec[i];
				else
					this->data[i][j] = 0;
			}
		}
	}

	Mat4::Mat4(float value)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (i == j)
					this->data[i][j] = value;
				else
					this->data[i][j] = 0;
			}
		}
	}

	Vec4 &Mat4::operator [] (int i)
	{
		return (this->data[i]);
	}

	Mat4 Mat4::rotateX(Mat4 mat, float angle)
	{
		float c = cos(angle);
		float s = sin(angle);
		Mat4 rotate;
		rotate[0] = Vec4(1,  0, 0, 0);
		rotate[1] = Vec4(0,  c, s, 0);
		rotate[2] = Vec4(0, -s, c, 0);
		rotate[3] = Vec4(0,  0, 0, 1);
		return (mat * rotate);
	}

	Mat4 Mat4::rotateY(Mat4 mat, float angle)
	{
		float c = cos(angle);
		float s = sin(angle);
		Mat4 rotate;
		rotate[0] = Vec4(c, 0, -s, 0);
		rotate[1] = Vec4(0, 1,  0, 0);
		rotate[2] = Vec4(s, 0,  c, 0);
		rotate[3] = Vec4(0, 0,  0, 1);
		return (mat * rotate);
	}

	Mat4 Mat4::rotateZ(Mat4 mat, float angle)
	{
		float c = cos(angle);
		float s = sin(angle);
		Mat4 rotate;
		rotate[0] = Vec4( c, s, 0, 0);
		rotate[1] = Vec4(-s, c, 0, 0);
		rotate[2] = Vec4( 0, 0, 1, 0);
		rotate[3] = Vec4( 0, 0, 0, 1);
		return (mat * rotate);
	}

	Mat4 Mat4::translate(Mat4 mat, Vec3 vec)
	{
		Mat4 translate(1);
		translate[3] = Vec4(vec, 1);
		return (mat * translate);
	}

	Mat4 Mat4::scale(Mat4 mat, Vec3 vec)
	{
		Mat4 scale(Vec4(vec, 1));
		return (mat * scale);
	}

	Mat4 Mat4::perspective(float fov, float aspect, float znear, float zfar)
	{
		float f = 1 / tan(fov / 2);
		Mat4 mat(Vec4(f / aspect, f, (zfar + znear) / (znear - zfar), 0));
		mat[2][3] = -1;
		mat[3][2] = (2 * zfar * znear) / (znear - zfar);
		return (mat);
	}

	Mat4 Mat4::lookAt(Vec3 eye, Vec3 center, Vec3 up)
	{
		Vec3 f(center - eye);
		f.normalize();
		up.normalize();
		Vec3 s(f.cross(up));
		Vec3 ss(s);
		ss.normalize();
		Vec3 u(ss.cross(f));
		f = -f;
		Mat4 mat;
		mat[0] = Vec4(s[0], u[0], f[0], 0);
		mat[1] = Vec4(s[1], u[1], f[1], 0);
		mat[2] = Vec4(s[2], u[2], f[2], 0);
		mat[3] = Vec4(0   , 0   , 0   , 1);
		return (translate(mat, Vec3(-eye)));
	}

	Mat4 Mat4::operator * (Mat4 mat)
	{
		Mat4 result;
		for (int i = 0; i < 4; ++i)
			result[i] = (*this)[0] * mat[i][0] + (*this)[1] * mat[i][1] + (*this)[2] * mat[i][2] + (*this)[3] * mat[i][3];
		return (result);
	}

	Vec4 Mat4::operator * (Vec4 vec)
	{
		Vec4 result;
		for (int i = 0; i < 4; ++i)
			result[i] = vec[0] * (*this)[0][i] + vec[1] * (*this)[1][i] + vec[2] * (*this)[2][i] + vec[3] * (*this)[3][i];
		return (result);
	}

}
