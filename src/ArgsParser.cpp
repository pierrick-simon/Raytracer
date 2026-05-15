/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ArgParser
*/

#include "ArgsParser.hpp"

namespace RayTracer {
    bool isArg(
        std::reference_wrapper<std::vector<std::string>> args, std::string flag)
    {
        for (auto arg = args.get().begin(); arg != args.get().end(); ++arg) {
            if (*arg == flag) {
                args.get().erase(arg);
                return true;
            }
        }
        return false;
    }
}
