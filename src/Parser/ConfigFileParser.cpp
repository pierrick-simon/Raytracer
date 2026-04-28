/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#include <libconfig.h++>
#include <utility>
#include <iostream>
#include <memory>
#include <fstream>

#include "ConfigFileParser.hpp"
#include "Camera.hpp"
#include "DirectionalLight.hpp"
#include "Lights.hpp"
#include "PointLight.hpp"
#include "Shpere.hpp"

namespace RayTracer {
    ConfigFileParser::ConfigFileParser(std::string s)
    {
        std::fstream file(s);
    
        if (!s.ends_with(FILE_EXT)
            || s.size() <= FILE_EXT.size() + 1)
            throw ParserError("Wrong Extenstion.");
        if (!file.is_open())
            throw ParserError("No Such File.");
        _filepath = {std::move(s)};
    }

    const char *ConfigFileParser::ParserError::what() const noexcept
    {
        return _err.c_str();
    }

    Maths::Vector3I ConfigFileParser::parseVector3I(
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
        const Maths::Vector3U resolution{resWidth, resHeight, 0};
        const libconfig::Setting &pos = root["camera"]["position"];
        const Maths::Vector3I position = parseVector3I(pos);
        const libconfig::Setting &rot = root["camera"]["rotation"];
        const Maths::Vector3I rotation = parseVector3I(rot);

        return Camera{resolution, position, rotation, fov};
    }

    std::unique_ptr<ILightSource> ConfigFileParser::parseDirectionalLight(
    libconfig::Setting const &element)
    {
        int x = 0;
        int y = 0;
        int z = 0;

        for (int i = 0; i < element.getLength(); ++i) {
            element[i].lookupValue("x", x);
            element[i].lookupValue("y", y);
            element[i].lookupValue("z", z);
        }
        return std::make_unique<DirectionalLight>(x, y, z);
    }

    std::unique_ptr<ILightSource> ConfigFileParser::parsePointLight(
    libconfig::Setting const &element)
    {
        int x = 0;
        int y = 0;
        int z = 0;

        for (int i = 0; i < element.getLength(); ++i) {
            element[i].lookupValue("x", x);
            element[i].lookupValue("y", y);
            element[i].lookupValue("z", z);
        }
        return std::make_unique<PointLight>(x, y, z);
    }

    LightConfig ConfigFileParser::parseLights() const
    {
        libconfig::Config cfg;

        cfg.readFile(_filepath.c_str());
        const libconfig::Setting &root = cfg.getRoot()["lights"];

        double ambient = 0.0;
        double diffuse = 0.0;
        std::vector<std::unique_ptr<ILightSource>> lights;
        root.lookupValue("ambient", ambient);
        root.lookupValue("diffuse", diffuse);
        lights.push_back(parsePointLight(root["point"]));
        lights.push_back(parseDirectionalLight(root["directional"]));
        return LightConfig{ambient, diffuse, std::move(lights)};
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

    std::unique_ptr<IObject> ConfigFileParser::parseSphere(
        libconfig::Setting const &element)
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
        return std::make_unique<Sphere>(Sphere{x, y, z, r,color});
    }

    std::vector<std::unique_ptr<IObject>> ConfigFileParser::parseSpheres(
        libconfig::Setting const &element)
    {
        int count = element.getLength();
        std::vector<std::unique_ptr<IObject>> spheres;

        for (int i = 0; i < count; ++i) {
            const libconfig::Setting &sphere = element[i];
            spheres.push_back(parseSphere(sphere));
        }
        return spheres;
    }

    std::vector<std::unique_ptr<IObject>> ConfigFileParser::parsePrimitives() const
    {
        libconfig::Config cfg;

        cfg.readFile(_filepath.c_str());

        const libconfig::Setting &root = cfg.getRoot()["primitives"];
        auto objects = parseSpheres(root["spheres"]);
        return objects;
    }
}
