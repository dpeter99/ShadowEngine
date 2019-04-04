//
// Created by dpete on 2/8/2019.
//

#ifndef CPP_VECTOR2FLOAT_H
#define CPP_VECTOR2FLOAT_H


#include "Vector2int.h"

namespace ShadowMath{

class Vector2float {
public:
    float x;
    float y;

    Vector2float(float x, float y) {
        this->x = x;
        this->y = y;
    }

    Vector2float() {
        this->x = 0;
        this->y = 0;
    }

    Vector2float(const Vector2float &cpy) {
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

    Vector2float operator+(const Vector2float &b);

    Vector2float operator-(const Vector2float &b);

    Vector2float operator*(const Vector2float &b);

    Vector2float operator*(const int &b);

    Vector2float operator*(const float &b);

    operator Vector2int();
};

}


#endif //CPP_VECTOR2FLOAT_H