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
    #include "Point3.hpp"
    #include "IObjectPlugin.hpp"
    #include "Material.hpp"

namespace RayTracer {
    class ParserUtils {
    public:
        static Maths::Vector3I parseVector3I(libconfig::Setting const &element);
        static double parseDouble(
            libconfig::Setting const &element, std::string value);
        static Maths::Vector3D parseVector3D(libconfig::Setting const &element);
        static Maths::Point3D parsePoint3D(libconfig::Setting const &element);
        static Maths::RGB parseColor(libconfig::Setting const &element);
        static Material::Builder getBuilder(
            libconfig::Setting const &element,
            BuilderMap &);
        static Material::Builder parseMaterial(
            libconfig::Setting const &element,
            Material::Builder builder);

    };
} // RayTracer

#endif
