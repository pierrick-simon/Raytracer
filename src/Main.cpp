/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Main
*/

#include <iostream>

#include "ConfigFileParser.hpp"
#include "Raytracer.hpp"

int main()
{
    try {
        RayTracer::ConfigFileParser p("test2.cfg");
        auto cam = p.parsePrimitives();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return RayTracer::EPISUCCESS;
}
