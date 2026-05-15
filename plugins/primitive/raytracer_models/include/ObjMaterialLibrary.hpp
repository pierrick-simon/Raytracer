/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ObjMaterialLibrary
*/

#ifndef OBJMATERIALLIBRARY_HPP
    #define OBJMATERIALLIBRARY_HPP

    #include <filesystem>
    #include <istream>
    #include <string>
    #include <unordered_map>

    #include "Color.hpp"

namespace RayTracer {
    class ObjMaterialLibrary {
    public:
        struct MaterialData {
            Maths::Color ambient = Maths::Color::BLACK;
            Maths::Color diffuse = Maths::Color::WHITE;
            Maths::Color specular = Maths::Color::BLACK;
            Maths::Color emission = Maths::Color::BLACK;
            Maths::Color transmission = Maths::Color::BLACK;
            double shininess = 0.0;
            double opacity = 1.0;
            double refraction = 1.0;
            double metallic = 0.0;
            double roughness = 0.0;
            int illum = 0;
            std::unordered_map<std::string, std::string> textures;
        };

        ObjMaterialLibrary() = default;

        void parseFile(const std::string &path);

        [[nodiscard]] const std::unordered_map<std::string, MaterialData> &
            getMaterials() const noexcept;

        [[nodiscard]] const MaterialData *findMaterial(
            const std::string &name) const noexcept;

    private:
        friend std::istream &operator>>(std::istream &stream,
            ObjMaterialLibrary &library);

        void parseLine(const std::string &line);

        void addNewMaterial(std::istringstream &line);
        void addAmbient(std::istringstream &line);
        void addDiffuse(std::istringstream &line);
        void addSpecular(std::istringstream &line);
        void addEmission(std::istringstream &line);
        void addTransmission(std::istringstream &line);
        void addShininess(std::istringstream &line);
        void addOpacity(std::istringstream &line);
        void addTransparency(std::istringstream &line);
        void addRefraction(std::istringstream &line);
        void addIllum(std::istringstream &line);
        void addMetallic(std::istringstream &line);
        void addRoughness(std::istringstream &line);
        void addTextureAmbient(std::istringstream &line);
        void addTextureDiffuse(std::istringstream &line);
        void addTextureSpecular(std::istringstream &line);
        void addTextureEmission(std::istringstream &line);
        void addTextureShininess(std::istringstream &line);
        void addTextureOpacity(std::istringstream &line);
        void addTextureBump(std::istringstream &line);
        void addTextureDisplacement(std::istringstream &line);
        void addTextureReflection(std::istringstream &line);
        void addTextureMetallic(std::istringstream &line);
        void addTextureRoughness(std::istringstream &line);

        MaterialData &currentMaterial();
        void storeTexture(std::istringstream &line, const std::string &slot);

        static Maths::Color parseColor(std::istringstream &line,
            const char *label);
        static double parseScalar(std::istringstream &line,
            const char *label);
        static std::string parseTexturePath(std::istringstream &line);

        std::unordered_map<std::string, MaterialData> _materials;
        std::string _currentMaterialName;
        std::filesystem::path _basePath;

        static const std::unordered_map<std::string, void (ObjMaterialLibrary::*)(
            std::istringstream &)> LINE_PARSE_FUNCTION;
    };

    std::istream &operator>>(std::istream &stream, ObjMaterialLibrary &library);
} // RayTracer

#endif
