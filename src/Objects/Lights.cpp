/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#include "Lights.hpp"

#include <utility>

namespace RayTracer {
    Lights::Lights(double ambient, double diffuse,
        const std::vector<Maths::Vector3<int>>& point,
        const std::vector<Maths::Vector3<int>>& directional) :
    _ambient(ambient), _diffuse(diffuse), _point(point), _directional(directional) {}

    void Lights::setAmbient(double ambient)
    {
        _ambient = ambient;
    }

    void Lights::setDiffuse(double diffuse)
    {
        _diffuse = diffuse;
    }

    void Lights::setPoint(std::vector<Maths::Vector3<int>> point)
    {
        _point = std::move(point);
    }

    void Lights::setDirectional(std::vector<Maths::Vector3<int>> directional)
    {
        _directional = std::move(directional);
    }

    double Lights::getAmbient() const
    {
        return _ambient;
    }

    double Lights::getDiffuse() const
    {
        return _diffuse;
    }

    std::vector<Maths::Vector3<int>> Lights::getPoint()
    {
        return _point;
    }

    std::vector<Maths::Vector3<int>> Lights::getDirectional()
    {
        return _directional;
    }
}
