/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#include "Shpere.hpp"

namespace RayTracer {
    Sphere::Sphere(int x, int y, int z, Maths::Vector3<int> color) :
    _x(x), _y(y), _z(z), _color(color) {}

    void Sphere::setX(int x)
    {
        _x = x;
    }

    void Sphere::setY(int y)
    {
        _y = y;
    }

    void Sphere::setZ(int z)
    {
        _z = z;
    }

    void Sphere::setColor(Maths::Vector3<int> const color)
    {
        _color = color;
    }

    int Sphere::getX() const
    {
        return _x;
    }

    int Sphere::getY() const
    {
        return _y;
    }

    int Sphere::getZ() const
    {
        return _z;
    }

    Maths::Vector3<int> Sphere::getColor() const
    {
        return _color;
    }
}
