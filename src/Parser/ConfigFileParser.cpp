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

namespace RayTracer {
    ConfigFileParser::ConfigFileParser(std::string filepath,
        std::vector<std::unique_ptr<IObjectPlugin>> &primitivePlugins,
        std::vector<std::unique_ptr<ILightSourcePlugin>> &lightPlugins) :
        _primitivePlugins(primitivePlugins),
        _lightPlugins(lightPlugins)
    {
        std::fstream file(filepath);

        if (!filepath.ends_with(FILE_EXT)
            || filepath.size() <= FILE_EXT.size() + 1)
            throw ParserError("Wrong Extenstion.");
        if (!file.is_open())
            throw ParserError("No Such File.");
        _filepath = {std::move(filepath)};
    }

    ConfigFileParser::ParserError::ParserError(std::string s) :
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
        const Maths::Vector3D rotation = ParserUtils::parseVector3D(rot);

        return Camera{resolution, position, rotation, fov};
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

        for (const auto &light: root) {
            auto it = std::ranges::find_if(this->_lightPlugins,
                [&](auto &plugin) {
                    return plugin->getLightsTypeName() == light.getName();
                });

            if (it != this->_lightPlugins.end()) {
                auto pluginObjects = parseSimilarLight(
                    light, *it);
                std::ranges::move(pluginObjects, std::back_inserter(lights));
            }
        }

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
            auto it = std::ranges::find_if(this->_primitivePlugins,
                [&](auto &plugin) {
                    return plugin->getObjectsTypeName() == primitive.getName();
                });

            if (it != this->_primitivePlugins.end()) {
                auto pluginObjects = it->get()->parseObjects(primitive);
                std::ranges::move(pluginObjects, std::back_inserter(objects));
            }
        }
        return objects;
    }

    std::vector<std::unique_ptr<ILightSource>>
    ConfigFileParser::parseSimilarLight(libconfig::Setting const &lightsSetting,
        std::unique_ptr<ILightSourcePlugin> const &plugin)
    {
        std::vector<std::unique_ptr<ILightSource>> lights;
        for (const auto &light: lightsSetting)
            lights.emplace_back(plugin->parseLight(light));
        return std::move(lights);
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
}
