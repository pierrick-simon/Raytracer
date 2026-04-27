/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Main
*/

#include <iostream>

#include "ConfigFileParser.hpp"
#include "../include/Objects/Lights/Lights.hpp"
#include "Raytracer.hpp"

int main()
{
    try {
        auto const parser = RayTracer::ConfigFileParser(RayTracer::CONFIGFILE_PATH);
        auto cam = parser.parseCamera();
        auto lights = parser.parseLights();
        auto primitives = parser.parsePrimitives();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return RayTracer::EPISUCCESS;
}
