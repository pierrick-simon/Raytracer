/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#include <libconfig.h++>
#include <utility>

#include "ConfigFileParser.hpp"

#include <iostream>

#include "Camera.hpp"

namespace RayTracer {
    ConfigFileParser::ConfigFileParser(std::string s) : _filepath(std::move(s))
    {
    }

    ConfigFileParser::ParserError::ParserError(char *s)
    {
        _err = s;
    }

    const char *ConfigFileParser::ParserError::what() const noexcept
    {
        return _err;
    }

    Maths::Vector3<int> ConfigFileParser::parseVector3I(
        libconfig::Setting const &element)
    {
        int x = 0;
        int y = 0;
        int z = 0;

        element.lookupValue("x", x);
        element.lookupValue("y", y);
        element.lookupValue("z", z);
        return Maths::Vector3{x, y, z};
    }

    Camera ConfigFileParser::parseCamera() const
    {
        libconfig::Config cfg;

        cfg.readFile(_filepath.c_str());

        const libconfig::Setting &root = cfg.getRoot();
        const double fov = root["camera"]["fieldOfView"];

        const libconfig::Setting &reso = root["camera"]["resolution"];
        unsigned int resHeight = 0;
        unsigned int resWidth = 0;
        reso.lookupValue("width", resWidth);
        reso.lookupValue("height", resHeight);
        const Maths::Vector3<unsigned int> resolution{resWidth, resHeight, 0};
        const libconfig::Setting &pos = root["camera"]["position"];
        const Maths::Vector3<int> position = parseVector3I(pos);
        const libconfig::Setting &rot = root["camera"]["rotation"];
        const Maths::Vector3<int> rotation = parseVector3I(rot);

        return Camera{resolution, position, rotation, fov};
    }
}
