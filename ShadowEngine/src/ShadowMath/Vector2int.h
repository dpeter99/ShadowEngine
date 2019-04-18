//
// Created by dpete on 2/12/2019.
//

#ifndef CPP_VECTOR2INT_H
#define CPP_VECTOR2INT_H

namespace ShadowMath
{
	struct Vector2int
	{
	public:
		int x;
		int y;

		Vector2int(int x, int y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2int()
		{
			this->x = 0;
			this->y = 0;
		}

		Vector2int(const Vector2int& cpy)
		{
			this->x = cpy.x;
			this->y = cpy.y;
		}

		Vector2int operator+(const Vector2int& b);

		Vector2int operator-(const Vector2int& b);

		Vector2int operator*(const Vector2int& b);

		Vector2int operator*(const int& b);

		Vector2int operator*(const float& b);

		bool operator==(const Vector2int& b);
	};
}
#endif //CPP_VECTOR2INT_H
