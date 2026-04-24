/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#ifndef DIRECTIONALLIGHT_HPP
    #define DIRECTIONALLIGHT_HPP
    #include "ILightSource.hpp"

namespace RayTracer {
    class DirectionalLight : public ILightSource {
    public:
        DirectionalLight(int x, int y, int z);

        Maths::Vector3D getPosition() override;
        Maths::RGB getColor() override;
        double getLightAmount(const Ray &ray) override;
    };
}

#endif //DIRECTIONALLIGHT_HPP
