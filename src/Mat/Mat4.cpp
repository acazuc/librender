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
				this->data[i][j] = 0;
			}
		}
		for (int i = 0; i < 4; ++i)
			this->data[i][i] = vec[i];
	}

	Mat4::Mat4(float value)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				this->data[i][j] = 0;
			}
		}
		for (int i = 0; i < 4; ++i)
			this->data[i][i] = value;
	}

	Vec4 &Mat4::operator [] (int i)
	{
		return (this->data[i]);
	}

	Mat4 Mat4::rotate(Mat4 mat, float angle, Vec3 axis)
	{
		float c = cos(angle);
		float s = sin(angle);
		float c1 = 1 - c;
		float xs = s * axis.x;
		float ys = s * axis.y;
		float zs = s * axis.z;
		float xx = axis.x * axis.x * c1;
		float xy = axis.x * axis.y * c1;
		float xz = axis.x * axis.z * c1;
		float yy = axis.y * axis.y * c1;
		float yz = axis.y * axis.z * c1;
		float zz = axis.z * axis.z * c1;
		axis.normalize();
		Mat4 rotate;
		rotate[0][0] = xx + c;
		rotate[0][1] = xy + zs;
		rotate[0][2] = xz - ys;
		rotate[0][3] = 0;
		rotate[1][0] = xy - zs;
		rotate[1][1] = yy + c;
		rotate[1][2] = yz + xs;
		rotate[1][3] = 0;
		rotate[2][0] = xz + ys;
		rotate[2][1] = yz - xs;
		rotate[2][2] = zz + c;
		rotate[2][3] = 0;
		rotate[3] = Vec4(0, 0, 0, 1);
		return (mat * rotate);
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

	Mat4 Mat4::ortho(float left, float right, float bottom, float top, float near, float far)
	{
		Mat4 mat(Vec4(2 / (right - left), 2 / (top - bottom), -2 / (far - near), 1));
		mat[3][0] = -(right + left) / (right - left);
		mat[3][1] = -(top + bottom) / (top - bottom);
		mat[3][2] = -(far + near) / (far - near);
		return (mat);
	}

	Mat4 Mat4::operator * (Mat4 mat)
	{
		Mat4 result;
		for (int i = 0; i < 4; ++i)
			result[i] = (*this)[0] * mat[i][0] + (*this)[1] * mat[i][1] + (*this)[2] * mat[i][2] + (*this)[3] * mat[i][3];
		return (result);
	}

	Vec4 operator * (Mat4 mat, Vec4 vec)
	{
		Vec4 result;
		for (int i = 0; i < 4; ++i)
			result[i] = vec.x * mat[0][i] + vec.y * mat[1][i] + vec.z * mat[2][i] + vec.w * mat[3][i];
		return (result);
	}

	Vec4 operator * (Vec4 vec, Mat4 mat)
	{
		Vec4 result;
		for (int i = 0; i < 4; ++i)
			result[i] = vec.x * mat[i].x + vec.y * mat[i].y + vec.z * mat[i].z + vec.w * mat[i].w;
		return (result);
	}


}
