/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#include <utility>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <ranges>

#include "ConfigFileParser.hpp"
#include "DirectionalLight.hpp"
#include "ParserUtils.hpp"
#include "PointLight.hpp"

namespace RayTracer {
    ConfigFileParser::ConfigFileParser(std::string s,
        std::vector<std::unique_ptr<IObjectPlugin>> &primitivePlugins,
        BuilderMap &materials
    ) :
        _primitivePlugins(primitivePlugins)
    {
        std::fstream file(s);

        if (!s.ends_with(FILE_EXT)
            || s.size() <= FILE_EXT.size() + 1)
            throw ParserError("Wrong Extenstion.");
        if (!file.is_open())
            throw ParserError("No Such File.");
        _filepath = {std::move(s)};
        for (auto builder: materials)
            _presetMaterialBuilders.insert(builder);
        libconfig::Config cfg;
        cfg.readFile(_filepath.c_str());
        const libconfig::Setting &root = cfg.getRoot();
        if (root.exists("materials"))
            parseMaterials(root["materials"]);
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
        const double fov =
            ParserUtils::parseDouble(root["camera"], "fieldOfView");

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

        double ambient = ParserUtils::parseDouble(root, "ambient");
        double diffuse = ParserUtils::parseDouble(root, "diffuse");
        std::vector<std::unique_ptr<ILightSource>> lights;
        lights.push_back(parsePointLight(root["point"]));
        lights.push_back(parseDirectionalLight(root["directional"]));
        return LightConfig{ambient, diffuse, std::move(lights)};
    }

    void ConfigFileParser::parseMaterials(libconfig::Setting const &element)
    {
        for (int i = 0; i < element.getLength(); ++i) {
            Material::Builder builder;
            if (element[i].exists("type")
                && _presetMaterialBuilders.find(element[i]["type"])
                    != _presetMaterialBuilders.end())
                builder = _presetMaterialBuilders.find(element[i]["type"])->second;
            std::string name = element[i]["name"];
            _presetMaterialBuilders.emplace(name,
                ParserUtils::parseMaterial(element[i], builder));
        }
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
                auto pluginObjects = parseSimilarPrimitives(
                    primitive, *it);
                std::ranges::move(pluginObjects, std::back_inserter(objects));
            }
        }
        return objects;
    }

    std::vector<std::unique_ptr<IObject>> ConfigFileParser::
        parseSimilarPrimitives(libconfig::Setting const &element,
            std::unique_ptr<RayTracer::IObjectPlugin> const &plugins) const
    {
        int count = element.getLength();
        std::vector<std::unique_ptr<IObject>> object;

        for (int i = 0; i < count; ++i) {
            const libconfig::Setting &prim = element[i];
            object.push_back(plugins->parseObject(prim, _presetMaterialBuilders));
        }
        return std::move(object);
    }
}
