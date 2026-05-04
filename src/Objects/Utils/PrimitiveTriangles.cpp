/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#include "PrimitiveTriangles.hpp"

namespace RayTracer {
    PrimitiveTriangle::PrimitiveTriangle(const Maths::Point3D &a,
        const Maths::Point3D &b, const Maths::Point3D &c,
        const Material &mat) : _a(a), _b(b), _c(c), _material(mat)
    {
    }

    std::optional<HitInfo> PrimitiveTriangle::fillHitInfo(Ray const &ray,
        Maths::Vector3D const &AB, Maths::Vector3D const &AC, double t)
    {
        HitInfo hit{};
        hit.hitPos = ray.origin + ray.direction * t;
        hit.hitDist = Maths::Vector3D(hit.hitPos, ray.origin).length();
        hit.impactNormal = AB.crossProduct(AC).normalized();
        hit.material = _material;
        return std::make_optional<HitInfo>(hit);
    }

    std::optional<HitInfo> PrimitiveTriangle::rayTriangleMollerTrumboreAlgo(Ray const &ray, Maths::Vector3D AB, Maths::Vector3D AC, Maths::Vector3D h)
    {
        double det = AB.dot(h);

        if (std::abs(det) < EPSILON)
            return std::nullopt;

        double invDet = 1.0 / det;
        Maths::Vector3D AO(_a, ray.origin);

        double u = AO.dot(h) * invDet;
        if (u < 0.0 || u > 1.0)
            return std::nullopt;

        Maths::Vector3D q = AO.crossProduct(AB);
        double v = ray.direction.dot(q) * invDet;
        if (v < 0.0 || u + v > 1.0)
            return std::nullopt;

        double t = AC.dot(q) * invDet;
        if (t < EPSILON)
            return std::nullopt;
        return fillHitInfo(ray, AB, AC, t);
    }

    std::optional<HitInfo> PrimitiveTriangle::hits(Ray const &ray)
    {

        Maths::Vector3D AB(_a, _b);
        Maths::Vector3D AC(_a, _c);
        Maths::Vector3D h = ray.direction.crossProduct(AC);
        
        return rayTriangleMollerTrumboreAlgo(ray, AB, AC, h);
    }
}
