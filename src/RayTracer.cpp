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
        this->loadLightPlugins();
        auto const parser = ConfigFileParser(args.front(),
            this->_primitivesPlugins, this->_lightsPlugins,
            _presetMaterialBuilders);
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
        Maths::Vector2U res = _camera.getResolution();

        for (std::size_t i = 0; i < res.getX(); ++i) {
            for (std::size_t j = 0; j < res.getY(); ++j) {
                setPixel(i, j, res);
            }
        }
        fprintf(stdout, "\nDone !!\n");
    }

    double RayTracer::getSpecular(const Ray &ray,
        const Ray &lihtRay, HitInfo &info)
    {        
        Maths::Vector3D r = ray.direction - info.impactNormal
            * info.impactNormal.dot(ray.direction) * 2;
        auto dot = lihtRay.direction.dot(r.normalized());
        if (dot <= DOUBLE_OFFSET)
            return 0;
        return std::pow(dot,
            info.material.getShininess());
    }

    Maths::Color RayTracer::parseLight(const Ray &ray, HitInfo &info)
    {
        Maths::Color color(info.material.getColor() * _lights.getAmbient());

        for (auto &light : _lights.getLights()) {
            Ray lightRay;
            lightRay.direction = Maths::Vector3D(
                light->getPosition() - info.hitPos).normalized();
            lightRay.origin = info.hitPos + info.impactNormal * DOUBLE_OFFSET;
            auto diffuse = lightRay.direction.dot(info.impactNormal);
            if (diffuse <= DOUBLE_OFFSET)
                continue;
            if (!getHitObject(lightRay)) {
                Maths::Color lightColor = light->getLightAmount(lightRay);
                color += lightColor * (info.material.getDiffuse() * diffuse
                    * _lights.getDiffuse()
                    + getSpecular(ray, lightRay, info)
                    * info.material.getSpecular()
                );
            }
        }
        return color;
    }

    Maths::Color RayTracer::hitColor(const Ray &ray,
        HitInfo &info, std::size_t depth)
    {
        auto hit = info;
        if (ray.direction.dot(hit.impactNormal) > 0)
            hit.impactNormal *= -1;
        Maths::Color localColor = parseLight(ray, hit);
        Maths::Color reflectColor = Maths::Color::BLACK;
        if (info.material.getSpecular() > DOUBLE_OFFSET) 
            reflectColor =
                parseObject(info.material.getReflectRay(ray, hit), depth + 1);
        Maths::Color refractColor = Maths::Color::BLACK;
        if (1 - info.material.getOpacity() > DOUBLE_OFFSET) {
            auto refract = info.material.getRefractRay(ray, info);
            if (refract)
                refractColor = parseObject(*refract, depth + 1);
        }
        double F = info.material.getFresnel(ray, hit);
        Maths::Color color(localColor
            + reflectColor * F
            + refractColor * (1 - F));

        color = Maths::Color(color * info.material.getOpacity()
                             + refractColor * (1 - info.material.getOpacity()));
        return Maths::Color(color * info.material.getColor());
    }

    std::optional<HitInfo> RayTracer::getHitObject(Ray const &ray)
    {
        std::optional<HitInfo> closerHit = std::nullopt;
    
        for (auto &object : _objects) {
            auto hit = object->hits(ray);
            if (hit.has_value() && (!closerHit.has_value()
                || hit->hitDist < closerHit->hitDist)
                && ray.origin != hit->hitPos && hit->hitDist > DOUBLE_OFFSET)
                closerHit = hit.value();
        }
        return closerHit;
    }

    Maths::Color RayTracer::parseObject(const Ray &ray, std::size_t depth)
    {
        Maths::Color color = Maths::Color::BLACK;
    
        if (depth < MAX_DEPTH) {
            auto closerHit = getHitObject(ray);
            if (closerHit)
                color = hitColor(ray, *closerHit, depth);
        }
        return color;
    }


    void RayTracer::setPixel(
        std::size_t x, std::size_t y, Maths::Vector2U resolution) noexcept
    {
        double u = (1.0 / resolution.getX()) * x;
        double v = (1.0 / resolution.getY()) * y;
        Ray ray = _camera.ray(u, v);
        Maths::Color c(parseObject(ray, 0));
        loadingBar(x * _camera.getResolution().getY() + y);
        _ppm.setPix(x, y, c);
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

    void RayTracer::loadingBar(std::size_t pix)
    {
        double percentage = static_cast<double>(pix)
            / static_cast<double>(_camera.getNbPixel());
        
        if (percentage - 0.015 > _loadingPercentage)
            _loadingPercentage += 0.015;
        else
            return;
        if (_loadingPercentage < 1.0 / 3.0)
            fprintf(stdout, "\e[0;31m");
        else if (_loadingPercentage < 2.0 / 3.0)
            fprintf(stdout, "\e[0;33m");
        else
            fprintf(stdout, "\e[0;32m");
        fprintf(stdout, "#\e[0;37m");
        fflush(stdout);
    }
}
