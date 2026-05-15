/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DESCRIPTION
*/

#include <iostream>
#include <ParserUtils.hpp>
#include <PrimitiveCylinder.hpp>

#include "CylinderPlugin.hpp"

namespace RayTracer {
    const std::string_view & CylinderPlugin::getObjectsTypeName()
    {
        return CYLINDER_TYPE_NAME;
    }

    std::unique_ptr<IObject> CylinderPlugin::parseObject(
        libconfig::Setting const &element, BuilderMap &builders,
        TextureGenerationMap &texture)
    {
        double r = 0;
        std::optional<double> h = std::nullopt;

        std::cout << "Loading cylinder..." << std::endl;

        Maths::Point3D origin = ParserUtils::parseVector3D(element["origin"]);
        Material mat = ParserUtils::getBuilder(element, builders).build();
        r = ParserUtils::parseDouble(element, "r");
        if (element.exists("h"))
            h = ParserUtils::parseDouble(element, "h");
        else
            h = std::nullopt;
        return std::make_unique<PrimitiveCylinder>(origin, r, h, mat, 
            ParserUtils::parseTexture(element, texture));
    }
}
