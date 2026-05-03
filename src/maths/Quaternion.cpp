/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#include "Quaternion.hpp"

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
} // Maths