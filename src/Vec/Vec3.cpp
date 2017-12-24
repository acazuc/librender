#include "Vec3.h"
#include <algorithm>
#include <cmath>

namespace librender
{

	Vec3 Vec3::reflect(Vec3 vec)
	{
		return (*this - vec * 2 * this->dot(vec));
	}

	Vec3 Vec3::cross(Vec3 vec)
	{
		return (Vec3(this->y * vec.z - this->z * vec.y, this->z * vec.x - this->x * vec.z, this->x * vec.y - this->y * vec.x));
	}

	float Vec3::dot(Vec3 vec)
	{
		return (this->x * vec.x + this->y * vec.y + this->z * vec.z);
	}

	float Vec3::angle(Vec3 vec)
	{
		return (acos(dot(vec) / (length() * vec.length())));
	}

	float Vec3::length()
	{
		return (sqrt(dot(*this)));
	}

	void Vec3::normalize()
	{
		*this /= this->length();
	}

	void Vec3::min(float val)
	{
		this->x = std::min(val, this->x);
		this->y = std::min(val, this->y);
		this->z = std::min(val, this->z);
	}

	void Vec3::max(float val)
	{
		this->x = std::max(val, this->x);
		this->y = std::max(val, this->y);
		this->z = std::max(val, this->z);
	}

	void Vec3::clamp(float min, float max)
	{
		this->max(min);
		this->min(max);
	}

	float &Vec3::operator [] (int idx)
	{
		return (reinterpret_cast<float*>(this)[idx]);
	}

	Vec3 Vec3::operator - ()
	{
		return (Vec3(-this->x, -this->y, -this->z));
	}

	Vec3 Vec3::operator + (float val)
	{
		return (Vec3(this->x + val, this->y + val, this->z + val));
	}

	Vec3 Vec3::operator - (float val)
	{
		return (Vec3(this->x - val, this->y - val, this->z - val));
	}

	Vec3 Vec3::operator * (float val)
	{
		return (Vec3(this->x * val, this->y * val, this->z * val));
	}

	Vec3 Vec3::operator / (float val)
	{
		return (Vec3(this->x / val, this->y / val, this->z / val));
	}

	Vec3 Vec3::operator + (Vec3 vec)
	{
		return (Vec3(this->x + vec.x, this->y + vec.y, this->z + vec.z));
	}

	Vec3 Vec3::operator - (Vec3 vec)
	{
		return (Vec3(this->x - vec.x, this->y - vec.y, this->z - vec.z));
	}

	Vec3 Vec3::operator * (Vec3 vec)
	{
		return (Vec3(this->x * vec.x, this->y * vec.y, this->z * vec.z));
	}

	Vec3 Vec3::operator / (Vec3 vec)
	{
		return (Vec3(this->x / vec.x, this->y / vec.y, this->z / vec.z));
	}

	Vec3 Vec3::operator += (float val)
	{
		return (*this = *this + val);
	}

	Vec3 Vec3::operator -= (float val)
	{
		return (*this = *this - val);
	}

	Vec3 Vec3::operator *= (float val)
	{
		return (*this = *this * val);
	}

	Vec3 Vec3::operator /= (float val)
	{
		return (*this = *this / val);
	}

	Vec3 Vec3::operator += (Vec3 vec)
	{
		return (*this = *this + vec);
	}

	Vec3 Vec3::operator -= (Vec3 vec)
	{
		return (*this = *this - vec);
	}

	Vec3 Vec3::operator *= (Vec3 vec)
	{
		return (*this = *this * vec);
	}

	Vec3 Vec3::operator /= (Vec3 vec)
	{
		return (*this = *this / vec);
	}

	bool Vec3::operator == (Vec3 vec)
	{
		return (this->x == vec.x && this->y == vec.y && this->z == vec.z);
	}

	bool Vec3::operator != (Vec3 vec)
	{
		return (!(*this == vec));
	}

}
