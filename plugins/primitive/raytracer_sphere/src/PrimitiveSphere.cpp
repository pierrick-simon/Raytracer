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
        double radius, Material material) :
        _origin(origin),
        _radius(radius),
        _material(material)
    {
    }

    HitInfo PrimitiveSphere::computeHitInfos(const Ray &ray, double x)
        const noexcept
    {
        HitInfo hit;
        Maths::Vector3D directionMultiplied = ray.direction * x;
        hit.hitPos = ray.origin + directionMultiplied;
        hit.hitDist = hit.hitPos.distance(ray.origin);
        hit.impactNormal = (hit.hitPos - _origin) / _radius;
        hit.material = _material;
        return hit;
    }

    double PrimitiveSphere::solveQuadratic(double a, double b,
            double c, double delta) noexcept
    {
        double x = 0;
        if (delta == 0)
            x = (b * -1.0) / (2.0 * a);
        else {
            x = ((b * -1.0) - sqrt(delta)) / (2.0 * a);
            if (x < 0)
               x = ((b * -1.0) + sqrt(delta)) / (2.0 * a);
        }
        return x;
    }

    std::optional<HitInfo> PrimitiveSphere::hits(const Ray &ray)
    {
        Maths::Vector3D origin = ray.origin - _origin;

        double a = (ray.direction.getX() * ray.direction.getX()) + (
                       ray.direction.getY() * ray.direction.getY()) + (
                       ray.direction.getZ() * ray.direction.getZ());
        double b = ray.direction.dot(Maths::Vector3D(origin)) * 2;
        double c = (origin.getX() * origin.getX()) + (origin.getY() * origin.getY())
                   + (origin.getZ() * origin.getZ()) - (_radius * _radius);
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
}
