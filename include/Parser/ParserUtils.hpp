/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef PARSERUTILS_HPP
    #define PARSERUTILS_HPP
    #include <libconfig.h++>

    #include "Color.hpp"
    #include "Vector.hpp"
    #include "Point.hpp"
    #include "IObjectPlugin.hpp"
    #include "Material.hpp"
    #include "Quaternion.hpp"
    #include "Texture.hpp"

namespace RayTracer {
    class ParserUtils {
    public:
        static double parseDouble(
            libconfig::Setting const &element, std::string value);

        static bool parseBool(
            libconfig::Setting const &element, std::string value);

        static std::size_t parseSizeT(
            libconfig::Setting const &element, std::string key);

        static Maths::Vector3D parseVector3D(libconfig::Setting const &element);

        static Maths::Quaternion parseQuaternionFromEuler(
            libconfig::Setting const &element);

        static Maths::Point3D parsePoint3D(libconfig::Setting const &element);

        static Maths::Color parseColor(libconfig::Setting const &element);

        static Material::Builder getBuilder(
            libconfig::Setting const &element,
            BuilderMap &);

        static Material::Builder parseMaterial(
            libconfig::Setting const &element,
            Material::Builder builder);
        
        static std::optional<Texture> parseTexture(
            libconfig::Setting const &element, TextureGenerationMap map);
    private:
        static std::optional<Texture> parseTextureName(
            std::string name, TextureGenerationMap maps);
    };
} // RayTracer

#endif
