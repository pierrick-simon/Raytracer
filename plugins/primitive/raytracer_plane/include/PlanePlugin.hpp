/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef PLANEPLUGIN_HPP
    #define PLANEPLUGIN_HPP
    #include "IObjectPlugin.hpp"

namespace RayTracer {
    class PlanePlugin : public IObjectPlugin {
    public:
        const std::string_view &getObjectsTypeName() override;

        std::unique_ptr<IObject> parseObject(
            libconfig::Setting const &, BuilderMap &, TextureGenerationMap &) override;

    private:
        static constexpr std::string_view PLANE_TYPE_NAME = "planes";
    };
} // RayTracer

#endif
