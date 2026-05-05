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
        Material material) : _origin(origin),
        _height(height),
        _width(width),
        _length(length),
        _material(material)
    {
        Maths::Point3D apex(origin.x, origin.y, origin.z + height);
        Maths::Point3D A(origin.x - width / 2, origin.y - length / 2, origin.z);
        Maths::Point3D B(origin.x + width / 2, origin.y - length / 2, origin.z);
        Maths::Point3D C(origin.x + width / 2, origin.y + length / 2, origin.z);
        Maths::Point3D D(origin.x - width / 2, origin.y + length / 2, origin.z);

        _pyramid = TriangleShape({
            PrimitiveTriangle(A, B, apex, material),
            PrimitiveTriangle(B, C, apex, material),
            PrimitiveTriangle(C, D, apex, material),
            PrimitiveTriangle(D, A, apex, material),
            PrimitiveTriangle(A, C, B, material),
            PrimitiveTriangle(A, D, C, material),
        });
    }

    std::optional<HitInfo> Pyramid::hits(Ray const &ray)
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

    Material Pyramid::getMaterial() const
    {
        return _material;
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
