/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#include "Pyramid.hpp"

namespace RayTracer {
    Pyramid::Pyramid(const Maths::Point3D &origin,
        Maths::Vector2D size, double length,
        Material material, std::optional<Texture> texture) :
        _origin(origin),
        _height(size.getX()),
        _width(size.getY()),
        _length(length),
        _material(material),
        _texture(texture)
    {
        Maths::Point3D apex(origin.getX(), origin.getY(), origin.getZ() + _height);
        Maths::Point3D A(origin.getX() - _width / 2, origin.getY() - length / 2, origin.getZ());
        Maths::Point3D B(origin.getX() + _width / 2, origin.getY() - length / 2, origin.getZ());
        Maths::Point3D C(origin.getX() + _width / 2, origin.getY() + length / 2, origin.getZ());
        Maths::Point3D D(origin.getX() - _width / 2, origin.getY() + length / 2, origin.getZ());

        _pyramid = TriangleShape({
            PrimitiveTriangle(A, B, apex, material, _texture),
            PrimitiveTriangle(B, C, apex, material, _texture),
            PrimitiveTriangle(C, D, apex, material, _texture),
            PrimitiveTriangle(D, A, apex, material, _texture),
            PrimitiveTriangle(A, C, B, material, _texture),
            PrimitiveTriangle(A, D, C, material, _texture),
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
