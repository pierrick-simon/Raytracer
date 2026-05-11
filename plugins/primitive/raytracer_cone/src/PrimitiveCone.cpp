/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/


#include "RayTracer.hpp"
#include "PrimitiveCone.hpp"

namespace RayTracer {
    PrimitiveCone::PrimitiveCone(const Maths::Point3D &origin,
        double const radius, std::optional<double> const height,
        Material const &Material) : _origin(origin), _radius(radius),
        _height(height), _material(Material)
    {
    }

    std::optional<HitInfo> PrimitiveCone::hits(const Ray &ray)
    {
        // TODO
        return std::nullopt;
    }

    HitInfo PrimitiveCone::fillHitInfo(const Ray &ray, double t) const
    {
        HitInfo hit;
        // TODO
        return hit;
    }

    const Maths::Point3D &PrimitiveCone::getOrigin() const
    {
        return _origin;
    }

    Maths::Point3D &PrimitiveCone::getOrigin()
    {
        return _origin;
    }

    double PrimitiveCone::getRadius() const
    {
        return _radius;
    }

    std::optional<double> PrimitiveCone::getHeight() const
    {
        return _height;
    }
}