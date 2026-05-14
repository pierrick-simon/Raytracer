/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#include "RayTracer.hpp"
#include "PrimitiveCone.hpp"

#include <utility>

namespace RayTracer {
    PrimitiveCone::PrimitiveCone(const Maths::Point3D &origin,
        double const radius, std::optional<double> const height,
        Material Material) : _origin(origin), _radius(radius),
        _height(height), _material(std::move(Material))
    {
    }

    std::optional<HitInfo> PrimitiveCone::hitsInfinite(Ray const &ray) const
    {
        Maths::Vector3D diff = ray.origin - _origin;
        double k = _height.has_value() ? (_radius / _height.value()) *
            (_radius / _height.value()) : 1.0;
        double a = ray.direction.getX() * ray.direction.getX() + ray.direction.getY() *
            ray.direction.getY() - k * ray.direction.getZ() * ray.direction.getZ();
        double b = 2.0 * (diff.getX() * ray.direction.getX()+ diff.getY() *
            ray.direction.getY() - k * diff.getZ() * ray.direction.getZ());
        double c = diff.getX() * diff.getX() + diff.getY() * diff.getY()
            - k * diff.getZ() * diff.getZ();
        double delta = b * b - 4.0 * a * c;

        if (delta < 0.0)
            return std::nullopt;

        double t1 = (-b - sqrt(delta)) / (2.0 * a);
        double t2 = (-b + sqrt(delta)) / (2.0 * a);
        double t = t1 > DOUBLE_OFFSET ? t1 : t2;

        if (t < DOUBLE_OFFSET || diff.getZ() + ray.direction.getZ() * t > 0.0)
            return std::nullopt;

        return fillHitInfo(ray, t);
    }

    void PrimitiveCone::getBottomCapBestT(std::optional<double> &bestT,
        double t, double hx, double hy) const
    {
        if (hx * hx + hy * hy <= _radius * _radius && (!bestT.has_value()
            || t < bestT.value()))
            bestT = t;
    }

    bool PrimitiveCone::getSlideBestT(std::optional<double> &bestT, double t,
        double hitZ) const
    {
        if (hitZ >= 0.0 && hitZ <= _height.value()) {
            if (!bestT.has_value() || t < bestT.value())
                bestT = t;
            return true;
        }
        return false;
    }

    std::optional<double> PrimitiveCone::hitSlide(Ray const &ray,
        Maths::Vector3D diff,
        double a, double b, double delta) const
    {
        std::optional<double> bestT = std::nullopt;
        double sqrtDelta = sqrt(delta);
        for (double const t: {
                 (-b - sqrtDelta) / (2.0 * a),
                 (-b + sqrtDelta) / (2.0 * a)
             }) {
            if (t < DOUBLE_OFFSET)
                continue;
            double hitZ = diff.getZ() + ray.direction.getZ() * t;
            if (getSlideBestT(bestT, t, hitZ))
                break;
        }
        return bestT;
    }

    void PrimitiveCone::hitCap(Ray const &ray, Maths::Vector3D diff,
        std::optional<double> &bestT) const
    {
        if (std::abs(ray.direction.getZ()) > DOUBLE_OFFSET) {
            double t = -diff.getZ() / ray.direction.getZ();
            if (t > DOUBLE_OFFSET) {
                double hx = diff.getX() + ray.direction.getX() * t;
                double hy = diff.getY() + ray.direction.getY() * t;
                getBottomCapBestT(bestT, t, hx, hy);
            }
        }
    }

    std::optional<HitInfo> PrimitiveCone::hitsCone(Ray const &ray) const
    {
        Maths::Vector3D diff = ray.origin - _origin;
        std::optional<HitInfo> hitInfo = std::nullopt;
        double k = (_radius / _height.value()) * (_radius / _height.value());
        double a = ray.direction.getX() * ray.direction.getX() + ray.direction.
            getY() * ray.direction.getY() - k * ray.direction.getZ() * ray.
            direction.getZ();
        double b = 2.0 * (diff.getX() * ray.direction.getX() + diff.getY() * ray
            .direction.getY()
            - k * (diff.getZ() - _height.value()) * ray.direction.getZ());
        double c = diff.getX() * diff.getX() + diff.getY() * diff.getY() - k * (
            diff.getZ() - _height.value()) * (diff.getZ() - _height.value());
        double delta = b * b - 4.0 * a * c;

        if (delta < 0.0)
            return std::nullopt;
        std::optional<double> bestT = hitSlide(ray, diff, a, b, delta);
        hitCap(ray, diff, bestT);
        if (bestT.has_value())
            hitInfo = fillHitInfo(ray, bestT.value());
        return hitInfo;
    }

    std::optional<HitInfo> PrimitiveCone::hits(const Ray &ray)
    {
        return _height == std::nullopt ? hitsInfinite(ray) : hitsCone(ray);
    }

    Maths::Vector3D PrimitiveCone::coneNormal(Maths::Point3D hitPos) const
    {
        double x = hitPos.getX() - _origin.getX();
        double y = hitPos.getY() - _origin.getY();
        double z = hitPos.getZ() - _origin.getZ();

        if (_height.has_value() && z <= DOUBLE_OFFSET)
            return Maths::Vector3D{0, 0, -1};

        double k = _height.has_value()
            ? (_radius / _height.value()) * (_radius / _height.value()) : 1.0;

        Maths::Vector3D normal{x, y, -k * z};

        return normal.normalized();
    }

    HitInfo PrimitiveCone::fillHitInfo(const Ray &ray, double t) const
    {
        HitInfo hit;
        hit.hitPos.getX() = ray.origin.getX() + ray.direction.getX() * t;
        hit.hitPos.getY() = ray.origin.getY() + ray.direction.getY() * t;
        hit.hitPos.getZ() = ray.origin.getZ() + ray.direction.getZ() * t;
        hit.hitDist = hit.hitPos.distance(ray.origin);
        hit.impactNormal = coneNormal(hit.hitPos);
        hit.material = _material;
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
