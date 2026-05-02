/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#ifndef TRIANGLEPLUGIN_HPP
    #define TRIANGLEPLUGIN_HPP

    #include "IObjectPlugin.hpp"

namespace RayTracer {
    class TrianglePlugin : public IObjectPlugin {
    public:
        const std::string_view &getObjectsTypeName() override;

        static std::unique_ptr<IObject> parseTriangle(
            libconfig::Setting const &element);

        std::vector<std::unique_ptr<IObject>> parseObjects(
            libconfig::Setting const &element) override;

    private:
        static constexpr std::string_view TRIANGLE_TYPE_NAME = "triangles";
    };
} // RayTracer

#endif
