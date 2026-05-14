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

    #include "DLLoader.hpp"
    #include "Camera.hpp"
    #include "ILightSourcePlugin.hpp"
    #include "IObjectPlugin.hpp"
    #include "LightConfig.hpp"
    #include "Material.hpp"
    #include "ITextureGenerationPlugin.hpp"

namespace RayTracer {
    constexpr std::string_view FILE_EXT = ".cfg";

    class ConfigFileParser {
    public:
        ConfigFileParser(std::vector<std::string> &args);

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
                std::unique_ptr<IObjectPlugin> const &plugins) const;

    private:
        void loadPrimitivePlugins();
        void loadLightPlugins();
        void loadTexturePlugins();

        std::string _filepath;
        std::vector<DLLoader<IObjectPlugin>> _primitivesPluginsLoaders;
        std::vector<std::unique_ptr<IObjectPlugin>> _primitivesPlugins;
        std::vector<DLLoader<ILightSourcePlugin>> _lightsPluginsLoaders;
        std::vector<std::unique_ptr<ILightSourcePlugin>> _lightsPlugins;
        std::vector<DLLoader<ITextureGenerationPlugin>> _texturesGenerationPluginsLoaders;
        std::vector<std::unique_ptr<ITextureGenerationPlugin>> _texturesGenerationPlugins;
        std::unordered_map<std::string, Material::Builder> _materialBuilders;
        static BuilderMap _presetMaterialBuilders;
        static constexpr std::string_view PLUGINS_FOLDER = "plugins";
    };
}

#endif //CONFIGFILEPARSER_HPP
