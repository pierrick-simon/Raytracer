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
        auto const parser = ConfigFileParser(args.front(), this->_primitivesPlugins);
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

        for (auto &object: _objects) {
            double u = (1.0 / res.x) * 25;
            double v = (1.0 / res.y) * 25;
            Ray r = _camera.ray(u, v);
            if (object->hits(r))
                std::cout << "hit" << std::endl;
            else
                std::cout << "no hit" << std::endl;
            // for (std::size_t i = 0; i <= res.x; ++i) {
            //     for (std::size_t j = 0; j <= res.y; ++j) {
            //         double u = (1.0 / res.x) * i;
            //         double v = (1.0 / res.y) * j;
            //         Ray r = _camera.ray(u, v);
            //         if (object->hits(r))
            //             _ppm.setPix(i, j, r.color);
            //     }
            // }
        }
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
}
