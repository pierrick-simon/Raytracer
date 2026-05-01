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

    #include "Camera.hpp"
    #include "IObjectPlugin.hpp"
    #include "IMaterialPlugin.hpp"
    #include "LightConfig.hpp"
    #include "Lights.hpp"

namespace RayTracer {
    constexpr std::string_view FILE_EXT = ".cfg";

    class ConfigFileParser {
    public:
        ConfigFileParser(std::string s,
            std::vector<std::unique_ptr<IObjectPlugin>> &primitivePlugins,
            std::vector<std::unique_ptr<IMaterialPlugin>> &materialPlugins);

        class ParserError : public std::exception {
        public:
            explicit ParserError(std::string s);;

            [[nodiscard]] const char *what() const noexcept override;

        private:
            std::string _err;
        };

        [[nodiscard]] Camera parseCamera() const;

        [[nodiscard]] LightConfig parseLights() const;

        [[nodiscard]] std::vector<std::unique_ptr<IObject>>
        parsePrimitives() const;

        [[nodiscard]] std::vector<std::unique_ptr<IObject>>
            parseSimilarPrimitives(libconfig::Setting const &element,
                std::unique_ptr<RayTracer::IObjectPlugin> const &plugins) const;

        [[nodiscard]] std::shared_ptr<IMaterial> parseMaterial(
            libconfig::Setting const &element) const;

    private:
        static std::unique_ptr<ILightSource> parseDirectionalLight(
            libconfig::Setting const &);

        static std::unique_ptr<ILightSource> parsePointLight(
            libconfig::Setting const &);

        std::string _filepath;
        std::vector<std::unique_ptr<IObjectPlugin>> &_primitivePlugins;
        std::vector<std::unique_ptr<IMaterialPlugin>> &_materialPlugins;
    };
}

#endif //CONFIGFILEPARSER_HPP
