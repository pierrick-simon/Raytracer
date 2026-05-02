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

        Maths::RGB getLightAmount(const Ray &ray) override;
    private:
        Maths::Point3D _pos;
        Maths::RGB _color;
        double _strength;
    };
}

#endif //DIRECTIONALLIGHT_HPP
