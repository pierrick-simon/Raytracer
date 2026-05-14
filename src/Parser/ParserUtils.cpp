/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#include <iostream>
#include "ParserUtils.hpp"

namespace RayTracer {

    double ParserUtils::parseDouble(
        libconfig::Setting const &element, std::string value)
    {
        double nb = 0;
        if (!element.lookupValue(value, nb)) {
            int tmp = 0;
            if (!element.lookupValue(value, tmp))
                throw libconfig::SettingTypeException(element);
            nb = static_cast<double>(tmp);
        }
        return nb;
    }

    bool ParserUtils::parseBool(
        libconfig::Setting const &element, std::string key)
    {
        bool value = false;

        if (!element.lookupValue(key, value))
            throw libconfig::SettingTypeException(element);
        return value;
    }

    std::size_t ParserUtils::parseSizeT(
            libconfig::Setting const &element, std::string key)
    {
        int value = 0;

        if (!element.lookupValue(key, value) || value < 0) {
            throw libconfig::SettingTypeException(element);
        }
        return value;
    }

    Maths::Vector3D ParserUtils::parseVector3D(
        libconfig::Setting const &element)
    {
        double x = parseDouble(element, "x");
        double y = parseDouble(element, "y");
        double z = parseDouble(element, "z");

        return Maths::Vector3D{x, y, z};
    }

    Maths::Quaternion ParserUtils::parseQuaternionFromEuler(
        libconfig::Setting const &element)
    {
        double x = parseDouble(element, "x");
        double y = parseDouble(element, "y");
        double z = parseDouble(element, "z");

        return Maths::Quaternion::fromEulerDegrees(x, y, z);
    }

    Maths::Point3D ParserUtils::parsePoint3D(
        libconfig::Setting const &element)
    {
        double x = parseDouble(element, "x");
        double y = parseDouble(element, "y");
        double z = parseDouble(element, "z");

        return Maths::Point3D{x, y, z};
    }

    Maths::Color ParserUtils::parseColor(libconfig::Setting const &element)
    {
        unsigned int r = 0;
        unsigned int g = 0;
        unsigned int b = 0;

        element.lookupValue("r", r);
        element.lookupValue("g", g);
        element.lookupValue("b", b);
        if (r > 255 || g > 255 || b > 255)
            throw libconfig::SettingTypeException(element);
        return Maths::Color::from8Bit(r, g, b);
    }

    Material::Builder ParserUtils::parseMaterial(
        libconfig::Setting const &element,
        Material::Builder builder)
    {
        if (element.exists("color"))
            builder.color(parseColor(element["color"]));
        if (element.exists("metallic"))
            builder.metallic(parseDouble(element, "metallic"));
        if (element.exists("specular"))
            builder.specular(parseDouble(element, "specular"));
        if (element.exists("roughness"))
            builder.roughness(parseDouble(element, "roughness"));
        if (element.exists("opacity"))
            builder.opacity(parseDouble(element, "opacity"));
        if (element.exists("refraction"))
            builder.refraction(parseDouble(element, "refraction"));
        return builder;
    }

    Material::Builder ParserUtils::getBuilder(
        libconfig::Setting const &element,
        BuilderMap &builders)
    {
        Material::Builder builder{};

        if (element["material"].isGroup()) {
            libconfig::Setting const &material = element["material"];
            if (material.exists("name")
                && builders.contains(material["name"]))
                    builder = builders.find(material["name"])->second;
            builder = parseMaterial(material, builder);
        } else if (builders.contains(element["material"]))
            builder = builders.find(element["material"])->second;
        else
            throw libconfig::SettingTypeException(element);
        return builder;
    }

    std::optional<Texture> ParserUtils::parseTextureName(
        std::string name, TextureGenerationMap maps)
    {
        std::optional<Texture> texture = std::nullopt;

        for (const auto &map: maps) {
            if (std::string(name) == map.first) {
                texture = Texture(map.second);
                break;
            }
        }
        if (!texture)
            texture = Texture(name);
        return texture;
    }

    std::optional<Texture> ParserUtils::parseTexture(
        libconfig::Setting const &element, TextureGenerationMap maps)
    {
        std::optional<Texture> texture = std::nullopt;
    
        if (element.exists("texture")) {
            texture = parseTextureName(element["texture"], maps);
        }
        return texture;
    }

} // RayTracer