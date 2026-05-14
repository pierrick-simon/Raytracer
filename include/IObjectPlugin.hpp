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
    #include <unordered_map>


    #include "IObject.hpp"
    #include "Material.hpp"
    #include "PortablePixMap.hpp"

namespace RayTracer {

    using BuilderMap =
        const std::unordered_map<std::string, Material::Builder>;
    using TextureGenerationMap =
        const std::unordered_map<std::string, PortablePixMap>;

    class IObjectPlugin {
    public:
        virtual ~IObjectPlugin() = default;

        virtual const std::string_view &getObjectsTypeName() = 0;

        virtual std::unique_ptr<IObject> parseObject(
            libconfig::Setting const &element,
            BuilderMap &, TextureGenerationMap &) = 0;
    };
}

#endif
