/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#ifndef CONFIGFILEPARSER_HPP
    #define CONFIGFILEPARSER_HPP

    #include <string>
    #include <string_view>
    #include <libconfig.h++>
    #include <memory>
    #include <vector>
    #include <unordered_map>

    #include "Camera.hpp"
#include "ILightSourcePlugin.hpp"
    #include "IObjectPlugin.hpp"
    #include "LightConfig.hpp"
    #include "Lights.hpp"
    #include "Material.hpp"

namespace RayTracer {
    constexpr std::string_view FILE_EXT = ".cfg";

    class ConfigFileParser {
    public:
        ConfigFileParser(std::string filepath,
        std::vector<std::unique_ptr<IObjectPlugin>> &primitivePlugins,
        std::vector<std::unique_ptr<ILightSourcePlugin>> &lightPlugins,
            BuilderMap &materials);

        class ParserError : public std::exception {
        public:
            explicit ParserError(std::string s);;

            [[nodiscard]] const char *what() const noexcept override;

        private:
            std::string _err;
        };

        [[nodiscard]] Camera parseCamera() const;

        [[nodiscard]] LightConfig parseLights() const;

        void parseMaterials(
            libconfig::Setting const &element);

        [[nodiscard]] std::vector<std::unique_ptr<IObject>>
            parsePrimitives() const;

        [[nodiscard]] static std::vector<std::unique_ptr<ILightSource>>
        parseSimilarLight(
            libconfig::Setting const &lightsSetting,
            std::unique_ptr<ILightSourcePlugin> const &plugin);

        [[nodiscard]] std::vector<std::unique_ptr<IObject>>
            parseSimilarPrimitives(libconfig::Setting const &element,
                std::unique_ptr<RayTracer::IObjectPlugin> const &plugins) const;

    private:
        static std::unique_ptr<ILightSource> parseDirectionalLight(
            libconfig::Setting const &);

        static std::unique_ptr<ILightSource> parsePointLight(
            libconfig::Setting const &);

        std::string _filepath;
        std::vector<std::unique_ptr<IObjectPlugin>> &_primitivePlugins;
        std::vector<std::unique_ptr<ILightSourcePlugin>> &_lightPlugins;
        std::unordered_map<std::string, Material::Builder> _presetMaterialBuilders;
    };
}

#endif //CONFIGFILEPARSER_HPP
