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

        virtual Maths::RGB getLightAmount(const Ray &) = 0;
    };
}

#endif //ILIGHTSOURCE_HPP