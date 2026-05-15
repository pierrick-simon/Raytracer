/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#include <utility>

#include "data/Triangle.hpp"

namespace RayTracer {
    namespace {
        constexpr double EPSILON = 0.0000001;
    }

    Triangle::Triangle(const std::array<const Maths::Point3D, 3> &points,
        const Material &material,
        std::optional<std::reference_wrapper<const Texture>> texture,
        std::optional<std::array<Maths::Vector3D, 3>> texCoords) :
        _points{points},
        _texture(texture),
        _texCoords(std::move(texCoords)),
        _material(material),
        _ab(points[1] - points[0]),
        _ac(points[2] - points[0])
    {
    }

    std::optional<Maths::Color> Triangle::getTextureColor(const Maths::Vector2D &uvPos) const
    {
        std::optional<Maths::Color> color;
        if (_texture && _texCoords) {
            double w = 1.0 - uvPos[0] - uvPos[1];
            auto &coords = _texCoords.value();
            Maths::Vector2D uv(
                coords[0].getX() * w + coords[1].getX() * uvPos[0]
                    + coords[2].getX() * uvPos[1],
                coords[0].getY() * w + coords[1].getY() * uvPos[0]
                    + coords[2].getY() * uvPos[1]
            );
            color = _texture->get().getColor(uv, false);
        }
        return color;
    }

    std::optional<HitInfo> Triangle::createHitInfo(const Ray &ray,
        double t, const Maths::Vector2D &uvPos) const
    {
        HitInfo hit;

        hit.hitPos = ray.origin + ray.direction * t;
        hit.hitDist = t;
        hit.impactNormal = _ab.crossProduct(_ac).normalized();
        hit.textureColor = this->getTextureColor(uvPos);
        hit.material = _material;
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
        return createHitInfo(ray, t, Maths::Vector2D{u, v});
    }
} // RayTracer
