/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DisplaySFML
*/

#include "PrimitiveSphere.hpp"

namespace RayTracer {
    PrimitiveSphere::PrimitiveSphere(const Maths::Point3D &origin, double radius,
        Maths::RGB color):
        _origin(origin),
        _radius(radius),
        _color(color)
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

    const Maths::Point3D &PrimitiveSphere::getOrigin() const
    {
        return this->_origin;
    }

    Maths::Point3D &PrimitiveSphere::getOrigin()
    {
        return this->_origin;
    }

    double PrimitiveSphere::getRadius() const
    {
        return this->_radius;
    }

    Maths::RGB PrimitiveSphere::getColor() const
    {
        return _color;
    }
}
