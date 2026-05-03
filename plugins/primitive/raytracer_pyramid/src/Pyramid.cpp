/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#include "Pyramid.hpp"

namespace RayTracer {
    Pyramid::Pyramid(const Maths::Point3D &origin,
        double height, double width, double length,
        Maths::RGB const color) : _origin(origin),
        _height(height),
        _width(width),
        _length(length),
        _color(color)
    {
        Maths::Point3D apex(origin.x, origin.y + height, origin.z);
        Maths::Point3D A(origin.x - width / 2, origin.y, origin.z - length / 2);
        Maths::Point3D B(origin.x + width / 2, origin.y, origin.z - length / 2);
        Maths::Point3D C(origin.x + width / 2, origin.y, origin.z + length / 2);
        Maths::Point3D D(origin.x - width / 2, origin.y, origin.z + length / 2);

        _pyramid = TriangleShape({
            PrimitiveTriangle(A, B, apex, color),
            PrimitiveTriangle(B, C, apex, color),
            PrimitiveTriangle(C, D, apex, color),
            PrimitiveTriangle(D, A, apex, color),
            PrimitiveTriangle(A, C, B, color),
            PrimitiveTriangle(A, D, C, color),
        });
    }

    std::optional<HitInfo> Pyramid::hits(Ray &ray)
    {
        return _pyramid.hits(ray);
    }

    const Maths::Point3D &Pyramid::getOrigin() const
    {
        return _origin;
    }

    Maths::Point3D &Pyramid::getOrigin()
    {
        return _origin;
    }

    Maths::RGB Pyramid::getColor() const
    {
        return _color;
    }

    double Pyramid::getHeight() const
    {
        return _height;
    }

    double Pyramid::getWidth() const
    {
        return _width;
    }

    double Pyramid::getLength() const
    {
        return _length;
    }
}
