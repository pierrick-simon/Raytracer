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
    RayTracer::RayTracer::RayTracer(std::queue<std::string> args)
    {
        if (args.empty() || args.front() == HELP_FLAG) {
            showHelp();
            throw HelpException();
        }
        _ppm = PortablePixMap(args.front());
        std::filesystem::path path(args.front());
        _name = path.filename();
        size_t pos = _name.find(ARG_EXT);
        if (pos != std::string::npos)
            _name.replace(pos, _name.length() - pos, "\0");
        args.pop();
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
