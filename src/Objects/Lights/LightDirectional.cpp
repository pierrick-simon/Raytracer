/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#include "Objects/Lights/DirectionalLight.hpp"

namespace RayTracer {
    DirectionalLight::DirectionalLight(int x, int y, int z) :
        _pos(static_cast<double>(x),
            static_cast<double>(y),
            static_cast<double>(z)),
        _color(Maths::RGB(255, 255, 255)),
        _strength(1)
    {
    }

    Maths::RGB DirectionalLight::getLightAmount(const Ray &ray)
    {
        return this->_color;
    }
}
