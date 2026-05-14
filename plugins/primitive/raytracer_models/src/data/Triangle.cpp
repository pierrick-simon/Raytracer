/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#include <utility>
#include <iostream>

#include "data/Triangle.hpp"

namespace RayTracer {
    namespace {
        constexpr double EPSILON = 0.0000001;
    }

    Triangle::Triangle(const Maths::Point3D &a, const Maths::Point3D &b,
        const Maths::Point3D &c,
        std::optional<std::reference_wrapper<const Texture>> texture,
        std::optional<std::array<Maths::Vector3D, 3>> texCoords) :
        _points{a, b, c},
        _texture(texture),
        _texCoords(std::move(texCoords)),
        _ab(b - a),
        _ac(c - a)
    {
    }

    const std::array<Maths::Point3D, 3> &Triangle::getPoints() const noexcept
    {
        return _points;
    }

    std::optional<HitInfo> Triangle::createHitInfo(const Ray &ray, double u,
        double v, double t) const
    {
        HitInfo hit;

        hit.hitPos = ray.origin + ray.direction * t;
        hit.hitDist = t;
        hit.impactNormal = _ab.crossProduct(_ac).normalized();
        if (_texture && _texCoords) {
            double w = 1.0 - u - v;
            auto &coords = _texCoords.value();
            Maths::Vector2D uv(
                coords[0].getX() * w + coords[1].getX() * u
                    + coords[2].getX() * v,
                coords[0].getY() * w + coords[1].getY() * u
                    + coords[2].getY() * v
            );
            hit.textureColor = _texture->get().getColor(uv, false);
        }
        return hit;
    }

    std::optional<HitInfo> Triangle::hits(const Ray &ray) const
    {
        const Maths::Vector3D pvec = ray.direction.crossProduct(_ac);
        const double det = _ab.dot(pvec);
        if (det > -EPSILON && det < EPSILON)
            return std::nullopt;

        const double invDet = 1.0 / det;
        const Maths::Vector3D tvec = ray.origin - _points[0];
        const double u = tvec.dot(pvec) * invDet;
        if (u < 0.0 || u > 1.0)
            return std::nullopt;

        const Maths::Vector3D qvec = tvec.crossProduct(_ab);
        const double v = ray.direction.dot(qvec) * invDet;
        if (v < 0.0 || (u + v) > 1.0)
            return std::nullopt;

        const double t = _ac.dot(qvec) * invDet;
        if (t <= EPSILON)
            return std::nullopt;
        return createHitInfo(ray, u, v, t);
    }
} // RayTracer
