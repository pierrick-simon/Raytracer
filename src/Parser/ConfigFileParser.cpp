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
#include "Shpere.hpp"

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

    Maths::RGB ConfigFileParser::parseColor(libconfig::Setting const &element)
    {
        unsigned int r = 0;
        unsigned int g = 0;
        unsigned int b = 0;

        element.lookupValue("r", r);
        element.lookupValue("g", g);
        element.lookupValue("b", b);
        if (r > 255 || g > 255 || b > 255)
            throw libconfig::SettingTypeException(element);
        return Maths::RGB{static_cast<unsigned char>(r),
            static_cast<unsigned char>(g),
            static_cast<unsigned char>(b)};
    }

    Sphere ConfigFileParser::parseSphere(libconfig::Setting const &element)
    {
        int x = 0;
        int y = 0;
        int z = 0;
        unsigned int r = 0;
        Maths::RGB color{0, 0, 0};

        element.lookupValue("x", x);
        element.lookupValue("y", y);
        element.lookupValue("z", z);
        element.lookupValue("r", r);
        color = parseColor(element["color"]);
        return Sphere{x, y, z, r,color};
    }

    std::vector<Sphere> ConfigFileParser::parseSpheres(
        libconfig::Setting const &element)
    {
        int count = element.getLength();
        std::vector<Sphere> spheres;

        for (int i = 0; i < count; ++i) {
            const libconfig::Setting &sphere = element[i];
            spheres.push_back(parseSphere(sphere));
        }
        return spheres;
    }

    std::vector<IObject> ConfigFileParser::parsePrimitives() const
    {
        std::vector<IObject> objects;
        libconfig::Config cfg;

        cfg.readFile(_filepath.c_str());

        const libconfig::Setting &root = cfg.getRoot();
        const libconfig::Setting &primitives = root["primitives"];
        auto spheres = parseSpheres(primitives["spheres"]);

        return objects;
    }
}
