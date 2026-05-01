/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef FLATCOLORPLUGIN_HPP
    #define FLATCOLORPLUGIN_HPP
    #include "IMaterialPlugin.hpp"

namespace RayTracer {
    class FlatColorPlugin : public IMaterialPlugin {
    public:
        const std::string_view &getMaterialsTypeName() override;

        std::shared_ptr<IMaterial> parseMaterial(
            libconfig::Setting const &element) override;

    private:
        static constexpr std::string_view FLATCOLOR_TYPE_NAME = "flat color";
    };
} // RayTracer

#endif
