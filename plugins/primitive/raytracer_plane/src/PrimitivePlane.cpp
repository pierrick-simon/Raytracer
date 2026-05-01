/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DisplaySFML
*/

#include "PrimitivePlane.hpp"

namespace RayTracer {
    PrimitivePlane::PrimitivePlane(PrimitivePlane::Axis axis, double pos, Maths::RGB color) :
        _axis(axis),
        _pos(pos),
        _color(color)
    {
    }

    std::optional<HitInfo> PrimitivePlane::hits(Ray &ray)
    {
        std::optional<HitInfo> info = std::nullopt;
        Maths::Vector3D normal;

        if (_axis == PrimitivePlane::Axis::X)
            normal = Maths::Vector3D(1, 0, 0);
        if (_axis == PrimitivePlane::Axis::Y)
            normal = Maths::Vector3D(0, 1, 0);
        if (_axis == PrimitivePlane::Axis::Z)
            normal = Maths::Vector3D(0, 0, 1);
        double origin = ray.origin.x * normal.x + ray.origin.y
            * normal.y + ray.origin.z * normal.z;
        double direction = ray.direction.x * normal.x + ray.direction.y
            * normal.y + ray.direction.z * normal.z;
        if (direction != 0) {
            double t = (_pos - origin) / direction;
            if (t >= 0) {
                Maths::Point3D point(ray.origin + t);
                point = Maths::Point3D(point.x * ray.direction.x, point.y
                    * ray.direction.y, point.z * ray.direction.z);
                info = {point, normal, Maths::Vector3D(point, ray.origin).length()};
            }
        }
        return info;
    }

    PrimitivePlane::Axis PrimitivePlane::getAxis() const
    {
        return _axis;
    }

    double PrimitivePlane::getPos() const
    {
        return _pos;
    }

    Maths::RGB PrimitivePlane::getColor() const
    {
        return _color;
    }

    const std::unordered_map<std::string, PrimitivePlane::Axis>
        PrimitivePlane::_axisName = {
        {"X", PrimitivePlane::Axis::X},
        {"Y", PrimitivePlane::Axis::Y},
        {"Z", PrimitivePlane::Axis::Z},
    };
}
