#include "Mat2.h"

namespace librender
{

	Mat2::Mat2(Vec2 vec)
	{
		this->data[0][0] = vec[0];
		this->data[0][1] = 0;
		this->data[1][0] = 0;
		this->data[1][1] = vec[1];
	}

	Mat2::Mat2(float value)
	{
		this->data[0][0] = value;
		this->data[0][1] = 0;
		this->data[1][0] = 0;
		this->data[1][1] = value;
	}

	Vec2 &Mat2::operator [] (int i)
	{
		return (this->data[i]);
	}

	Mat2 Mat2::operator * (Mat2 mat)
	{
		Mat2 result;
		for (int i = 0; i < 2; ++i)
			result[i] = (*this)[0] * mat[i][0] + (*this)[1] * mat[i][1];
		return (result);
	}

	Vec2 Mat2::operator * (Vec2 vec)
	{
		Vec2 result;
		for (int i = 0; i < 2; ++i)
			result[i] = vec[0] * (*this)[0][i] + vec[1] * (*this)[1][i];
		return (result);
	}

}
