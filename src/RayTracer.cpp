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
#include <chrono>

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

    void RayTracer::rayWorker(Maths::Vector2U start,
        Maths::Vector2U end, Maths::Vector2U res)
    {
        std::vector<Maths::Color> update;
        update.reserve((end.getX() - start.getX()) * (end.getY() - start.getY()));
        for (std::size_t i = start.getX(); i < end.getX(); ++i) {
            for (std::size_t j = start.getY(); j < end.getY(); ++j) {
                double u = (1.0 / res.getX()) * i;
                double v = (1.0 / res.getY()) * j;
                Ray ray = _camera.ray(u, v);
                update.emplace_back(parseObject(ray, 0));
            }
        }

        size_t idx = 0;
        auto iter = update.begin();
        _mutex.lock();
        for (std::size_t i = start.getX(); i < end.getX(); ++i) {
            for (std::size_t j = start.getY(); j < end.getY(); ++j) {
                _ppm.setPix(i, j, *iter);
                ++iter;
            }
        }
        _mutex.unlock();
    }

    void RayTracer::throwRays() noexcept
    {
        Maths::Vector2U res = _camera.getResolution();
        std::size_t splitx = 8;
        std::size_t splity = 8;

        auto t1 = std::chrono::high_resolution_clock::now();
        auto rw = [this](Maths::Vector2U start,
            Maths::Vector2U end, Maths::Vector2U res)
            { rayWorker(start, end, res); };
        std::size_t stepx = res.getX() / splitx;
        std::size_t stepy = res.getY() / splity;
        for (std::size_t i = 0; i < splitx; ++i) {
            for (std::size_t j = 0; j < splity; ++j) {
                Maths::Vector2U start(stepx * i, stepy * j);
                Maths::Vector2U end(stepx * (i + 1), stepy * (j + 1));
                _workers.emplace_back(rw, start, end, res);
            }
        }
        auto end = _workers.end();
        for (auto worker = _workers.begin(); worker != end; ++worker)
            worker->join();
        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> ms = t2 - t1;
        std::cout << "\nDone in " << ms.count() / 1000 << "s" << std::endl;
    }

    double RayTracer::getSpecular(const Ray &ray,
        const Ray &lihtRay, HitInfo &info)
    {        
        Maths::Vector3D r = ray.direction - info.impactNormal
            * info.impactNormal.dot(ray.direction) * 2;
        auto dot = lihtRay.direction.dot(r.normalized());
        if (dot <= DOUBLE_OFFSET)
            return 0;
        return std::pow(dot, info.material.getShininess());
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
