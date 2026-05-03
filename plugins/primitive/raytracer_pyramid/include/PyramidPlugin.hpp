/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#ifndef PYRAMIDPLUGIN_HPP
    #define PYRAMIDPLUGIN_HPP

    #include "IObjectPlugin.hpp"

namespace RayTracer {
    class PyramidPlugin : public IObjectPlugin {
    public:
        const std::string_view &getObjectsTypeName() override;

        static std::unique_ptr<IObject> parseTriangle(
            libconfig::Setting const &element);

        std::vector<std::unique_ptr<IObject>> parseObjects(
            libconfig::Setting const &element) override;

    private:
        static constexpr std::string_view TRIANGLE_TYPE_NAME = "pyramid";
    };
} // RayTracer

#endif
