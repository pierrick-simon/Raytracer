/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#include <iostream>
#include "SpherePlugin.hpp"
#include "ParserUtils.hpp"
#include "PrimitiveSphere.hpp"

namespace RayTracer {
    const std::string_view &SpherePlugin::getObjectsTypeName()
    {
        return SPHERE_TYPE_NAME;
    }

    std::unique_ptr<IObject> SpherePlugin::parseSphere(
        libconfig::Setting const &element)
    {
        std::cout << "Loading sphere..." << std::endl;
        Maths::Point3D origin;
        double r;

        element.lookupValue("x", origin.x);
        element.lookupValue("y", origin.x);
        element.lookupValue("z", origin.x);
        element.lookupValue("r", r);
        Maths::RGB color = ParserUtils::parseColor(element["color"]);
        return std::make_unique<PrimitiveSphere>(origin, r, color);
    }

    std::vector<std::unique_ptr<IObject>> SpherePlugin::parseObjects(
        libconfig::Setting const &element)
    {
        int count = element.getLength();
        std::vector<std::unique_ptr<IObject>> spheres;

        for (int i = 0; i < count; ++i) {
            const libconfig::Setting &sphere = element[i];
            spheres.push_back(parseSphere(sphere));
        }
        return std::move(spheres);
    }
} // RayTracer