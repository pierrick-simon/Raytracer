/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PerlinNoisePlugin
*/

#include <iostream>
#include "PerlinNoisePlugin.hpp"
#include "ParserUtils.hpp"
#include "PerlinNoise.hpp"

namespace RayTracer {
    const std::string_view &PerlinNoisePlugin::getTexturesTypeName()
    {
        return PERLINNOISE_TYPE_NAME;
    }

    std::unique_ptr<ITextureGeneration> PerlinNoisePlugin::parseTexture(
        libconfig::Setting const &element)
    {
        std::cout << "Loading perlin noise..." << std::endl;
        auto size = ParserUtils::parseVector2U(element["size"]);
        auto seed = ParserUtils::parseSizeT(element, "seed");

        if (size.getX() == 0)
            size.getX()++;
        if (size.getY() == 0)
            size.getY()++;
        
        return std::make_unique<PerlinNoise>(size, seed);
    }
}
