/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** RayTracer
*/

#include <iostream>
#include <filesystem>
#include <algorithm>
#include <cmath>

#include "RayTracer.hpp"

namespace RayTracer {
    RayTracer::RayTracer(std::queue<std::string> args)
    {
        if (args.empty() || args.front() == HELP_FLAG) {
            showHelp();
            throw HelpException();
        }
        this->loadPrimitivePlugins();
        auto const parser = ConfigFileParser(args.front(),
            this->_primitivesPlugins, this->_presetMaterialBuilders);
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

    Maths::Vector3D RayTracer::hitColor(const Ray &ray,
        const HitInfo &info, std::size_t depth)
    {
        Maths::Vector3D color(0,0,0);
        Ray reflected = info.material.reflect(ray, info);
        Ray diffuse = info.material.diffuse(ray, info);
        auto through = info.material.through(ray, info);

        if (reflected.strength > 0)
            color += parseObject(reflected,  depth + 1);
        if (diffuse.strength > 0)
            color += parseObject(diffuse,  depth + 1);
        if (through.has_value() && through->strength > 0)
            color += parseObject(*through, depth + 1);
        return color;
    }

    std::optional<HitInfo> RayTracer::getHitObject(Ray const &ray)
    {
        std::optional<HitInfo> closerHit = std::nullopt;
    
        for (auto &object : _objects) {
            Ray r = ray;
            auto hit = object->hits(r);
            if (hit.has_value() && (!closerHit.has_value()
                || hit->hitDist < closerHit->hitDist)
                && ray.origin != hit->hitPos)
                closerHit = hit.value();
        }
        return closerHit;
    }

    Maths::Vector3D RayTracer::parseObject(const Ray &ray, std::size_t depth)
    {
        Maths::Vector3D color(0, 0, 0);
    
        if (depth >= MAX_DEPTH || ray.strength <= DOUBLE_OFFSET
            || ray.colorPercentage.length() <= DOUBLE_OFFSET)
            color = ray.colorPercentage;
        else {
            auto closerHit = getHitObject(ray);
            if (!closerHit.has_value() && depth != 0)
                color = ray.colorPercentage;
            if (closerHit.has_value())
                color = hitColor(ray, *closerHit, depth);
        }
        return color;
    }


    void RayTracer::setPixel(
        std::size_t x, std::size_t y, Maths::Vector3U resolution) noexcept
    {
        double u = (1.0 / resolution.x) * x;
        double v = (1.0 / resolution.y) * y;
        Ray ray = _camera.ray(u, v);
        double max = std::numeric_limits<unsigned char>::max();
        auto c = parseObject(ray, 0) * max;
        Maths::RGB color((unsigned char)std::min(c.x, max),
            (unsigned char)std::min(c.y, max),
            (unsigned char)std::min(c.z, max));
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
}
