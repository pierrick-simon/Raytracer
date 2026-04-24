/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#ifndef LIGHTS_HPP
    #define LIGHTS_HPP
#include <memory>
#include <vector>

#include "ILightSource.hpp"
#include "Vector3.hpp"

namespace RayTracer {
    class Lights : public ILightSource{
    public:
        Lights(std::vector<std::unique_ptr<ILightSource>>&);

        void addLight(std::unique_ptr<ILightSource>);

        Maths::Vector3D getPosition() override;
        Maths::RGB getColor() override;
        double getLightAmount(const Ray &) override;
    private:
        std::vector<std::unique_ptr<ILightSource>> _lights;
    };
}

#endif //LIGHTS_HPP