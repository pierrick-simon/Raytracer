/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#include "Parser/ParserUtils.hpp"

namespace RayTracer {

    Maths::Vector3D ParserUtils::parseVector3D(
        libconfig::Setting const &element)
    {
        double x = 0;
        double y = 0;
        double z = 0;

        element.lookupValue("x", x);
        element.lookupValue("y", y);
        element.lookupValue("z", z);
        return Maths::Vector3D{x, y, z};
    }

    Maths::RGB ParserUtils::parseColor(libconfig::Setting const &element)
    {
        unsigned int r = 0;
        unsigned int g = 0;
        unsigned int b = 0;

        element.lookupValue("r", r);
        element.lookupValue("g", g);
        element.lookupValue("b", b);
        if (r > 255 || g > 255 || b > 255)
            throw libconfig::SettingTypeException(element);
        return Maths::RGB{
            static_cast<unsigned char>(r),
            static_cast<unsigned char>(g),
            static_cast<unsigned char>(b)
        };
    }
} // RayTracer