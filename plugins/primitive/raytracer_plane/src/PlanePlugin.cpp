/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#include <iostream>
#include "PlanePlugin.hpp"
#include "ParserUtils.hpp"
#include "PrimitivePlane.hpp"

namespace RayTracer {
    const std::string_view &PlanePlugin::getObjectsTypeName()
    {
        return PLANE_TYPE_NAME;
    }

     std::unique_ptr<IObject> PlanePlugin::parseObject(
        libconfig::Setting const &element, BuilderMap &map)
    {
        std::cout << "Loading plane..." << std::endl;
        std::string axisName = element["axis"];
        if (!PrimitivePlane::getAxisName().contains(axisName))
            throw libconfig::SettingTypeException(element);
        double pos = ParserUtils::parseDouble(element, "position");
        return std::make_unique<PrimitivePlane>(PrimitivePlane::getAxisName()
            .at(axisName), pos,
            ParserUtils::getBuilder(element, map).build());
    }
} // RayTracer