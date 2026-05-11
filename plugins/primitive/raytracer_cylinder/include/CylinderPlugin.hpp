/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef CYLINDERPLUGIN_HPP
    #define CYLINDERPLUGIN_HPP
    #include "IObjectPlugin.hpp"

namespace RayTracer {
    class CylinderPlugin : public IObjectPlugin {
    public:
        const std::string_view &getObjectsTypeName() override;

        std::unique_ptr<IObject> parseObject(
            libconfig::Setting const &, BuilderMap &) override;

    private:
        static constexpr std::string_view CYLINDER_TYPE_NAME = "cylinders";
    };
} // RayTracer

#endif
