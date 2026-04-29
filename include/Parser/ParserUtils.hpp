/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef PARSERUTILS_HPP
    #define PARSERUTILS_HPP
    #include <libconfig.h++>

    #include "Vector3.hpp"

namespace RayTracer {
    class ParserUtils {
    public:
        static Maths::Vector3I parseVector3I(libconfig::Setting const &element);

        static Maths::RGB parseColor(libconfig::Setting const &element);

    };
} // RayTracer

#endif
