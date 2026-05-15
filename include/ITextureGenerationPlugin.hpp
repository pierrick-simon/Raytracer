/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef ITEXTUREPLUGIN_HPP
    #define ITEXTUREPLUGIN_HPP
    #include <libconfig.h++>
    #include <memory>
    #include <string>
    #include <vector>

    #include "ITextureGeneration.hpp"
    #include "Material.hpp"

namespace RayTracer {
    class ITextureGenerationPlugin {
    public:
        virtual ~ITextureGenerationPlugin() = default;

        virtual const std::string_view &getTexturesTypeName() = 0;

        virtual std::unique_ptr<ITextureGeneration> parseTexture(
            libconfig::Setting const &element) = 0;
    };
}

#endif
