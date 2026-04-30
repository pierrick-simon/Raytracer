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

    std::unique_ptr<IObject> PlanePlugin::parsePlane(
        libconfig::Setting const &element)
    {
        std::cout << "Loading plane..." << std::endl;
        std::string axisName = element["axis"];
        auto axis = PrimitivePlane::getAxisName().find(axisName);
        if (axis == PrimitivePlane::getAxisName().end())
            throw libconfig::SettingTypeException(element);
        double pos = element["position"];
        Maths::RGB color = ParserUtils::parseColor(element["color"]);
        return std::make_unique<PrimitivePlane>(axis->second, pos, color);
    }

    std::vector<std::unique_ptr<IObject>> PlanePlugin::parseObjects(
        libconfig::Setting const &element)
    {
        int count = element.getLength();
        std::vector<std::unique_ptr<IObject>> plane;

        for (int i = 0; i < count; ++i) {
            const libconfig::Setting &sphere = element[i];
            plane.push_back(parsePlane(sphere));
        }
        return std::move(plane);
    }
} // RayTracer