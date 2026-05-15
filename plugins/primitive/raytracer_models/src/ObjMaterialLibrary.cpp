/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ObjMaterialLibrary
*/

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

#include "ObjMaterialLibrary.hpp"

namespace RayTracer {
    void ObjMaterialLibrary::parseFile(const std::string &path)
    {
        std::ifstream file(path);

        if (!file.is_open())
            throw std::invalid_argument(
                "The given material path is not a valid file");
        _basePath = std::filesystem::path(path).parent_path();
        while (file >> *this) {
        }
    }

    const std::unordered_map<std::string, ObjMaterialLibrary::MaterialData> &
    ObjMaterialLibrary::getMaterials() const noexcept
    {
        return _materials;
    }

    const ObjMaterialLibrary::MaterialData *ObjMaterialLibrary::findMaterial(
        const std::string &name) const noexcept
    {
        auto it = _materials.find(name);

        if (it == _materials.end())
            return nullptr;
        return &it->second;
    }

    void ObjMaterialLibrary::parseLine(const std::string &line)
    {
        std::string cleanedLine = line.substr(0, line.find('#'));
        std::istringstream iss(cleanedLine);

        iss >> std::ws;
        if (iss.eof())
            return;
        std::string command;
        iss >> command;
        if (!iss || iss.eof())
            throw std::invalid_argument("The given command is not a valid");
        auto it = LINE_PARSE_FUNCTION.find(command);
        if (it != LINE_PARSE_FUNCTION.end())
            (this->*it->second)(iss);
    }

    void ObjMaterialLibrary::addNewMaterial(std::istringstream &line)
    {
        std::string name;

        line >> name;
        if (!line)
            throw std::invalid_argument("Invalid newmtl line");
        line >> std::ws;
        if (!line.eof())
            throw std::invalid_argument("Invalid newmtl line");
        _currentMaterialName = name;
        _materials.insert_or_assign(name, MaterialData{});
    }

    void ObjMaterialLibrary::addAmbient(std::istringstream &line)
    {
        currentMaterial().ambient = parseColor(line, "Ka");
    }

    void ObjMaterialLibrary::addDiffuse(std::istringstream &line)
    {
        currentMaterial().diffuse = parseColor(line, "Kd");
    }

    void ObjMaterialLibrary::addSpecular(std::istringstream &line)
    {
        currentMaterial().specular = parseColor(line, "Ks");
    }

    void ObjMaterialLibrary::addEmission(std::istringstream &line)
    {
        currentMaterial().emission = parseColor(line, "Ke");
    }

    void ObjMaterialLibrary::addTransmission(std::istringstream &line)
    {
        currentMaterial().transmission = parseColor(line, "Tf");
    }

    void ObjMaterialLibrary::addShininess(std::istringstream &line)
    {
        currentMaterial().shininess = parseScalar(line, "Ns");
    }

    void ObjMaterialLibrary::addOpacity(std::istringstream &line)
    {
        currentMaterial().opacity = parseScalar(line, "d");
    }

    void ObjMaterialLibrary::addTransparency(std::istringstream &line)
    {
        currentMaterial().opacity = 1.0 - parseScalar(line, "Tr");
    }

    void ObjMaterialLibrary::addRefraction(std::istringstream &line)
    {
        currentMaterial().refraction = parseScalar(line, "Ni");
    }

    void ObjMaterialLibrary::addIllum(std::istringstream &line)
    {
        double value = parseScalar(line, "illum");

        currentMaterial().illum = static_cast<int>(value);
    }

    void ObjMaterialLibrary::addMetallic(std::istringstream &line)
    {
        currentMaterial().metallic = parseScalar(line, "Pm");
    }

    void ObjMaterialLibrary::addRoughness(std::istringstream &line)
    {
        currentMaterial().roughness = parseScalar(line, "Pr");
    }

    void ObjMaterialLibrary::addTextureAmbient(std::istringstream &line)
    {
        storeTexture(line, "map_Ka");
    }

    void ObjMaterialLibrary::addTextureDiffuse(std::istringstream &line)
    {
        storeTexture(line, "map_Kd");
    }

    void ObjMaterialLibrary::addTextureSpecular(std::istringstream &line)
    {
        storeTexture(line, "map_Ks");
    }

    void ObjMaterialLibrary::addTextureEmission(std::istringstream &line)
    {
        storeTexture(line, "map_Ke");
    }

    void ObjMaterialLibrary::addTextureShininess(std::istringstream &line)
    {
        storeTexture(line, "map_Ns");
    }

    void ObjMaterialLibrary::addTextureOpacity(std::istringstream &line)
    {
        storeTexture(line, "map_d");
    }

    void ObjMaterialLibrary::addTextureBump(std::istringstream &line)
    {
        storeTexture(line, "map_bump");
    }

    void ObjMaterialLibrary::addTextureDisplacement(std::istringstream &line)
    {
        storeTexture(line, "map_disp");
    }

    void ObjMaterialLibrary::addTextureReflection(std::istringstream &line)
    {
        storeTexture(line, "map_refl");
    }

    void ObjMaterialLibrary::addTextureMetallic(std::istringstream &line)
    {
        storeTexture(line, "map_Pm");
    }

    void ObjMaterialLibrary::addTextureRoughness(std::istringstream &line)
    {
        storeTexture(line, "map_Pr");
    }

    ObjMaterialLibrary::MaterialData &ObjMaterialLibrary::currentMaterial()
    {
        if (_currentMaterialName.empty()
            || !_materials.contains(_currentMaterialName))
            throw std::invalid_argument("Material data without active material");
        return _materials[_currentMaterialName];
    }

    void ObjMaterialLibrary::storeTexture(std::istringstream &line,
        const std::string &slot)
    {
        std::string texture = parseTexturePath(line);
        std::filesystem::path texturePath = texture;

        if (!_basePath.empty())
            texturePath = _basePath / texturePath;
        currentMaterial().textures[slot] = texturePath.string();
    }

    Maths::Color ObjMaterialLibrary::parseColor(std::istringstream &line,
        const char *label)
    {
        double r = 0.0;
        double g = 0.0;
        double b = 0.0;

        line >> r >> g >> b;
        if (!line)
            throw std::invalid_argument(
                std::string("Invalid ") + label + " line");
        line >> std::ws;
        if (!line.eof())
            throw std::invalid_argument(
                std::string("Invalid ") + label + " line");
        return Maths::Color(r, g, b);
    }

    double ObjMaterialLibrary::parseScalar(std::istringstream &line,
        const char *label)
    {
        double value = 0.0;

        line >> value;
        if (!line)
            throw std::invalid_argument(
                std::string("Invalid ") + label + " line");
        line >> std::ws;
        if (!line.eof())
            throw std::invalid_argument(
                std::string("Invalid ") + label + " line");
        return value;
    }

    std::string ObjMaterialLibrary::parseTexturePath(std::istringstream &line)
    {
        std::vector<std::string> tokens;
        std::string token;

        while (line >> token)
            tokens.push_back(token);
        if (tokens.empty())
            throw std::invalid_argument("Invalid texture line");
        return tokens.back();
    }

    std::istream &operator>>(std::istream &stream, ObjMaterialLibrary &library)
    {
        std::string line;

        if (!std::getline(stream, line))
            return stream;
        library.parseLine(line);
        return stream;
    }

    const std::unordered_map<std::string, void (ObjMaterialLibrary::*)(
        std::istringstream &)> ObjMaterialLibrary::LINE_PARSE_FUNCTION = {
        {"newmtl", &ObjMaterialLibrary::addNewMaterial},
        {"Ka", &ObjMaterialLibrary::addAmbient},
        {"Kd", &ObjMaterialLibrary::addDiffuse},
        {"Ks", &ObjMaterialLibrary::addSpecular},
        {"Ke", &ObjMaterialLibrary::addEmission},
        {"Tf", &ObjMaterialLibrary::addTransmission},
        {"Ns", &ObjMaterialLibrary::addShininess},
        {"Ni", &ObjMaterialLibrary::addRefraction},
        {"d", &ObjMaterialLibrary::addOpacity},
        {"Tr", &ObjMaterialLibrary::addTransparency},
        {"illum", &ObjMaterialLibrary::addIllum},
        {"Pm", &ObjMaterialLibrary::addMetallic},
        {"Pr", &ObjMaterialLibrary::addRoughness},
        {"map_Ka", &ObjMaterialLibrary::addTextureAmbient},
        {"map_Kd", &ObjMaterialLibrary::addTextureDiffuse},
        {"map_Ks", &ObjMaterialLibrary::addTextureSpecular},
        {"map_Ke", &ObjMaterialLibrary::addTextureEmission},
        {"map_Ns", &ObjMaterialLibrary::addTextureShininess},
        {"map_d", &ObjMaterialLibrary::addTextureOpacity},
        {"map_bump", &ObjMaterialLibrary::addTextureBump},
        {"bump", &ObjMaterialLibrary::addTextureBump},
        {"map_Bump", &ObjMaterialLibrary::addTextureBump},
        {"disp", &ObjMaterialLibrary::addTextureDisplacement},
        {"map_disp", &ObjMaterialLibrary::addTextureDisplacement},
        {"refl", &ObjMaterialLibrary::addTextureReflection},
        {"map_refl", &ObjMaterialLibrary::addTextureReflection},
        {"map_Pm", &ObjMaterialLibrary::addTextureMetallic},
        {"map_Pr", &ObjMaterialLibrary::addTextureRoughness},
    };
} // RayTracer
