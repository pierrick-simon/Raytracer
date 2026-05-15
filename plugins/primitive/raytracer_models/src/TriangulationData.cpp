/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** TriangulationData
*/

#include <cmath>

#include "TriangulationData.hpp"

namespace RayTracer {
    TriangulationData::TriangulationData(std::vector<Maths::Point3D> polygon) :
        _polygon(std::move(polygon))
    {
        _indices.reserve(_polygon.size());
        for (size_t i = 0; i < _polygon.size(); ++i)
            _indices.push_back(i);
    }

    bool TriangulationData::triangulate()
    {
        if (_polygon.size() < 3)
            return false;

        Maths::Vector3D normal = computeNormal();
        if (normal.norm_squared() <= EPSILON * EPSILON)
            return false;

        _dropAxis = pickProjectionAxis(normal);
        _isCCW = signedArea2D() > 0.0;

        for (size_t guard = 0; _indices.size() > 2
            && guard < _polygon.size() * _polygon.size(); ++guard) {
            if (!clipNextEar())
                return false;
        }
        return _indices.size() <= 2;
    }

    const std::vector<std::array<size_t, 3>> &TriangulationData::getTriangles()
        const noexcept
    {
        return _triangles;
    }

    Maths::Vector3D TriangulationData::computeNormal() const
    {
        Maths::Vector3D normal{};

        for (size_t i = 0; i < _polygon.size(); ++i) {
            const auto &current = _polygon[i];
            const auto &next = _polygon[(i + 1) % _polygon.size()];
            normal.getX() += (current.getY() - next.getY())
                * (current.getZ() + next.getZ());
            normal.getY() += (current.getZ() - next.getZ())
                * (current.getX() + next.getX());
            normal.getZ() += (current.getX() - next.getX())
                * (current.getY() + next.getY());
        }
        return normal.normalized();
    }

    TriangulationData::ProjectionAxis
    TriangulationData::pickProjectionAxis(const Maths::Vector3D &normal)
    {
        double ax = std::abs(normal.getX());
        double ay = std::abs(normal.getY());
        double az = std::abs(normal.getZ());

        if (ay >= ax && ay >= az)
            return ProjectionAxis::Y;
        if (az >= ax && az >= ay)
            return ProjectionAxis::Z;
        return ProjectionAxis::X;
    }

    void TriangulationData::projectPoint(const Maths::Point3D &point,
        Maths::Vector2D &projected) const
    {
        if (_dropAxis == ProjectionAxis::X) {
            projected.getX() = point.getY();
            projected.getY() = point.getZ();
        } else if (_dropAxis == ProjectionAxis::Y) {
            projected.getX() = point.getX();
            projected.getY() = point.getZ();
        } else {
            projected.getX() = point.getX();
            projected.getY() = point.getY();
        }
    }

    double TriangulationData::signedArea2D() const
    {
        double area = 0.0;

        for (size_t i = 0; i < _polygon.size(); ++i) {
            Maths::Vector2D p1{};
            Maths::Vector2D p2{};

            projectPoint(_polygon[i], p1);
            projectPoint(_polygon[(i + 1) % _polygon.size()], p2);
            area += (p1.getX() * p2.getY() - p2.getX() * p1.getY());
        }
        return area * 0.5;
    }

    bool TriangulationData::isPointInTriangle2D(const Maths::Vector2D &p,
        const Maths::Vector2D &a, const Maths::Vector2D &b,
        const Maths::Vector2D &c)
    {
        Maths::Vector2D v0 = c - a;
        Maths::Vector2D v1 = b - a;
        Maths::Vector2D v2 = p - a;

        double dot00 = v0.dot(v0);
        double dot01 = v0.dot(v1);
        double dot02 = v0.dot(v2);
        double dot11 = v1.dot(v1);
        double dot12 = v1.dot(v2);

        double denom = dot00 * dot11 - dot01 * dot01;
        if (std::abs(denom) < EPSILON)
            return false;
        double invDenom = 1.0 / denom;
        double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
        double v = (dot00 * dot12 - dot01 * dot02) * invDenom;
        return (u >= -EPSILON) && (v >= -EPSILON)
            && (u + v <= 1.0 + EPSILON);
    }

    std::array<size_t, 3> TriangulationData::makeIndexTriplet(size_t i) const
    {
        const size_t count = _indices.size();

        return {
            _indices[(i + count - 1) % count],
            _indices[i],
            _indices[(i + 1) % count]
        };
    }

    bool TriangulationData::isConvexAt(
        const std::array<size_t, 3> &triplet) const
    {
        const size_t i0 = triplet[0];
        const size_t i1 = triplet[1];
        const size_t i2 = triplet[2];

        std::array<Maths::Vector2D, 3> points;

        projectPoint(_polygon[i0], points[0]);
        projectPoint(_polygon[i1], points[1]);
        projectPoint(_polygon[i2], points[2]);

        double cross = (points[1].getX() - points[0].getX())
            * (points[2].getY() - points[0].getY())
            - (points[1].getY() - points[0].getY())
            * (points[2].getX() - points[0].getX());
        return _isCCW ? (cross > EPSILON) : (cross < -EPSILON);
    }

    bool TriangulationData::containsPointInEar(
        const std::array<size_t, 3> &triplet) const
    {
        const size_t i0 = triplet[0];
        const size_t i1 = triplet[1];
        const size_t i2 = triplet[2];

        std::array<Maths::Vector2D, 3> points;

        projectPoint(_polygon[i0], points[0]);
        projectPoint(_polygon[i1], points[1]);
        projectPoint(_polygon[i2], points[2]);

        for (size_t k = 0; k < _indices.size(); ++k) {
            size_t idx = _indices[k];
            if (idx == i0 || idx == i1 || idx == i2)
                continue;
            Maths::Vector2D p{};
            projectPoint(_polygon[idx], p);
            if (isPointInTriangle2D(p, points[0], points[1], points[2]))
                return true;
        }
        return false;
    }

    void TriangulationData::appendTriangle(
        const std::array<size_t, 3> &triplet)
    {
        const size_t i0 = triplet[0];
        const size_t i1 = triplet[1];
        const size_t i2 = triplet[2];

        _triangles.push_back(_isCCW
            ? std::array{i0, i1, i2}
            : std::array{i2, i1, i0});
    }

    bool TriangulationData::tryClipEar(size_t i)
    {
        const std::array<size_t, 3> triplet = makeIndexTriplet(i);

        if (!isConvexAt(triplet))
            return false;
        if (containsPointInEar(triplet))
            return false;

        appendTriangle(triplet);
        _indices.erase(_indices.begin() + static_cast<long>(i));
        return true;
    }

    bool TriangulationData::clipNextEar()
    {
        for (size_t i = 0; i < _indices.size(); ++i) {
            if (tryClipEar(i))
                return true;
        }
        return false;
    }
}

