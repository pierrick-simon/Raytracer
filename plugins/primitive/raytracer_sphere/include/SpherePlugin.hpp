/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef SPHEREPLUGIN_HPP
    #define SPHEREPLUGIN_HPP
    #include "IObjectPlugin.hpp"

namespace RayTracer {
    class SpherePlugin : public IObjectPlugin {
    public:
        const std::string_view &getObjectsTypeName() override;

        std::vector<std::unique_ptr<IObject>> parseObjects(
            libconfig::Setting const &element) override;

    private:
        static constexpr std::string_view SPHERE_TYPE_NAME = "spheres";
    };
} // RayTracer

#endif
