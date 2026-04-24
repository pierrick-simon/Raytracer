/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#include "Shpere.hpp"

namespace RayTracer {
    Sphere::Sphere(int x, int y, int z, std::size_t r, Maths::RGB color) :
    _x(x), _y(y), _z(z), _r(r),_color(color) {}

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

    void Sphere::setRadius(std::size_t r)
    {
        _r = r;
    }

    void Sphere::setColor(Maths::RGB const color)
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

    std::size_t Sphere::getRadius() const
    {
        return _r;
    }

    Maths::RGB Sphere::getColor() const
    {
        return _color;
    }

    std::optional<HitInfo> Sphere::hits(Ray &)
    {
        // TODO
        return std::nullopt;
    }
}
