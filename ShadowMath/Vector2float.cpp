//
// Created by dpete on 2/8/2019.
//

#include <cmath>
#include "Vector2float.h"
#include "Vector2int.h"

namespace ShadowMath {

    float Vector2Float::MagnitudeSqr() {
        return sqrtf(this->x * this->x + this->y * this->y);
    }

    float Vector2Float::Magnitude() {
        return this->x * this->x + this->y * this->y;
    }

    void Vector2Float::Normalize() {
        float mag = this->Magnitude();
        this->x = this->x / mag;
        this->y = this->y / mag;
    }

    Vector2Float Vector2Float::LeftNormal() {
        return Vector2Float(-this->y, this->x);
    }

    Vector2Float Vector2Float::RightNormal() {
        return Vector2Float(this->y, -this->x);
    }

    float Vector2Float::Angle() {
        return atan2f(this->y, this->x);
    }

    const Vector2Float Vector2Float::Lerp(Vector2Float a, Vector2Float b, int t) {
        Vector2Float res;

        res.x = a.x - a.x / 100 * t;
        res.y = a.y - a.y / 100 * t;

        return res;
    }

    const float Vector2Float::DotProduct(Vector2Float a, Vector2Float b) {
        return 0;
    }

    const float Vector2Float::Distance(Vector2Float a, Vector2Float b) {
        return 0;
    }

    Vector2Float Vector2Float::operator+(const Vector2Float &b) {
        Vector2Float res;
        res.x = this->x + b.x;
        res.y = this->y + b.y;
        return res;
    }

    Vector2Float Vector2Float::operator-(const Vector2Float &b) {
        Vector2Float res;
        res.x = this->x - b.x;
        res.y = this->y - b.y;
        return res;
    }

    Vector2Float Vector2Float::operator*(const Vector2Float &b) {
        Vector2Float res;
        res.x = this->x * b.x;
        res.y = this->y * b.y;
        return res;
    }

    Vector2Float Vector2Float::operator*(const float &b) {
        return Vector2Float();
    }

    Vector2Float Vector2Float::operator*(const int &b) {
        return Vector2Float();
    }

//TODO: this should be fixed i think
    Vector2Float::operator Vector2int() {
        Vector2int posint(floorf(this->x), floorf(this->y));
        return posint;
    }

}