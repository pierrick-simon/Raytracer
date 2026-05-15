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
        libconfig::Setting const &element, BuilderMap &map,
        TextureGenerationMap &texture)
    {
        std::cout << "Loading sphere..." << std::endl;
        Maths::Point3D origin = ParserUtils::parsePoint3D(element);
        double r = ParserUtils::parseDouble(element, "r");

        return std::make_unique<PrimitiveSphere>(origin, r,
            ParserUtils::getBuilder(element, map).build(),
            ParserUtils::parseTexture(element, texture));
    }

} // RayTracer