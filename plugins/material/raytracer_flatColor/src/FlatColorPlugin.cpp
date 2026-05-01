/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#include <iostream>
#include "FlatColorPlugin.hpp"
#include "ParserUtils.hpp"
#include "MaterialFlatColor.hpp"

namespace RayTracer {
    const std::string_view &FlatColorPlugin::getMaterialsTypeName()
    {
        return FLATCOLOR_TYPE_NAME;
    }

    std::shared_ptr<IMaterial> FlatColorPlugin::parseMaterial(
            libconfig::Setting const &element)
    {
        Maths::RGB color = ParserUtils::parseColor(element["color"]);
        return std::make_shared<MaterialFlatColor>(color);
    }
} // RayTracer