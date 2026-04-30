/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DisplaySFML
*/

#include "PrimitiveSphere.hpp"

namespace RayTracer {
    PrimitiveSphere::PrimitiveSphere(const Maths::Point3D &origin, float radius,
        Maths::RGB color):
        _origin(origin),
        _radius(radius),
        _color(color)
    {
    }

    PrimitiveSphere::PrimitiveSphere():
        _origin(0, 2, 0),
        _radius(0.5),
        _color(Maths::RGB())
    {
    }

    std::optional<HitInfo> PrimitiveSphere::hits(Ray &ray)
    {
        ray.origin.x -= _origin.x;
        ray.origin.y -= _origin.y;
        ray.origin.z -= _origin.z;

        double a = (ray.direction.x * ray.direction.x) + (
                       ray.direction.y * ray.direction.y) + (
                       ray.direction.z * ray.direction.z);
        double b = ray.direction.dot(Maths::Vector3D(ray.origin)) * 2;
        double c = (ray.origin.x * ray.origin.x) + (ray.origin.y * ray.origin.y)
                   + (ray.origin.z * ray.origin.z) - (_radius * _radius);
        double delta = (b * b) - (4 * a * c);
        if (delta >= 0)
            return {};
        return {};
    }

    void PrimitiveSphere::setX(float x)
    {
        this->_origin.x = x;
    }

    void PrimitiveSphere::setY(float y)
    {
        this->_origin.y = y;
    }

    void PrimitiveSphere::setZ(float z)
    {
        this->_origin.z = z;
    }

    void PrimitiveSphere::setOrigin(const Maths::Point3D &newOrigin)
    {
        this->_origin = newOrigin;
    }

    void PrimitiveSphere::setRadius(float r)
    {
        this->_radius = r;
    }

    void PrimitiveSphere::setColor(Maths::RGB const color)
    {
        _color = color;
    }

    const Maths::Point3D &PrimitiveSphere::getOrigin() const
    {
        return this->_origin;
    }

    Maths::Point3D &PrimitiveSphere::getOrigin()
    {
        return this->_origin;
    }

    float PrimitiveSphere::getRadius() const
    {
        return this->_radius;
    }

    Maths::RGB PrimitiveSphere::getColor() const
    {
        return _color;
    }
}
