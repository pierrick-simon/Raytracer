/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ArgParser
*/

#include "ArgsParser.hpp"

namespace RayTracer {
    bool ArgsParser::isArg(
        std::reference_wrapper<std::vector<std::string>> args, std::string flag)
    {
        bool ret = false;
        for (auto arg = args.get().begin(); arg != args.get().end(); ++arg) {
            if (*arg == flag) {
                args.get().erase(arg);
                ret = true;
                break;
            }
        }
        return ret;
    }
}
