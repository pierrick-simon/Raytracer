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

        std::unique_ptr<IObject> parsePyramid(
            libconfig::Setting const &element, BuilderMap &builders);

        std::unique_ptr<IObject> parseObject(
            libconfig::Setting const &, BuilderMap &) override;

    private:
        static constexpr std::string_view TRIANGLE_TYPE_NAME = "pyramids";
    };
} // RayTracer

#endif
