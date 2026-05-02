/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#include "PrimitiveTriangle.hpp"

namespace RayTracer {
    PrimitiveTriangle::PrimitiveTriangle(const Maths::Point3D &origin,
        double height, double width, double length, Maths::RGB const color):
        _origin(origin),
        _height(height),
        _width(width),
        _length(length),
        _color(color)
    {
    }

    std::optional<HitInfo> PrimitiveTriangle::hits(Ray &ray)
    {
        // TODO
        return std::nullopt;
    }

    const Maths::Point3D &PrimitiveTriangle::getOrigin() const
    {
        return _origin;
    }

    Maths::Point3D &PrimitiveTriangle::getOrigin()
    {
        return _origin;
    }

    Maths::RGB PrimitiveTriangle::getColor() const
    {
        return _color;
    }
}
