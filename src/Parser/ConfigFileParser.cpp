/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#include <utility>
#include <fstream>

#include "ConfigFileParser.hpp"

#include <algorithm>
#include <filesystem>
#include <ranges>

#include "DirectionalLight.hpp"
#include "ParserUtils.hpp"
#include "PointLight.hpp"

namespace RayTracer {
    ConfigFileParser::ConfigFileParser(std::string s, std::vector<std::unique_ptr<IObjectPlugin>> &primitivePlugins) :
        _primitivePlugins(primitivePlugins)
    {
        std::fstream file(s);

        if (!s.ends_with(FILE_EXT)
            || s.size() <= FILE_EXT.size() + 1)
            throw ParserError("Wrong Extenstion.");
        if (!file.is_open())
            throw ParserError("No Such File.");
        _filepath = {std::move(s)};
    }

    ConfigFileParser::ParserError::ParserError(std::string s):
        _err(std::move(s))
    {
    }

    const char *ConfigFileParser::ParserError::what() const noexcept
    {
        return _err.c_str();
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
        const Maths::Point3D position = ParserUtils::parseVector3D(pos);
        const libconfig::Setting &rot = root["camera"]["rotation"];
        const Maths::Vector3D rotation = TORAD(ParserUtils::parseVector3D(rot));

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

    std::vector<std::unique_ptr<IObject>>
    ConfigFileParser::parsePrimitives() const
    {
        libconfig::Config cfg;
        std::vector<std::unique_ptr<IObject>> objects = {};

        cfg.readFile(_filepath.c_str());

        const libconfig::Setting &root = cfg.getRoot()["primitives"];
        for (const auto &primitive: root) {
            auto it = std::ranges::find_if(this->_primitivePlugins, [&](auto &plugin) {
                return plugin->getObjectsTypeName() == primitive.getName();
            });

            if (it != this->_primitivePlugins.end()) {
                auto pluginObjects = it->get()->parseObjects(primitive);
                std::ranges::move(pluginObjects, std::back_inserter(objects));
            }
        }
        return objects;
    }
}
