/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#ifndef LIGHTCONFIG_HPP
    #define LIGHTCONFIG_HPP
    #include <memory>
    #include <vector>

    #include "ILightSource.hpp"

namespace RayTracer {
    class LightConfig {
    public:
        LightConfig() {};
        LightConfig(double ambient, double diffuse, std::vector<std::unique_ptr<ILightSource>> lights);
        [[nodiscard]] double getAmbient() const;
        [[nodiscard]] double getDiffuse() const;

        void setAmbient(double);
        void setDiffuse(double);

        std::vector<std::unique_ptr<ILightSource>> _lights;
    private:
        double _ambient;
        double _diffuse;
    };
}

#endif //LIGHTCONFIG_HPP