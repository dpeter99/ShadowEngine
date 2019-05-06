//
// Created by dpete on 2/8/2019.
//

#include "shpch.h"

#include <cmath>
#include "Vector2float.h"
#include "Vector2int.h"

namespace ShadowMath
{
	const Vector2float Vector2float::zero = Vector2float(0, 0);

	float Vector2float::MagnitudeSqr()
	{
		return sqrtf(this->x * this->x + this->y * this->y);
	}

	float Vector2float::Magnitude()
	{
		return this->x * this->x + this->y * this->y;
	}

	void Vector2float::Normalize()
	{
		float mag = this->Magnitude();
		this->x = this->x / mag;
		this->y = this->y / mag;
	}

	Vector2float Vector2float::LeftNormal()
	{
		return Vector2float(-this->y, this->x);
	}

	Vector2float Vector2float::RightNormal()
	{
		return Vector2float(this->y, -this->x);
	}

	float Vector2float::Angle()
	{
		return atan2f(this->y, this->x);
	}

	const Vector2float Vector2float::Lerp(Vector2float a, Vector2float b, int t)
	{
		Vector2float res;

		res.x = a.x - a.x / 100 * t;
		res.y = a.y - a.y / 100 * t;

		return res;
	}

	const float Vector2float::DotProduct(Vector2float a, Vector2float b)
	{
		return 0;
	}

	const float Vector2float::Distance(Vector2float a, Vector2float b)
	{
		return 0;
	}

	Vector2float Vector2float::operator+(const Vector2float& b)
	{
		Vector2float res;
		res.x = this->x + b.x;
		res.y = this->y + b.y;
		return res;
	}

	Vector2float Vector2float::operator-(const Vector2float& b)
	{
		Vector2float res;
		res.x = this->x - b.x;
		res.y = this->y - b.y;
		return res;
	}

	Vector2float Vector2float::operator*(const Vector2float& b)
	{
		Vector2float res;
		res.x = this->x * b.x;
		res.y = this->y * b.y;
		return res;
	}

	Vector2float Vector2float::operator*(const float& b)
	{
		return Vector2float();
	}


	bool Vector2float::operator==(const Vector2float b) const
	{
		return this->x == b.x && this->y == b.y;
	}

	bool Vector2float::operator!=(const Vector2float b) const
	{
		return !(*this == b);
	}

	float& Vector2float::operator[](int i)
	{
		if (i == 0) 
			return x;
		else if (i == 1)
			return y;
		else
		{
			throw std::out_of_range("Only 0-1");
		}
	}

	Vector2float Vector2float::operator*(const int& b)
	{
		return Vector2float();
	}

	//TODO: this should be fixed i think
	Vector2float::operator Vector2int()
	{
		Vector2int posint(floorf(this->x), floorf(this->y));
		return posint;
	}
}
