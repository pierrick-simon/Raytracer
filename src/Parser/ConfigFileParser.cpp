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
#include <ranges>

#include "ConfigFileParser.hpp"
#include "ParserUtils.hpp"

namespace RayTracer {
    ConfigFileParser::ConfigFileParser(std::string filepath, std::vector<std::unique_ptr<IObjectPlugin>> &primitivePlugins,
        std::vector<std::unique_ptr<ILightSourcePlugin>> &lightPlugins,
        BuilderMap &materials) :
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
        for (const auto& builder: materials)
            _presetMaterialBuilders.insert(builder);
        libconfig::Config cfg;
        cfg.readFile(_filepath.c_str());
        const libconfig::Setting &root = cfg.getRoot();
        if (root.exists("materials"))
            parseMaterials(root["materials"]);
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

    LightConfig ConfigFileParser::parseLights() const
    {
        libconfig::Config cfg;

        cfg.readFile(_filepath.c_str());
        const libconfig::Setting &root = cfg.getRoot()["lights"];

        double ambient = ParserUtils::parseDouble(root, "ambient");
        double diffuse = ParserUtils::parseDouble(root, "diffuse");
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

    void ConfigFileParser::parseMaterials(libconfig::Setting const &element)
    {
        for (int i = 0; i < element.getLength(); ++i) {
            Material::Builder builder{};
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
            auto it = std::ranges::find_if(this->_primitivePlugins,
                [&](auto &plugin) {
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

    std::vector<std::unique_ptr<ILightSource>>
    ConfigFileParser::parseSimilarLight(libconfig::Setting const &lightsSetting,
        std::unique_ptr<ILightSourcePlugin> const &plugin)
    {
        std::vector<std::unique_ptr<ILightSource>> lights;
        for (const auto &light: lightsSetting)
            lights.emplace_back(plugin->parseLight(light));
        return std::move(lights);
    }

    std::vector<std::unique_ptr<IObject>> ConfigFileParser::
        parseSimilarPrimitives(libconfig::Setting const &element,
            std::unique_ptr<IObjectPlugin> const &plugins) const
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
