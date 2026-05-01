/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef IMATERIALPLUGIN_HPP
    #define IMATERIALPLUGIN_HPP
    #include <libconfig.h++>
    #include <memory>
    #include <string>
    #include <vector>

    #include "IMaterial.hpp"

namespace RayTracer {
    class IMaterialPlugin {
    public:
        virtual ~IMaterialPlugin() = default;

        virtual const std::string_view &getMaterialsTypeName() = 0;

        virtual std::vector<std::unique_ptr<IMaterial>> parseMaterials(
            libconfig::Setting const &element) = 0;
    };
}

#endif
