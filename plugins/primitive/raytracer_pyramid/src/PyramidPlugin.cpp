/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#include <iostream>

#include "Pyramid.hpp"
#include "PyramidPlugin.hpp"
#include "ParserUtils.hpp"

namespace RayTracer {
    const std::string_view &PyramidPlugin::getObjectsTypeName()
    {
        return TRIANGLE_TYPE_NAME;
    }

    std::unique_ptr<IObject> PyramidPlugin::parsePyramid(
        libconfig::Setting const &element, BuilderMap &builders)
    {
        std::cout << "Loading pyramids..." << std::endl;

        Maths::Point3D origin = ParserUtils::parseVector3D(element["origin"]);
        Material mat = ParserUtils::getBuilder(element, builders).build();
        double h = ParserUtils::parseDouble(element, "h");
        double w = ParserUtils::parseDouble(element, "w");
        double l = ParserUtils::parseDouble(element, "l");

        return std::make_unique<Pyramid>(origin, h, w, l, mat);
    }

    std::unique_ptr<IObject> PyramidPlugin::parseObject(libconfig::Setting const &element, BuilderMap &builders)
    {
        return parsePyramid(element, builders);
    }

} // RayTracer
