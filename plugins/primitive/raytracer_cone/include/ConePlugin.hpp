/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef CONEPLUGIN_HPP
    #define CONEPLUGIN_HPP
    #include "IObjectPlugin.hpp"

namespace RayTracer {
    class ConePlugin : public IObjectPlugin {
    public:
        const std::string_view &getObjectsTypeName() override;

        std::unique_ptr<IObject> parseObject(
            libconfig::Setting const &, BuilderMap &) override;

    private:
        static constexpr std::string_view CONE_TYPE_NAME = "cones";
    };
} // RayTracer

#endif
