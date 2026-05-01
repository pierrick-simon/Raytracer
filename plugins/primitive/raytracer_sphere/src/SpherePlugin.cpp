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

    std::unique_ptr<IObject> SpherePlugin::parseObject(
        libconfig::Setting const &element, std::shared_ptr<IMaterial> material)
    {
        std::cout << "Loading sphere..." << std::endl;
        Maths::Point3D origin;
        double r;

        element.lookupValue("x", origin.x);
        element.lookupValue("y", origin.x);
        element.lookupValue("z", origin.x);
        element.lookupValue("r", r);
        return std::make_unique<PrimitiveSphere>(origin, r, material);
    }
} // RayTracer