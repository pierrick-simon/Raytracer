/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** BoundingBox
*/

#include <algorithm>
#include <cmath>
#include <limits>

#include "data/BoundingBox.hpp"

namespace RayTracer {
    BoundingBox::BoundingBox() :
        _valid(false)
    {
    }

    BoundingBox::BoundingBox(const Maths::Point3D &minPoint,
        const Maths::Point3D &maxPoint) :
        _min(minPoint),
        _max(maxPoint),
        _valid(true)
    {
    }

    Maths::Vector3D BoundingBox::createVertexWithOffset(const Vertex &vertex,
        const Maths::Vector3D &offset)
    {
        return Maths::Vector3D{
            vertex.getX() + offset.getX(),
            vertex.getY() + offset.getY(),
            vertex.getZ() + offset.getZ()
        };
    }

    BoundingBox BoundingBox::fromVertices(const std::vector<Vertex> &vertices,
        const Maths::Point3D &offset)
    {
        if (vertices.empty())
            return {};

        Maths::Vector3D min = createVertexWithOffset(vertices[0], offset);
        Maths::Vector3D max = min;

        for (const auto &vertex: vertices) {
            Maths::Vector3D pos = createVertexWithOffset(vertex, offset);

            for (size_t i = 0; i < 3; ++i) {
                min[i] = std::min(min[i], pos[i]);
                max[i] = std::max(max[i], pos[i]);
            }
        }

        return BoundingBox(min, max);
    }

    bool BoundingBox::hits(const Ray &ray) const
    {
        if (!this->_valid)
            return false;

        double tmin = -std::numeric_limits<double>::infinity();
        double tmax = std::numeric_limits<double>::infinity();

        for (size_t i = 0; i < 3; ++i)
            if (!updateIntersectionInterval(ray, i, tmin, tmax))
                return false;

        return isIntersectionValid(tmin, tmax);
    }

    bool BoundingBox::updateIntersectionInterval(const Ray &ray, size_t axis,
        double &tmin, double &tmax) const
    {
        if (std::abs(ray.direction[axis]) <=
            std::numeric_limits<double>::epsilon()) {
            return ray.origin[axis] >= this->_min[axis]
                   && ray.origin[axis] <= this->_max[axis];
        }

        double invDir = 1.0 / ray.direction[axis];
        double t0 = (this->_min[axis] - ray.origin[axis]) * invDir;
        double t1 = (this->_max[axis] - ray.origin[axis]) * invDir;

        if (t0 > t1)
            std::swap(t0, t1);

        tmin = std::max(tmin, t0);
        tmax = std::min(tmax, t1);

        return tmax >= tmin;
    }

    bool BoundingBox::isIntersectionValid(double tmin, double tmax)
    {
        return tmax >= std::max(tmin, 0.0);
    }

    bool BoundingBox::isValid() const
    {
        return this->_valid;
    }
}
