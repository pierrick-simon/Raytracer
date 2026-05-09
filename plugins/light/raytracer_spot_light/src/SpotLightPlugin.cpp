/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#include <iostream>
#include "SpotLightPlugin.hpp"
#include "ParserUtils.hpp"
#include "SpotLight.hpp"

namespace RayTracer {
    const std::string_view &SpotLightPlugin::getLightsTypeName()
    {
        return SPOT_LIGHT_TYPE_NAME;
    }

    std::unique_ptr<ILightSource> SpotLightPlugin::parseLight(
        libconfig::Setting const &element)
    {
        std::cout << "Loading spot light..." << std::endl;
        Maths::Point3D origin = ParserUtils::parsePoint3D(element["position"]);
        Maths::Vector3D direction = ParserUtils::parseVector3D(
            element["direction"]);
        Maths::Color color = ParserUtils::parseColor(element["color"]);
        double falloutDistance = ParserUtils::parseDouble(element,
            "falloutDistance");
        double outerAngle = ParserUtils::parseDouble(element, "outerConeAngle");
        double innerAngler =
            ParserUtils::parseDouble(element, "innerConeAngle");

        return std::make_unique<SpotLight>(
            SpotLight::Builder::builder()
            .withPos(origin)
            .withDirection(direction)
            .withColor(color)
            .withFalloutDistance(falloutDistance)
            .withInnerConeAngle(TORAD(innerAngler))
            .withOuterConeAngle(TORAD(outerAngle))
        );
    }
} // RayTracer
