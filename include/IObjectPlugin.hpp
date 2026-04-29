/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef IOBJECTPLUGIN_HPP
    #define IOBJECTPLUGIN_HPP
    #include <libconfig.h++>
    #include <memory>
    #include <string>
    #include <vector>

    #include "IObject.hpp"

namespace RayTracer {
    class IObjectPlugin {
    public:
        virtual ~IObjectPlugin() = default;

        virtual const std::string_view &getObjectsTypeName() = 0;

        virtual std::vector<std::unique_ptr<IObject>> parseObjects(
            libconfig::Setting const &element) = 0;
    };
}

#endif
