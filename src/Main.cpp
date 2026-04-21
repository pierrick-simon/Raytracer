/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Main
*/

#include "RayTracer.hpp"

int main(int ac, char **av)
{
    std::queue<std::string> args(std::deque<std::string>(av + 1, av + ac));
    try {
        RayTracer::RayTracer tmp(args);
        tmp.run();
    } catch (RayTracer::RayTracer::HelpException &_) {
        return RayTracer::EPISUCCESS;
    }
    return RayTracer::EPISUCCESS;
}
