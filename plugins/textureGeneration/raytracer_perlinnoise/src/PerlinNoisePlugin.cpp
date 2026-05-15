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
        std::size_t smooth = SMOOTH;
        Maths::Vector2U spread(SPREAD, SPREAD);

        if (size.getX() == 0)
            size.getX()++;
        if (size.getY() == 0)
            size.getY()++;
        if (element.exists("smooth"))
            smooth = ParserUtils::parseSizeT(element, "smooth");
        if (element.exists("spread")) {
            spread = ParserUtils::parseVector2U(element["spread"]);
            spread.getX() = std::min(spread.getX(), unsigned(size.getX() - 1));
            spread.getY() = std::min(spread.getY(), unsigned(size.getY() - 1));
        }
        return std::make_unique<PerlinNoise>(size, seed, smooth, spread);
    }
}
