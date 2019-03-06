//
// Created by dpete on 2/12/2019.
//

#include "Vector2int.h"

Vector2int Vector2int::operator+(const Vector2int &b) {
    Vector2int res;
    res.x = this->x + b.x;
    res.y = this->y + b.y;
    return res;
}

Vector2int Vector2int::operator-(const Vector2int &b) {
    Vector2int res;
    res.x = this->x - b.x;
    res.y = this->y - b.y;
    return res;
}

Vector2int Vector2int::operator*(const Vector2int &b) {
    Vector2int res;
    res.x = this->x * b.x;
    res.y = this->y * b.y;
    return res;
}

Vector2int Vector2int::operator*(const int &b) {
    Vector2int res;
    res.x = this->x * b;
    res.y = this->y * b;
    return res;
}

