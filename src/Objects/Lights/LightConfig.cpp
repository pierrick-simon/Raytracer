/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#include "../../../include/Objects/Lights/LightConfig.hpp"

#include <utility>

namespace RayTracer {
    LightConfig::LightConfig(double ambient, double diffuse,
        std::vector<std::unique_ptr<ILightSource>> lights) : _lights(std::move(lights)),
    _ambient(ambient), _diffuse(diffuse) {}

    double LightConfig::getAmbient() const
    {
        return _ambient;
    }

    double LightConfig::getDiffuse() const
    {
        return _diffuse;
    }

    void LightConfig::setAmbient(double ambient)
    {
        _ambient = ambient;
    }

    void LightConfig::setDiffuse(double diffuse)
    {
        _diffuse = diffuse;
    }
}
