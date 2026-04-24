/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#ifndef POINTLIGHT_HPP
    #define POINTLIGHT_HPP
    #include "ILightSource.hpp"

namespace RayTracer {
    class PointLight : public ILightSource {
    public:
        PointLight(int x, int y, int z);

        Maths::Vector3D getPosition() override;
        Maths::RGB getColor() override;
        double getLightAmount(const Ray &ray) override;
    };
}

#endif //POINTLIGHT_HPP