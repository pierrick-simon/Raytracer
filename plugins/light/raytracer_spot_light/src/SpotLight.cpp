/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DisplaySFML
*/

#include "SpotLight.hpp"

#include <numeric>

namespace RayTracer {
    SpotLight::Builder SpotLight::Builder::builder()
    {
        return {};
    }

    Maths::Point3D SpotLight::Builder::getPos() const
    {
        return _pos;
    }

    Maths::Vector3D SpotLight::Builder::getDirection() const
    {
        return _direction;
    }

    Maths::RGB SpotLight::Builder::getColor() const
    {
        return _color;
    }

    double SpotLight::Builder::getFalloutDistance() const
    {
        return _falloutDistance;
    }

    double SpotLight::Builder::getOuterConeAngle() const
    {
        return _outerConeAngle;
    }

    double SpotLight::Builder::getInnerConeAngle() const
    {
        return this->_innerConeAngle;
    }

    SpotLight::Builder SpotLight::Builder::withPos(
        const Maths::Point3D &pos) const
    {
        Builder copy = *this;
        copy._pos = pos;
        return copy;
    }

    SpotLight::Builder SpotLight::Builder::withDirection(
        const Maths::Vector3D &dir) const
    {
        Builder copy = *this;
        copy._direction = dir;
        return copy;
    }

    SpotLight::Builder SpotLight::Builder::withColor(Maths::RGB color) const
    {
        Builder copy = *this;
        copy._color = color;
        return copy;
    }

    SpotLight::Builder SpotLight::Builder::withFalloutDistance(
        double falloutDistance) const
    {
        Builder copy = *this;
        copy._falloutDistance = falloutDistance;
        return copy;
    }

    SpotLight::Builder SpotLight::Builder::withOuterConeAngle(
        double outerAngle) const
    {
        Builder copy = *this;
        copy._outerConeAngle = outerAngle;
        return copy;
    }

    SpotLight::Builder SpotLight::Builder::withInnerConeAngle(
        double innerAngle) const
    {
        Builder copy = *this;
        copy._innerConeAngle = innerAngle;
        return copy;
    }

    SpotLight::SpotLight(const Builder &builder) :
        ALightSource(builder.getPos()),
        _direction(builder.getDirection()),
        _color(builder.getColor()),
        _falloutDistance(builder.getFalloutDistance()),
        _outerConeAngle(builder.getOuterConeAngle()),
        _innerConeAngle(builder.getInnerConeAngle())
    {
    }

    Maths::RGB SpotLight::getLightAmount(const Ray &ray) const
    {
        auto delta = Maths::Vector3D(this->_pos - ray.origin);
        double angleDelta = delta.getAngle(ray.direction);
        double anglePercentage =
            angleDelta / (_outerConeAngle - _innerConeAngle);
        anglePercentage = std::clamp(anglePercentage, 0.0, 1.0);
        double distance = this->_pos.distance(ray.origin);
        double distancePercentage = distance / this->_falloutDistance;
        distancePercentage = (1 - std::clamp(distancePercentage, 0.0, 1.0));

        return this->_color *
               std::midpoint(distancePercentage, anglePercentage);
    }
}
