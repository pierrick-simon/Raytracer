/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#ifndef ILIGHTSOURCE_HPP
    #define ILIGHTSOURCE_HPP
    #include "Ray.hpp"
    #include "Vector3.hpp"

namespace RayTracer {
    class ILightSource {
    public:
        virtual ~ILightSource() = default;

        virtual Maths::Vector3D getPosition() = 0;
        virtual Maths::RGB getColor() = 0;
        virtual double getLightAmount(const Ray &) = 0;
    protected:
        Maths::Vector3D _pos{};
        Maths::RGB _color{};
        double _strength = 0.0;
    };
}

#endif //ILIGHTSOURCE_HPP