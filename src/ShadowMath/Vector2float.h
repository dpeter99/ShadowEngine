//
// Created by dpete on 2/8/2019.
//

#ifndef CPP_VECTOR2FLOAT_H
#define CPP_VECTOR2FLOAT_H


#include "Vector2int.h"

namespace ShadowMath{

class Vector2Float {
public:
    float x;
    float y;

    Vector2Float(float x, float y) {
        this->x = x;
        this->y = y;
    }

    Vector2Float() {
        this->x = 0;
        this->y = 0;
    }

    Vector2Float(const Vector2Float &cpy) {
        this->x = cpy.x;
        this->y = cpy.y;
    }

    float Magnitude();

    float MagnitudeSqr();

    void Normalize();

    Vector2Float LeftNormal();

    Vector2Float RightNormal();

    float Angle();

    const float DotProduct(Vector2Float a, Vector2Float b);

    const Vector2Float Lerp(Vector2Float a, Vector2Float b, int t);

    const float Distance(Vector2Float a, Vector2Float b);

    Vector2Float operator+(const Vector2Float &b);

    Vector2Float operator-(const Vector2Float &b);

    Vector2Float operator*(const Vector2Float &b);

    Vector2Float operator*(const int &b);

    Vector2Float operator*(const float &b);

    operator Vector2int();
};

}


#endif //CPP_VECTOR2FLOAT_H
