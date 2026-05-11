/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DisplaySFML
*/

#include <algorithm>

#include "PointLight.hpp"

namespace RayTracer {
    PointLight::PointLight(const Maths::Point3D &pos, Maths::Color color,
        double falloutDistance) :
        ALightSource(pos),
        _color(color),
        _falloutDistance(falloutDistance)
    {
    }

    Maths::Color PointLight::getLightAmount(const Ray &ray) const
    {
        double distance = this->_pos.distance(ray.origin);
        double lightPercentage = distance / this->_falloutDistance;

        return Maths::Color(this->_color * (1 - std::clamp(lightPercentage, 0.0, 1.0)));
    }
}
