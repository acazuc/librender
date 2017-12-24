#include "Vec4.h"
#include <algorithm>
#include <cmath>

namespace librender
{

	float Vec4::dot(Vec4 vec)
	{
		return (this->x * vec.x + this->y * vec.y + this->z * vec.z + this->w * vec.w);
	}

	float Vec4::angle(Vec4 vec)
	{
		return (acos(dot(vec) / (length() * vec.length())));
	}

	float Vec4::length()
	{
		return (sqrt(dot(*this)));
	}

	void Vec4::normalize()
	{
		*this = *this / this->length();
	}

	void Vec4::min(float val)
	{
		this->x = std::min(val, this->x);
		this->y = std::min(val, this->y);
		this->z = std::min(val, this->z);
		this->w = std::min(val, this->w);
	}

	void Vec4::max(float val)
	{
		this->x = std::max(val, this->x);
		this->y = std::max(val, this->y);
		this->z = std::max(val, this->z);
		this->w = std::max(val, this->w);
	}

	void Vec4::clamp(float min, float max)
	{
		this->max(min);
		this->min(max);
	}

	Vec3 Vec4::xyz()
	{
		return (Vec3(this->x, this->y, this->z));
	}

	Vec3 Vec4::rgb()
	{
		return (Vec3(this->r, this->g, this->b));
	}

	Vec2 Vec4::xy()
	{
		return (Vec2(this->x, this->y));
	}

	Vec2 Vec4::zw()
	{
		return (Vec2(this->z, this->w));
	}

	float &Vec4::operator [] (int idx)
	{
		return (reinterpret_cast<float*>(this)[idx]);
	}

	Vec4 Vec4::operator + (float val)
	{
		return (Vec4(this->x + val, this->y + val, this->z + val, this->w + val));
	}

	Vec4 Vec4::operator - (float val)
	{
		return (Vec4(this->x - val, this->y - val, this->z - val, this->w - val));
	}

	Vec4 Vec4::operator * (float val)
	{
		return (Vec4(this->x * val, this->y * val, this->z * val, this->w * val));
	}

	Vec4 Vec4::operator / (float val)
	{
		return (Vec4(this->x / val, this->y / val, this->z / val, this->w / val));
	}

	Vec4 Vec4::operator + (Vec4 vec)
	{
		return (Vec4(this->x + vec.x, this->y + vec.y, this->z + vec.z, this->w + vec.w));
	}

	Vec4 Vec4::operator - (Vec4 vec)
	{
		return (Vec4(this->x - vec.x, this->y - vec.y, this->z - vec.z, this->w - vec.w));
	}

	Vec4 Vec4::operator * (Vec4 vec)
	{
		return (Vec4(this->x * vec.x, this->y * vec.y, this->z * vec.z, this->w * vec.w));
	}

	Vec4 Vec4::operator / (Vec4 vec)
	{
		return (Vec4(this->x / vec.x, this->y / vec.y, this->z / vec.z, this->w / vec.w));
	}

	Vec4 Vec4::operator += (float val)
	{
		return (*this = *this + val);
	}

	Vec4 Vec4::operator -= (float val)
	{
		return (*this = *this - val);
	}

	Vec4 Vec4::operator *= (float val)
	{
		return (*this = *this * val);
	}

	Vec4 Vec4::operator /= (float val)
	{
		return (*this = *this / val);
	}

	Vec4 Vec4::operator += (Vec4 vec)
	{
		return (*this = *this + vec);
	}

	Vec4 Vec4::operator -= (Vec4 vec)
	{
		return (*this = *this - vec);
	}

	Vec4 Vec4::operator *= (Vec4 vec)
	{
		return (*this = *this * vec);
	}

	Vec4 Vec4::operator /= (Vec4 vec)
	{
		return (*this = *this / vec);
	}

}
