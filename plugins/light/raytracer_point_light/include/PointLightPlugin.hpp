/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef SPHEREPLUGIN_HPP
    #define SPHEREPLUGIN_HPP
    #include "ILightSourcePlugin.hpp"

namespace RayTracer {
    class PointLightPlugin : public ILightSourcePlugin {
    public:
        const std::string_view &getLightsTypeName() override;

        std::unique_ptr<ILightSource> parseLight(libconfig::Setting const &element) override;

    private:
        static constexpr std::string_view POINT_LIGHT_TYPE_NAME = "point_lights";
    };
} // RayTracer

#endif
