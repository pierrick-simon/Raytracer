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
        Material const &material, std::optional<Texture> texture) :
        _origin(origin), _radius(radius),
        _height(height), _material(material), _texture(texture)
    {
    }

    std::optional<HitInfo> PrimitiveCylinder::hits(const Ray &ray)
    {
        return _height == std::nullopt ? hitsInfinite(ray) : hitsCylinder(ray);
    }

    HitInfo PrimitiveCylinder::fillHitInfo(const Ray &ray, double t) const
    {
        HitInfo hit;
        hit.hitPos.getX() = ray.origin.getX() + (ray.direction.getX() * t);
        hit.hitPos.getY() = ray.origin.getY() + (ray.direction.getY() * t);
        hit.hitPos.getZ() = ray.origin.getZ() + (ray.direction.getZ() * t);
        hit.hitDist = hit.hitPos.distance(ray.origin);
        hit.impactNormal = cylNormal(hit.hitPos);
        hit.material = _material;

        if (_texture) {
            double nx = hit.hitPos.getX() - _origin.getX();
            double ny = hit.hitPos.getY() - _origin.getY();
            double u, v;
            if (std::abs(hit.impactNormal.getZ()) > 0.5) {
                u = nx / _radius * 0.5 + 0.5;
                v = ny / _radius * 0.5 + 0.5;
            } else {
                u = std::atan2(-ny, -nx) / (2.0 * M_PI) + 0.5;
                v = 1.0 - (hit.hitPos.getZ() - _origin.getZ()) / _height.value();
            }
            hit.textureColor = _texture->getColor(Maths::Vector2D(u, v), false);
        }
        return hit;
    }

    void PrimitiveCylinder::getBestT(std::optional<double> &bestT,
        const Ray &ray, double dz) const
    {
        double ox = ray.origin.getX() - _origin.getX();
        double oy = ray.origin.getY() - _origin.getY();
        double oz = ray.origin.getZ() - _origin.getZ();
        double dx = ray.direction.getX();
        double dy = ray.direction.getY();
        double t = -oz / dz;

        if (t > DOUBLE_OFFSET) {
            double hx = ox + dx * t;
            double hy = oy + dy * t;
            if (hx * hx + hy * hy <= _radius * _radius && (!bestT.has_value() ||
                t < bestT.value()))
                bestT = t;
        }
        t = (_height.value() - oz) / dz;
        if (t > DOUBLE_OFFSET) {
            double hx = ox + dx * t;
            double hy = oy + dy * t;
            if (hx * hx + hy * hy <= _radius * _radius && (!bestT.has_value() ||
                t < bestT.value()))
                bestT = t;
        }
    }

    void PrimitiveCylinder::hitCaps(Ray const &ray,
        std::optional<double> &bestT) const
    {
        double dz = ray.direction.getZ();

        if (std::abs(dz) > DOUBLE_OFFSET)
            getBestT(bestT, ray, dz);
    }

    void PrimitiveCylinder::computeHitSurface(const Ray &ray, double a,
        double b, double delta, std::optional<double> &bestT) const
    {
        double dz = ray.direction.getZ();
        double oz = ray.origin.getZ() - _origin.getZ();

        double sqrtDelta = sqrt(delta);
        for (double t:
             {(-b - sqrtDelta) / (2.0 * a), (-b + sqrtDelta) / (2.0 * a)}) {
            if (t < DOUBLE_OFFSET)
                continue;
            double hitZ = oz + dz * t;
            if (hitZ >= 0.0 && hitZ <= _height.value() && (!bestT.has_value() ||
                t < bestT.value())) {
                bestT = t;
                break;
            }
        }
    }

    std::optional<double> PrimitiveCylinder::hitSurface(const Ray &ray) const
    {
        double ox = ray.origin.getX() - _origin.getX();
        double oy = ray.origin.getY() - _origin.getY();

        double dx = ray.direction.getX();
        double dy = ray.direction.getY();

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
        double pz = p.getZ() - _origin.getZ();
        Maths::Vector3D result;

        if (pz <= DOUBLE_OFFSET)
            result = Maths::Vector3D{0, 0, -1};
        else if (pz >= _height.value() - DOUBLE_OFFSET)
            result = Maths::Vector3D{0, 0, 1};
        else {
            double nx = p.getX() - _origin.getX();
            double ny = p.getY() - _origin.getY();
            double len = sqrt(nx * nx + ny * ny);
            result = Maths::Vector3D{nx / len, ny / len, 0};
        }
        return result;
    }

    HitInfo PrimitiveCylinder::fillHitInfinite(const Ray &ray, double t) const
    {
        HitInfo hit;
        hit.hitPos.getX() = ray.origin.getX() + ray.direction.getX() * t;
        hit.hitPos.getY() = ray.origin.getY() + ray.direction.getY() * t;
        hit.hitPos.getZ() = ray.origin.getZ() + ray.direction.getZ() * t;
        hit.hitDist = hit.hitPos.distance(ray.origin);

        double nx = hit.hitPos.getX() - _origin.getX();
        double ny = hit.hitPos.getY() - _origin.getY();
        double len = sqrt(nx * nx + ny * ny);
        hit.impactNormal = Maths::Vector3D{nx / len, ny / len, 0};

        hit.material = _material;

        if (_texture) {
            double phi = std::atan2(-ny, -nx) + M_PI;
            double arcLength = phi * _radius;
            double hz = hit.hitPos.getZ() - _origin.getZ();
            hit.textureColor = _texture->getColor(
                Maths::Vector2D(arcLength, hz), true);
        }
        return hit;
    }

    std::optional<HitInfo> PrimitiveCylinder::hitsInfinite(const Ray &ray) const
    {
        double ox = ray.origin.getX() - _origin.getX();
        double oy = ray.origin.getY() - _origin.getY();
        double dx = ray.direction.getX();
        double dy = ray.direction.getY();

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
        return hit
            ? fillHitInfinite(ray, t) : std::optional<HitInfo>(std::nullopt);
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
