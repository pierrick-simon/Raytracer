/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#include <iostream>
#include "ModelPlugin.hpp"
#include "ParserUtils.hpp"
#include "Model.hpp"

namespace RayTracer {
    const std::string_view &ModelPlugin::getObjectsTypeName()
    {
        return MODEL_TYPE_NAME;
    }

    std::unique_ptr<IObject> ModelPlugin::parseObject(
        libconfig::Setting const &element, BuilderMap &map)
    {
        std::cout << "Loading model..." << std::endl;
        Maths::Point3D origin = ParserUtils::parsePoint3D(element);
        std::string path = element["path"];

        return std::make_unique<Model>(origin, path,
            ParserUtils::getBuilder(element, map).build());
    }

} // RayTracer