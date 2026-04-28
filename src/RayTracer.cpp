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
        try {
            auto const parser = ConfigFileParser(args.front());
            _camera = parser.parseCamera();
            _lights = parser.parseLights();
            _objects = parser.parsePrimitives();
        } catch (ConfigFileParser::ParserError &e) {
            throw e;
        };
        initVars(args);
        try {
            parseOptionalArgs(args);
        } catch (HelpException &e) {
            throw e;
        } catch (IncorrectLibTypeException &e) {
            throw e;
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

    void RayTracer::parseOptionalArgs(std::queue<std::string> args)
    {
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

    void RayTracer::run()
    {
        if (_display.has_value())
            runDisplay();
        _ppm.save(_name);
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
}
