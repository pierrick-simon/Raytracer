/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#include "Objects/Lights/Lights.hpp"

#include <utility>

namespace RayTracer {
    Lights::Lights(std::vector<std::unique_ptr<ILightSource>> &lights) :
    _lights(std::move(lights)){}

    void Lights::addLight(std::unique_ptr<ILightSource> element)
    {
        _lights.push_back(std::move(element));
    }

    Maths::Vector3D Lights::getPosition()
    {
        return _pos;
    }

    Maths::RGB Lights::getColor()
    {
        return _color;
    }

    double Lights::getLightAmount(const Ray &ray)
    {
        // TODO
        return 0.0;
    }
}
