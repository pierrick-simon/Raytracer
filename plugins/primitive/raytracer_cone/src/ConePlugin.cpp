/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DESCRIPTION
*/

#include <iostream>
#include <ParserUtils.hpp>

#include "ConePlugin.hpp"

#include <PrimitiveCone.hpp>

namespace RayTracer {
    const std::string_view & ConePlugin::getObjectsTypeName()
    {
        return CONE_TYPE_NAME;
    }

    std::unique_ptr<IObject> ConePlugin::parseObject(
    libconfig::Setting const &element, BuilderMap &builders,
        TextureGenerationMap &texture)
    {
        double r = 0;
        std::optional<double> h = std::nullopt;

        std::cout << "Loading cone..." << std::endl;

        Maths::Point3D origin = ParserUtils::parseVector3D(element["origin"]);
        Material mat = ParserUtils::getBuilder(element, builders).build();
        r = ParserUtils::parseDouble(element, "r");
        if (element.exists("h"))
            h = ParserUtils::parseDouble(element, "h");
        else
            h = std::nullopt;
        return std::make_unique<PrimitiveCone>(origin, r, h, mat, ParserUtils::parseTexture(element, texture));
    }
}
