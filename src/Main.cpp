/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Main
*/

#include <deque>
#include <iostream>
#include <queue>

#include "ConfigFileParser.hpp"
#include "RayTracer.hpp"

int main(int ac, char **av)
{
    std::queue<std::string> args(std::deque<std::string>(av + 1, av + ac));
    try {
        auto const parser = RayTracer::ConfigFileParser(RayTracer::CONFIG_FILEPATH);
        auto cam = parser.parseCamera();
        auto lights = parser.parseLights();
        auto primitives = parser.parsePrimitives();
        RayTracer::RayTracer tmp(args);
        tmp.run();
    } catch (RayTracer::RayTracer::HelpException &_) {
        return RayTracer::EPISUCCESS;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return RayTracer::EPIERROR;
    }
    return RayTracer::EPISUCCESS;
}
