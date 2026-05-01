/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DisplaySFML
*/

#include "PrimitiveSphere.hpp"
#include <iostream>

namespace RayTracer {
    PrimitiveSphere::PrimitiveSphere(const Maths::Point3D &origin,
        double radius, Maths::RGB color):
        _origin(origin),
        _radius(radius),
        _color(color)
    {
    }

    HitInfo PrimitiveSphere::computeHitInfos(Ray &ray, double x) noexcept
    {
        HitInfo hit;
        hit.hitPos.x = ray.origin.x + (ray.direction.x * x);
        hit.hitPos.y = ray.origin.y + (ray.direction.y * x);
        hit.hitPos.z = ray.origin.z + (ray.direction.z * x);
        hit.hitDist = Maths::Vector3D(hit.hitPos, ray.origin).length();
        ray.color = _color;
        return hit;
    }

    double PrimitiveSphere::solveQuadratic(double a, double b,
            double c, double delta) noexcept
    {
        double x = 0;
        if (delta == 0)
            x = (b * -1.0) / (2.0 * a);
        else
            x = ((b * -1.0) - sqrt(delta)) / (2.0 * a);
        return x;
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
        if (delta < 0)
            return {};
        double x = solveQuadratic(a, b, c, delta);
        if (x < 0)
            return {};
        return computeHitInfos(ray, x);
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
