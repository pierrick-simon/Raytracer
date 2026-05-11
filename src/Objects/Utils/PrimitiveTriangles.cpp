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
        const Material &mat) :
        _a(a),
        _b(b),
        _c(c),
        _material(mat)
    {
    }

    std::optional<HitInfo> PrimitiveTriangle::fillHitInfo(Ray const &ray,
        Maths::Vector3D const &AB, Maths::Vector3D const &AC, double t) const
    {
        HitInfo hit = HitInfo();
        hit.hitPos = Maths::Vector3D(ray.origin + ray.direction * t);
        hit.hitDist = hit.hitPos.distance(ray.origin);
        hit.impactNormal = AB.crossProduct(AC).normalized();
        hit.material = _material;
        return hit;
    }

    std::optional<HitInfo> PrimitiveTriangle::rayTriangleMollerTrumboreAlgo(
        Ray const &ray, Maths::Vector3D AB, Maths::Vector3D AC,
        Maths::Vector3D h) const
    {
        double det = AB.dot(h);

        if (std::abs(det) < EPSILON)
            return std::nullopt;

        double invDet = 1.0 / det;
        Maths::Vector3D AO = ray.origin - _a;

        double u = AO.dot(h) * invDet;
        if (u < -EPSILON || u - 1 > EPSILON)
            return std::nullopt;

        Maths::Vector3D q = AO.crossProduct(AB);
        double v = ray.direction.dot(q) * invDet;
        if (v < -EPSILON || u + v - 1 > EPSILON)
            return std::nullopt;

        double t = AC.dot(q) * invDet;
        if (t <= EPSILON)
            return std::nullopt;
        return fillHitInfo(ray, AB, AC, t);
    }

    std::optional<HitInfo> PrimitiveTriangle::hits(Ray const &ray) const
    {
        Maths::Vector3D AB = _b - _a;
        Maths::Vector3D AC = _c - _a;
        Maths::Vector3D h = ray.direction.crossProduct(AC);
        
        return rayTriangleMollerTrumboreAlgo(ray, AB, AC, h);
    }
}
