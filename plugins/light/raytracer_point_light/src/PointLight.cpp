/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DisplaySFML
*/

#include "PointLight.hpp"

namespace RayTracer {
    PointLight::PointLight(const Maths::Point3D &pos, Maths::RGB color,
        double falloutDistance) :
        _pos(pos),
        _color(color),
        falloutDistance(falloutDistance)
    {
    }

    Maths::RGB PointLight::getLightAmount(const Ray &ray)
    {
        double distance = this->_pos.distance(ray.origin);
        double lightPercentage = distance / this->falloutDistance;

        return this->_color * lightPercentage;
    }
}
