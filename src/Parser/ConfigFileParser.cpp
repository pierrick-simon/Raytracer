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
#include "ParserUtils.hpp"
#include "RayTracer.hpp"

namespace RayTracer {
    ConfigFileParser::ConfigFileParser(std::vector<std::string> &args)
    {
        if (args.empty() || args.front() == HELP_FLAG) {
            RayTracer::showHelp();
            throw RayTracer::HelpException();
        }
        std::fstream file(args.front());
        this->loadPrimitivePlugins();
        this->loadLightPlugins();
        this->loadTexturePlugins();
        if (!args.front().ends_with(FILE_EXT)
            || args.front().size() <= FILE_EXT.size() + 1)
            throw ParserError("Wrong Extenstion.");
        if (!file.is_open())
            throw ParserError("No Such File.");
        _filepath = {std::move(args.front())};
        for (const auto &builder: _presetMaterialBuilders)
            _materialBuilders.insert(builder);
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
        const Maths::Vector2U resolution{resWidth, resHeight};
        const libconfig::Setting &pos = root["camera"]["position"];
        const Maths::Point3D position = ParserUtils::parseVector3D(pos);
        const libconfig::Setting &rot = root["camera"]["rotation"];
        const Maths::Quaternion rotation =
            ParserUtils::parseQuaternionFromEuler(rot);

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
            auto it = std::ranges::find_if(this->_lightsPlugins,
                [&](auto &plugin) {
                    return plugin->getLightsTypeName() == light.getName();
                });

            if (it != this->_lightsPlugins.end()) {
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
                && _materialBuilders.contains(element[i]["type"]))
                builder = _materialBuilders.find(element[i]["type"])->
                    second;
            std::string name = element[i]["name"];
            _materialBuilders.emplace(name,
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
            auto it = std::ranges::find_if(this->_primitivesPlugins,
                [&](auto &plugin) {
                    return plugin->getObjectsTypeName() == primitive.getName();
                });

            if (it != this->_primitivesPlugins.end()) {
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
            object.push_back(
                plugins->parseObject(prim, _materialBuilders));
        }
        return std::move(object);
    }

    void ConfigFileParser::loadPrimitivePlugins()
    {
        std::filesystem::path path(PLUGINS_FOLDER);

        for (auto const &plugin : std::filesystem::directory_iterator(path)) {
            if (!std::filesystem::is_regular_file(plugin))
                continue;
            DLLoader<IObjectPlugin> loader(plugin.path().string());

            if (loader.getType() == LibType::PRIMITIVE) {
                this->_primitivesPlugins.emplace_back(loader.getInstance());
                this->_primitivesPluginsLoaders.emplace_back(std::move(loader));
            }
        }
    }

    void ConfigFileParser::loadLightPlugins()
    {
        std::filesystem::path path(PLUGINS_FOLDER);

        for (auto const &plugin : std::filesystem::directory_iterator(path)) {
            if (!std::filesystem::is_regular_file(plugin))
                continue;
            DLLoader<ILightSourcePlugin> loader(plugin.path().string());

            if (loader.getType() == LibType::LIGHT_SOURCE) {
                this->_lightsPlugins.emplace_back(loader.getInstance());
                this->_lightsPluginsLoaders.emplace_back(std::move(loader));
            }
        }
    }

    void ConfigFileParser::loadTexturePlugins()
    {
        std::filesystem::path path(PLUGINS_FOLDER);

        for (auto const &plugin : std::filesystem::directory_iterator(path)) {
            if (!std::filesystem::is_regular_file(plugin))
                continue;
            DLLoader<ITextureGenerationPlugin> loader(plugin.path().string());

            if (loader.getType() == LibType::TEXTURE_GENERATION) {
                this->_texturesGenerationPlugins.emplace_back(loader.getInstance());
                this->_texturesGenerationPluginsLoaders.emplace_back(std::move(loader));
            }
        }
    }
}
