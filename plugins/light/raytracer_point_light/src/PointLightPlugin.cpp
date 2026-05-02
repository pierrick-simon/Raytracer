/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#include <iostream>
#include "PointLightPlugin.hpp"
#include "ParserUtils.hpp"
#include "PointLight.hpp"

namespace RayTracer {
    const std::string_view &PointLightPlugin::getLightsTypeName()
    {
        return POINT_LIGHT_TYPE_NAME;
    }

    std::unique_ptr<ILightSource> PointLightPlugin::parseLight(
        libconfig::Setting const &element)
    {
        std::cout << "Loading point light..." << std::endl;
        Maths::Point3D origin(element["x"], element["y"], element["z"]);
        Maths::RGB color = ParserUtils::parseColor(element["color"]);
        double falloutDistance = element["falloutDistance"];

        return std::make_unique<PointLight>(origin, color, falloutDistance);
    }
} // RayTracer