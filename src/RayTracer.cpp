/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** RayTracer
*/

#include <iostream>
#include <filesystem>

#include "RayTracer.hpp"

namespace RayTracer {
    RayTracer::RayTracer(std::queue<std::string> args)
    {
        if (args.empty() || args.front() == HELP_FLAG) {
            showHelp();
            throw HelpException();
        }
        this->loadPrimitivePlugins();
        this->loadLightPlugins();
        auto const parser = ConfigFileParser(args.front(),
            this->_primitivesPlugins, this->_lightsPlugins, this->_presetMaterialBuilders);
        _camera = parser.parseCamera();
        _lights = parser.parseLights();
        _objects = parser.parsePrimitives();
        initVars(args);
        parseOptionalArgs(args);
    }

    void RayTracer::run() noexcept
    {
        throwRays();
        if (_display.has_value())
            runDisplay();
        _ppm.save(_name);
    }

    void RayTracer::throwRays() noexcept
    {
        Maths::Vector3U res = _camera.getResolution();

        for (std::size_t i = 0; i < res.x; ++i) {
            for (std::size_t j = 0; j < res.y; ++j) {
                setPixel(i, j, res);
            }
        }
    }

    void RayTracer::setPixel(
        std::size_t x, std::size_t y, Maths::Vector3U resolution) noexcept
    {
        double u = (1.0 / resolution.x) * x;
        double v = (1.0 / resolution.y) * y;
        Ray closerRay{};
        HitInfo closerHit{.hitDist = -1.0};
        for (auto &object: _objects) {
            Ray r = _camera.ray(u, v);
            auto hit = object->hits(r);
            if (hit.has_value() && (closerHit.hitDist == -1.0
                || hit.value().hitDist < closerHit.hitDist)) {
                closerRay = r;
                closerHit = hit.value();
            }
        }
        closerHit.material.scatter(closerRay, closerHit);
        Maths::Vector3D tmp = closerRay.colorPercentage
            * std::numeric_limits<unsigned char>::max();
        Maths::RGB color = {(unsigned char)tmp.x,
            (unsigned char)tmp.y,
            (unsigned char)tmp.z};
        _ppm.setPix(x, y, color);
    }

    void RayTracer::showHelp()
    {
        std::ifstream file({std::string(HELP)});

        if (file.is_open())
            std::cout << file.rdbuf();
    }

    const char *RayTracer::IncorrectLibTypeException::what() const noexcept
    {
        return "Tried to load an incorrect lib type.";
    }

    void RayTracer::runDisplay()
    {
        auto display = _display.value().getInstance();

        while (display->getEvent().first != Action::Close)
            display->draw(_ppm);
    }

    void RayTracer::parseOptionalArgs(std::queue<std::string> args)
    {
        if (args.empty())
            return;
        if (!args.empty() && args.front() == DISPLAY_FLAG && args.size() == 2) {
            args.pop();
            _display.emplace(args.front());
            if (_display->getType() != LibType::GRAPHICS)
                throw IncorrectLibTypeException();
        } else {
            showHelp();
            throw HelpException();
        }
    }

    void RayTracer::initVars(
        std::reference_wrapper<std::queue<std::string>> args)
    {
        _ppm = _camera.getResolution();
        std::filesystem::path path(args.get().front());
        _name = path.filename();
        size_t pos = _name.find(ARG_EXT);
        if (pos != std::string::npos)
            _name.replace(pos, _name.length() - pos, "\0");
        args.get().pop();
    }

    void RayTracer::loadPrimitivePlugins()
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

    void RayTracer::loadLightPlugins()
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
}
