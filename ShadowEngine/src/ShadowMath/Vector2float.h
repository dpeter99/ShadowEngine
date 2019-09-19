#pragma once

#include "Vector2int.h"

namespace ShadowMath
{
	class Vector2float
	{
	public:
		float x;
		float y;

		static const Vector2float zero;

		Vector2float(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2float()
		{
			this->x = 0;
			this->y = 0;
		}

		Vector2float(const Vector2float& cpy)
		{
			this->x = cpy.x;
			this->y = cpy.y;
		}

		float Magnitude();

		float MagnitudeSqr();

		void Normalize();

		Vector2float LeftNormal();

		Vector2float RightNormal();

		float Angle();

		const float DotProduct(Vector2float a, Vector2float b);

		const Vector2float Lerp(Vector2float a, Vector2float b, int t);

		const float Distance(Vector2float a, Vector2float b);

		Vector2float operator+(const Vector2float& b);

		Vector2float operator-(const Vector2float& b);

		Vector2float operator*(const Vector2float& b);

		Vector2float operator*(const int& b);

		Vector2float operator*(const float& b);

		bool operator==(const Vector2float b) const;

		bool operator!=(const Vector2float b) const;

		float& operator[](int i);

		operator Vector2int();
	};
}