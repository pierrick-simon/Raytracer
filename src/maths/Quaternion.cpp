/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#include "Quaternion.hpp"

#include <cmath>

namespace Maths {
    bool Quaternion::operator==(const Quaternion &rhs) const
    {
        return this->_w == rhs._w
               && this->_x == rhs._x
               && this->_y == rhs._y
               && this->_z == rhs._z;
    }

    bool Quaternion::operator!=(const Quaternion &rhs) const
    {
        return !(*this == rhs);
    }

    Quaternion Quaternion::operator*(const Quaternion &rhs) const
    {
        return {
            this->_w * rhs._w - this->_x * rhs._x -
            this->_y * rhs._y - this->_z * rhs._z,
            this->_w * rhs._x + this->_x * rhs._w -
            this->_y * rhs._z + this->_z * rhs._y,
            this->_w * rhs._y + this->_x * rhs._z +
            this->_y * rhs._w - this->_z * rhs._x,
            this->_w * rhs._z - this->_x * rhs._y +
            this->_y * rhs._x + this->_z * rhs._w
        };
    }

    Quaternion &Quaternion::operator*=(const Quaternion &rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    Quaternion Quaternion::normalized() const
    {
        double magnitude = this->magnitude();

        if (magnitude < 1e-4)
            return identity();

        return {
            this->_w / magnitude,
            this->_x / magnitude,
            this->_y / magnitude,
            this->_z / magnitude,
        };
    }

    Quaternion &Quaternion::normalize()
    {
        double magnitude = this->magnitude();

        if (magnitude < 1e-4)
            return *this;

        this->_w /= magnitude;
        this->_x /= magnitude;
        this->_y /= magnitude;
        this->_z /= magnitude;
        return *this;
    }

    Quaternion Quaternion::inversed() const
    {
        return {this->_w, -this->_x, -this->_y, -this->_z};
    }

    Quaternion &Quaternion::inverse()
    {
        this->_w = -this->_w;
        this->_x = -this->_x;
        this->_y = -this->_y;
        this->_z = -this->_z;

        return *this;
    }

    Quaternion Quaternion::fromEuler(double u, double v, double w)
    {
        double halfU = u / 2.0;
        double halfV = v / 2.0;
        double halfW = w / 2.0;

        double cosU = std::cos(halfU);
        double cosV = std::cos(halfV);
        double cosW = std::cos(halfW);

        double sinU = std::sin(halfU);
        double sinV = std::sin(halfV);
        double sinW = std::sin(halfW);

        return {
            cosU * cosV * cosW + sinU * sinV * sinW,
            sinU * cosV * cosW - cosU * sinV * sinW,
            cosU * sinV * cosW + sinU * cosV * sinW,
            cosU * cosV * sinW - sinU * sinV * cosW
        };
    }

    Quaternion Quaternion::identity()
    {
        return {1, 0, 0, 0};
    }

    Quaternion::Quaternion(double w, double x, double y, double z) :
        _w(w),
        _x(x),
        _y(y),
        _z(z)
    {
    }

    double Quaternion::magnitude() const
    {
        return std::sqrt(
            this->_w * this->_w + this->_x * this->_x +
            this->_y * this->_y + this->_z * this->_z
        );
    }
} // Maths
