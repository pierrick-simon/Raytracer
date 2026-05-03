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

    std::unique_ptr<IObject> PyramidPlugin::parseTriangle(
        libconfig::Setting const &element)
    {
        double h = 0;
        double w = 0;
        double l = 0;

        std::cout << "Loading pyramids..." << std::endl;

        Maths::Point3D origin = ParserUtils::parseVector3D(element["origin"]);
        Maths::RGB color = ParserUtils::parseColor(element["color"]);
        element.lookupValue("h", h);
        element.lookupValue("w", w);
        element.lookupValue("l", l);

        return std::make_unique<Pyramid>(origin, h, w, l, color);
    }

    std::vector<std::unique_ptr<IObject>> PyramidPlugin::parseObjects(
        libconfig::Setting const &element)
    {
        int count = element.getLength();
        std::vector<std::unique_ptr<IObject>> triangles;

        for (int i = 0; i < count; ++i) {
            const libconfig::Setting &sphere = element[i];
            triangles.push_back(parseTriangle(sphere));
        }
        return std::move(triangles);
    }
} // RayTracer
