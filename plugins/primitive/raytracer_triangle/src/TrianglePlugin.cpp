/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#include <iostream>

#include "PrimitiveTriangle.hpp"
#include "TrianglePlugin.hpp"
#include "ParserUtils.hpp"

namespace RayTracer {
    const std::string_view &TrianglePlugin::getObjectsTypeName()
    {
        return TRIANGLE_TYPE_NAME;
    }

    std::unique_ptr<IObject> TrianglePlugin::parseTriangle(
        libconfig::Setting const &element)
    {
        // TODO
        return std::make_unique<PrimitiveTriangle>(Maths::Point3D(0, 0, 0), 0, 0, 0,
            Maths::RGB(0, 0, 0));
    }

    std::vector<std::unique_ptr<IObject>> TrianglePlugin::parseObjects(
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
