/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#include "RayTracer.hpp"
#include "PrimitiveCylinder.hpp"

namespace RayTracer {
    PrimitiveCylinder::PrimitiveCylinder(const Maths::Point3D &origin,
        double const radius, std::optional<double> const height,
        Material const &Material) : _origin(origin), _radius(radius),
        _height(height), _material(Material)
    {
    }

    std::optional<HitInfo> PrimitiveCylinder::hits(const Ray &ray)
    {
        return _height == std::nullopt ? hitsInfinite(ray) : hitsCylinder(ray);
    }

    HitInfo PrimitiveCylinder::fillHitInfo(const Ray &ray, double t) const
    {
        HitInfo hit;
        hit.hitPos.x = ray.origin.x + (ray.direction.x * t);
        hit.hitPos.y = ray.origin.y + (ray.direction.y * t);
        hit.hitPos.z = ray.origin.z + (ray.direction.z * t);
        hit.hitDist = Maths::Vector3D(hit.hitPos, ray.origin).length();
        hit.impactNormal = cylNormal(hit.hitPos);
        hit.material = _material;
        return hit;
    }

    void PrimitiveCylinder::hitCaps(Ray const &ray, std::optional<double> &bestT) const
    {
        double ox = ray.origin.x - _origin.x;
        double oy = ray.origin.y - _origin.y;
        double oz = ray.origin.z - _origin.z;

        double dx = ray.direction.x;
        double dy = ray.direction.y;
        double dz = ray.direction.z;

        if (std::abs(dz) > DOUBLE_OFFSET) {
            double t = -oz / dz;
            if (t > DOUBLE_OFFSET) {
                double hx = ox + dx * t;
                double hy = oy + dy * t;
                if (hx * hx + hy * hy <= _radius * _radius)
                    if (!bestT.has_value() || t < bestT.value())
                        bestT = t;
            }
            t = (_height.value() - oz) / dz;
            if (t > DOUBLE_OFFSET) {
                double hx = ox + dx * t;
                double hy = oy + dy * t;
                if (hx * hx + hy * hy <= _radius * _radius)
                    if (!bestT.has_value() || t < bestT.value())
                        bestT = t;
            }
        }
    }

    void PrimitiveCylinder::computeHitSurface(const Ray &ray, double a, double b, double delta, std::optional<double> &bestT) const
    {
        double dz = ray.direction.z;
        double oz = ray.origin.z - _origin.z;

        double sqrtDelta = sqrt(delta);
        for (double t: {(-b - sqrtDelta) / (2.0 * a), (-b + sqrtDelta) / (2.0 * a)}) {
            if (t < DOUBLE_OFFSET)
                continue;
            double hitZ = oz + dz * t;
            if (hitZ >= 0.0 && hitZ <= _height.value()) {
                if (!bestT.has_value() || t < bestT.value())
                    bestT = t;
                break;
            }
        }
    }

    std::optional<double> PrimitiveCylinder::hitSurface(const Ray &ray) const
    {
        double ox = ray.origin.x - _origin.x;
        double oy = ray.origin.y - _origin.y;

        double dx = ray.direction.x;
        double dy = ray.direction.y;


        double a = dx * dx + dy * dy;
        double b = 2.0 * (ox * dx + oy * dy);
        double c = ox * ox + oy * oy - _radius * _radius;

        double delta = b * b - 4.0 * a * c;

        std::optional<double> bestT = std::nullopt;

        if (delta >= 0.0)
            computeHitSurface(ray, a, b, delta, bestT);
        return bestT;
    }

    std::optional<HitInfo> PrimitiveCylinder::hitsCylinder(const Ray &ray) const
    {
        std::optional<double> bestT = hitSurface(ray);
        hitCaps(ray, bestT);
        std::optional<HitInfo> hitInfo = std::nullopt;

        if (bestT.has_value())
            hitInfo = fillHitInfo(ray, bestT.value());
        return hitInfo;
    }

    Maths::Vector3D PrimitiveCylinder::cylNormal(Maths::Vector3D p) const
    {
        double pz = p.z - _origin.z;
        Maths::Vector3D result;

        if (pz <= DOUBLE_OFFSET)
            result = {0, 0, -1};
        else if (pz >= _height.value() - DOUBLE_OFFSET)
            result =  {0, 0, 1};
        else {
            double nx = p.x - _origin.x;
            double ny = p.y - _origin.y;
            double len = sqrt(nx * nx + ny * ny);
            result = {nx / len, ny / len, 0};
        }
        return result;
    }

    HitInfo PrimitiveCylinder::fillHitInfinite(const Ray &ray, double t) const
    {
        HitInfo hit;
        hit.hitPos.x = ray.origin.x + ray.direction.x * t;
        hit.hitPos.y = ray.origin.y + ray.direction.y * t;
        hit.hitPos.z = ray.origin.z + ray.direction.z * t;
        hit.hitDist = Maths::Vector3D(hit.hitPos, ray.origin).length();

        double nx = hit.hitPos.x - _origin.x;
        double ny = hit.hitPos.y - _origin.y;
        double len = sqrt(nx * nx + ny * ny);
        hit.impactNormal = {nx / len, ny / len, 0};

        hit.material = _material;
        return hit;
    }

    std::optional<HitInfo> PrimitiveCylinder::hitsInfinite(const Ray &ray) const
    {
        double ox = ray.origin.x - _origin.x;
        double oy = ray.origin.y - _origin.y;

        double dx = ray.direction.x;
        double dy = ray.direction.y;

        double a = dx * dx + dy * dy;
        double b = 2.0 * (ox * dx + oy * dy);
        double c = ox * ox + oy * oy - _radius * _radius;

        double delta = b * b - 4.0 * a * c;

        bool hit = true;
        if (delta < 0.0)
            hit = false;

        double sqrtDelta = sqrt(delta);
        double t1 = (-b - sqrtDelta) / (2.0 * a);
        double t2 = (-b + sqrtDelta) / (2.0 * a);

        double t = t1 > DOUBLE_OFFSET ? t1 : t2;
        if (t < DOUBLE_OFFSET)
            hit = false;
        return hit ? fillHitInfinite(ray, t) : std::optional<HitInfo>(std::nullopt);
    }

    const Maths::Point3D &PrimitiveCylinder::getOrigin() const
    {
        return _origin;
    }

    Maths::Point3D &PrimitiveCylinder::getOrigin()
    {
        return _origin;
    }

    double PrimitiveCylinder::getRadius() const
    {
        return _radius;
    }

    std::optional<double> PrimitiveCylinder::getHeight() const
    {
        return _height;
    }
}
