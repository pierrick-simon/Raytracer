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
#include "ArgsParser.hpp"

namespace RayTracer {
    RayTracer::RayTracer(std::vector<std::string> args)
        : _configFileParser(args)
    {
        _camera = _configFileParser.parseCamera();
        _lights = _configFileParser.parseLights();
        _objects = _configFileParser.parsePrimitives();
        initVars(args);
        parseOptionalArgs(args);
    }

    void RayTracer::run() noexcept
    {
        if (_display.has_value()) {
            _loadingPercentage = 0.0;
            _workers.clear();
            throwDisplay();
        } else
            throwRays(1, _maxDepth);
        _ppm.save(_name);
    }

    void RayTracer::cancelAndJoin(std::thread &thread)
    {
        _cancelRender = true;
        thread.join();
        _cancelRender = false;
    }

    std::thread RayTracer::startRender(std::size_t scale, std::size_t maxDepth)
    {
        _renderDone = false;
        _loadingPercentage = 0.0;
        _workers.clear();
        return std::thread([this, scale, maxDepth]() {
            throwRays(scale, maxDepth);
            _renderDone = true;
        });
    }

    void RayTracer::throwDisplay()
    {
        bool lowQuality = true;
        bool sleep = false;
        auto last = Clock::now();
        auto thread = startRender(LOW_QUALITY_SCALE, LOW_QUALITY_DEPTH);

        while (true) {
            auto event = _display->get()->getEvent();
            _display->get()->draw();
            auto action = handleEvent(event, last, sleep, lowQuality, thread);
            if (action == EXIT)
                break;
            else if (action == SKIP)
                continue;
            if (lowQuality && Clock::now() - last >= SLEEP) {
                cancelAndJoin(thread);
                lowQuality = false;
                thread = startRender(1, _maxDepth);
            }
            if (!lowQuality && _renderDone && !sleep) {
                thread.join();
                sleep = true;
            }
        }
        if (!sleep)
            cancelAndJoin(thread);
    }

    void RayTracer::makeWorker(Maths::Vector2U resolution, std::size_t scale,
        std::size_t maxDepth, double stepX, double stepY)
    {
        for (std::size_t i = 0; i < (std::size_t)_nbScreenSplit; ++i) {
            for (std::size_t j = 0; j < (std::size_t)_nbScreenSplit; ++j) {
                Maths::Vector2U start(
                    static_cast<unsigned>(std::round(stepX * i)),
                    static_cast<unsigned>(std::round(stepY * j)));
                Maths::Vector2U end(
                    static_cast<unsigned>(std::round(stepX * (i + 1))),
                    static_cast<unsigned>(std::round(stepY * (j + 1))));
                _workers.emplace_back(
                    [this, start, end, resolution, scale, maxDepth]() {
                        rayWorker(start, end, resolution, scale,
                            maxDepth);
                    });
            }
            if (_cancelRender)
                break;
        }
    }

    void RayTracer::throwRays(std::size_t scale, std::size_t maxDepth) noexcept
    {
        Maths::Vector2U fullRes = _camera.getResolution();

        auto t1 = std::chrono::high_resolution_clock::now();
        std::size_t width = (fullRes.getX() + scale - 1) / scale;
        std::size_t height = (fullRes.getY() + scale - 1) / scale;
        Maths::Vector2U resolution(width, height);
        double stepX = width / static_cast<double>(_nbScreenSplit);
        double stepY = height / static_cast<double>(_nbScreenSplit);

        if (!_display)
            updateLoadingBar();
        makeWorker(resolution, scale, maxDepth, stepX, stepY);
        for (auto &w : _workers)
            w.join();
        if (!_cancelRender && !_display) {
            auto t2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> ms = t2 - t1;
            std::cout << "\nDone in " << ms.count() / 1000 << "s" << std::endl;
        }
    }

    void RayTracer::updateRays(Maths::Vector2U start,
        Maths::Vector2U end, std::vector<Maths::Color> update)
    {
        auto iter = update.begin();
        _mutex.lock();
        for (std::size_t i = start.getX(); i < end.getX(); ++i) {
            for (std::size_t j = start.getY(); j < end.getY(); ++j) {
                _ppm.setPix(i, j, *iter);
                ++iter;
            }
        }
        if (!_display) {
            _loadingPercentage += 1.0 /
                (std::pow(static_cast<double>(_nbScreenSplit), 2));
            updateLoadingBar();
        }
        _mutex.unlock();
    }

    void RayTracer::rayWorkerBatch(std::size_t scale, std::size_t x, std::size_t y,
            std::vector<Maths::Color> &update, Maths::Color color)
    {
        auto fullRes = _camera.getResolution();
        if (scale == 1) {
            updateDisplayColor(x, y, color.to8Bit());
            update.push_back(color);
            return;
        }
        std::size_t px = x * scale;
        std::size_t py = y * scale;
        for (std::size_t i = 0; i < (std::size_t)scale; ++i) {
            for (std::size_t j = 0; j < (std::size_t)scale; ++j) {
                updateDisplayColor(px + i, py + j, color.to8Bit());
                update.push_back(color);
            }
        }
    }

    void RayTracer::rayWorker(Maths::Vector2U start, Maths::Vector2U end,
        Maths::Vector2U res, std::size_t scale, std::size_t maxDepth)
    {
        std::vector<Maths::Color> update;
        update.reserve((end.getX() - start.getX()) * (end.getY() - start.getY()));
        for (std::size_t i = start.getX(); i < end.getX(); ++i) {
            if (_cancelRender.load(std::memory_order_relaxed))
                return;
            for (std::size_t j = start.getY(); j < end.getY(); ++j) {
                Maths::Vector2D v((1.0 / res.getX()) * i, (1.0 / res.getY()) * j);
                Ray ray = _camera.ray(v);
                auto color = parseObject(ray, 0, maxDepth);
                rayWorkerBatch(scale, i, j, update, color);
            }
        }
        updateRays(start, end, update);
    }

    double RayTracer::getSpecular(const Ray &ray,
        const Ray &lightRay, HitInfo &info)
    {
        Maths::Vector3D r = ray.direction
            - info.impactNormal
            * info.impactNormal.dot(ray.direction) * 2;
        auto dot = lightRay.direction.dot(r.normalized());
        if (dot <= DOUBLE_OFFSET)
            return 0;
        return std::pow(dot, info.material.getShininess());
    }

    Maths::Color RayTracer::parseLight(const Ray &ray, HitInfo &info)
    {
        Maths::Color color(info.material.getColor(info) * _lights.getAmbient());

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
        HitInfo &info, std::size_t depth, int maxDepth)
    {
        auto hit = info;
        if (ray.direction.dot(hit.impactNormal) > 0)
            hit.impactNormal *= -1;
        Maths::Color localColor = parseLight(ray, hit);
        Maths::Color reflectColor = Maths::Color::BLACK;
        if (info.material.getSpecular() > DOUBLE_OFFSET)
            reflectColor = parseObject(
                info.material.getReflectRay(ray, hit), depth + 1, maxDepth);
        Maths::Color refractColor = Maths::Color::BLACK;
        if (1 - info.material.getOpacity() > DOUBLE_OFFSET) {
            auto refract = info.material.getRefractRay(ray, info);
            if (refract)
                refractColor = parseObject(*refract, depth + 1, maxDepth);
        }
        double F = info.material.getFresnel(ray, hit);
        Maths::Color color(localColor
            + reflectColor * F
            + refractColor * (1 - F));

        color = Maths::Color(color * info.material.getOpacity()
            + refractColor * (1 - info.material.getOpacity()));
        return Maths::Color(color * info.material.getColor(info));
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

    Maths::Color RayTracer::parseObject(const Ray &ray,
        std::size_t depth, int maxDepth)
    {
        if (depth >= static_cast<std::size_t>(maxDepth))
            return Maths::Color::BLACK;
        auto closerHit = getHitObject(ray);
        if (closerHit)
            return hitColor(ray, *closerHit, depth, maxDepth);
        return Maths::Color::BLACK;
    }

    void RayTracer::updateDisplayColor(std::size_t i, std::size_t j,
        Maths::Color8bit color)
    {
        if (_display)
            _display->get()->setPix(i, j, color);
    }

    void RayTracer::updateLoadingBar()
    {
        std::cout << "[";
        int p = static_cast<int>(_loadingPercentage * 100);
        for (int i = 0; i < 100; ++i) {
            if (i < p)
                std::cout << "=";
            else if (i == p)
                std::cout << ">";
            else
                std::cout << " ";
        }
        std::cout << "] " << p << " %\r" << std::flush;
    }


    bool RayTracer::moveCamera(Action action)
    {
        auto pos = _camera.getPosition();

        if (action == Action::Z)
            pos += _camera.forward();
        if (action == Action::S)
            pos -= _camera.forward();
        if (action == Action::D)
            pos += _camera.right();
        if (action == Action::Q)
            pos -= _camera.right();
        if (action == Action::X)
            pos += _camera.up();
        if (action == Action::W)
            pos -= _camera.up();
        bool changed = (pos != _camera.getPosition());
        _camera.setPosition(pos);
        return changed;
    }

    bool RayTracer::rotateCamera(Action action)
    {
        auto rotation = _camera.getRotation();

        if (action == Action::Down)
            rotation *= Maths::Quaternion::fromEulerDegrees(0,  1, 0);
        if (action == Action::Up)
            rotation *= Maths::Quaternion::fromEulerDegrees(0, -1, 0);
        if (action == Action::A)
            rotation *= Maths::Quaternion::fromEulerDegrees( 1, 0, 0);
        if (action == Action::E)
            rotation *= Maths::Quaternion::fromEulerDegrees(-1, 0, 0);
        if (action == Action::Right)
            rotation *= Maths::Quaternion::fromEulerDegrees(0, 0,  1);
        if (action == Action::Left)
            rotation *= Maths::Quaternion::fromEulerDegrees(0, 0, -1);
        bool changed = (rotation != _camera.getRotation());
        _camera.setRotation(rotation.normalize());
        _camera.updateCamera();
        return changed;
    }

    void RayTracer::updateCamera(Clock::time_point &clock,
        bool &sleep, bool &lowQuality, std::thread &thread)
    {
        clock = Clock::now();
        if (!sleep)
            cancelAndJoin(thread);
        sleep = false;
        lowQuality = true;
        thread = startRender(LOW_QUALITY_SCALE, LOW_QUALITY_DEPTH);
    }

    int RayTracer::handleEvent(Event event, Clock::time_point &clock, bool &sleep,
        bool &lowQuality, std::thread &thread)
    {
        auto actions = event.first;
        auto update = false;
        int value = EPISUCCESS;

        for (auto action: actions) {
            if (action == Action::Close || action == Action::Escape) {
                value = EXIT;
                break;
            }
            auto move = moveCamera(action);
            auto rotate = rotateCamera(action);
            update = update || move || rotate;
        }
        if (update && value == EPISUCCESS) {
            updateCamera(clock, sleep, lowQuality, thread);
            value = SKIP;
        }
        return value;
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

    void RayTracer::parseOptionalArgs(std::vector<std::string> args)
    {
        try {
            auto libName = ArgsParser::getArg<std::string>(args, "--display");
            if (libName.has_value())
                _displayLoader.emplace(libName.value());
            if (_displayLoader.has_value() && _displayLoader->getType() != LibType::GRAPHICS)
                    throw IncorrectLibTypeException();
            auto sd = ArgsParser::getArg<int>(args, "--screenDivision");
            if (sd.has_value())
                _nbScreenSplit = sd.value();
            auto md = ArgsParser::getArg<int>(args, "--maxDepth");
            if (md.has_value())
                _maxDepth = md.value();
            if (!args.empty() || _nbScreenSplit <= 0 || _maxDepth <= 0)
                throw ArgsParserError();
            if (_displayLoader) {
                _display = _displayLoader->getInstance();
                _display->get()->setSceneSize(_camera.getResolution().getX(),
                    _camera.getResolution().getY());
            }
        } catch (ArgsParserError) {
            showHelp();
            throw HelpException();
        }
    }

    void RayTracer::initVars(
        std::reference_wrapper<std::vector<std::string>> args)
    {
        _ppm = PortablePixMap(_camera.getResolution());
        std::filesystem::path path(args.get().front());
        _name = path.filename();
        size_t pos = _name.find(ARG_EXT);
        if (pos != std::string::npos)
            _name.replace(pos, _name.length() - pos, "\0");
        args.get().erase(args.get().begin());
    }
} // namespace RayTracer