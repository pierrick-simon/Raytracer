/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Main
*/

#include <deque>
#include <iostream>
#include <queue>

#include "RayTracer.hpp"

int main(int ac, char **av)
{
    std::vector<std::string> args;
    for (++av;*av != NULL; ++av)
        args.emplace_back(*av);
    try {
        RayTracer::RayTracer tmp(args);
        tmp.run();
    } catch (RayTracer::RayTracer::HelpException &_) {
        return RayTracer::EPISUCCESS;
    } catch (RayTracer::ConfigFileParser::ParserError &e) {
        std::cout << e.what() << std::endl;
        return RayTracer::EPIERROR;
    }
    return RayTracer::EPISUCCESS;
}
