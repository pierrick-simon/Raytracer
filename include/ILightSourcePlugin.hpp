/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef ILIGHTSOURCEPLUGIN_HPP
    #define ILIGHTSOURCEPLUGIN_HPP
    #include <libconfig.h++>
    #include <memory>
    #include <string>

    #include "ILightSource.hpp"

namespace RayTracer {
    class ILightSourcePlugin {
    public:
        virtual ~ILightSourcePlugin() = default;

        virtual const std::string_view &getLightsTypeName() = 0;

        virtual std::unique_ptr<ILightSource> parseLight(
            libconfig::Setting const &element) = 0;
    };
}

#endif
