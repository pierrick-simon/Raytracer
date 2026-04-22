/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Main
*/

#include <iostream>

#include "ConfigFileParser.hpp"
#include "Lights.hpp"
#include "Raytracer.hpp"

int main()
{
    try {
        RayTracer::ConfigFileParser p("test2.cfg");
        RayTracer::Lights cam = p.parseLights();
        std::cout << cam.getAmbient() << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return RayTracer::EPISUCCESS;
}
