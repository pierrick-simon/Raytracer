/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DisplaySFML
*/

#include "PrimitivePlane.hpp"

namespace RayTracer {
    PrimitivePlane::PrimitivePlane(PrimitivePlane::Axis axis,
        double pos, Material material) :
        _axis(axis),
        _pos(pos),
        _material(material)
    {
        if (_axis == PrimitivePlane::Axis::X)
            _normal = Maths::Vector3D(1, 0, 0);
        if (_axis == PrimitivePlane::Axis::Y)
            _normal = Maths::Vector3D(0, 1, 0);
        if (_axis == PrimitivePlane::Axis::Z)
            _normal = Maths::Vector3D(0, 0, 1);
    }

    Maths::Vector3D PrimitivePlane::getNormal(double direction)
    {
        Maths::Vector3D normal = _normal;

        if (direction > 0)
            normal *= -1;
        return normal;
    }

    std::optional<HitInfo> PrimitivePlane::hits(const Ray &ray)
    {
        std::optional<HitInfo> info = std::nullopt;

        double origin = ray.origin.dot(_normal);
        double direction = ray.direction.getX() * _normal.getX() + ray.direction.getY()
            * _normal.getY() + ray.direction.getZ() * _normal.getZ();
        if (direction != 0) {
            double t = (_pos - origin) / direction;
            if (t > 0) {
               Maths::Point3D point = ray.origin + ray.direction * t;
                info = {point, _normal,
                    point.distance(ray.origin), _material};
            }
        }
        return info;
    }

    std::unordered_map<std::string, PrimitivePlane::Axis>
        PrimitivePlane::getAxisName()
    {
        return _axisName;
    }

    PrimitivePlane::Axis PrimitivePlane::getAxis() const
    {
        return _axis;
    }

    double PrimitivePlane::getPos() const
    {
        return _pos;
    }

    const std::unordered_map<std::string, PrimitivePlane::Axis>
        PrimitivePlane::_axisName = {
        {"X", PrimitivePlane::Axis::X},
        {"Y", PrimitivePlane::Axis::Y},
        {"Z", PrimitivePlane::Axis::Z},
    };
}
