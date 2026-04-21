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
        RayTracer::Camera cam = p.parseCamera();
        std::cout << cam.getFov() << std::endl;
        std::cout << cam.getPosition().x << " " << cam.getPosition().y << " " << cam.getPosition().z << std::endl;
        std::cout << cam.getResolution().x << " " << cam.getResolution().y << " " << cam.getResolution().z << std::endl;
        std::cout << cam.getRotation().x << " " << cam.getRotation().y << " " << cam.getRotation().z << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return RayTracer::EPISUCCESS;
}
