/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#include "Objects/Lights/PointLight.hpp"

namespace RayTracer {
    PointLight::PointLight(int x, int y, int z)
    {
        _pos = Maths::Vector3D{static_cast<double>(x),
            static_cast<double>(y),
            static_cast<double>(z)};
        _color = Maths::RGB{255, 255, 255};
        _strength = 0.0;
    }

    Maths::Vector3D PointLight::getPosition()
    {
        return _pos;
    }

    Maths::RGB PointLight::getColor()
    {
        return _color;
    }

    double PointLight::getLightAmount(const Ray &ray)
    {
        // TODO
        return 0.0;
    }
}