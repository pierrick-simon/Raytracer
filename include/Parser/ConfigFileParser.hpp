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
    #include "LightConfig.hpp"
    #include "Lights.hpp"

namespace RayTracer {
    constexpr std::string_view FILE_EXT = ".cfg";

    class ConfigFileParser {
    public:
        ConfigFileParser(std::string s,
            std::vector<std::unique_ptr<IObjectPlugin>> &primitivePlugins);

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

    private:
        static std::unique_ptr<ILightSource> parseDirectionalLight(
            libconfig::Setting const &);

        static std::unique_ptr<ILightSource> parsePointLight(
            libconfig::Setting const &);

        std::string _filepath;
        std::vector<std::unique_ptr<IObjectPlugin>> &_primitivePlugins;
    };
}

#endif //CONFIGFILEPARSER_HPP
