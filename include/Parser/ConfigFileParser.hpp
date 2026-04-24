/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#ifndef CONFIGFILEPARSER_HPP
    #define CONFIGFILEPARSER_HPP
    #include <string>
    #include <libconfig.h++>
#include <memory>
#include <vector>

    #include "Camera.hpp"
#include "../Objects/Lights/LightConfig.hpp"
#include "Lights.hpp"
#include "Shpere.hpp"

namespace RayTracer {
    class ConfigFileParser {
    public:
        explicit ConfigFileParser(std::string);

        class ParserError : public std::exception {
        public:
            explicit ParserError(char *);
            [[nodiscard]] const char *what() const noexcept override;
        private:
            char *_err;
        };

        [[nodiscard]] Camera parseCamera() const;

        [[nodiscard]] LightConfig parseLights() const;
        [[nodiscard]] std::vector<std::unique_ptr<IObject>>
        parsePrimitives() const;
    private:
        static Maths::Vector3<int> parseVector3I(libconfig::Setting const &element);
        static Maths::RGB parseColor(libconfig::Setting const &element);
        static std::unique_ptr<IObject> parseSphere(
            libconfig::Setting const &element);
        static std::vector<std::unique_ptr<IObject>> parseSpheres(
            libconfig::Setting const &element);
        static std::unique_ptr<ILightSource> parseDirectionalLight(libconfig::Setting const &);
        static std::unique_ptr<ILightSource> parsePointLight(libconfig::Setting const &);
        std::string _filepath;
    };
}

#endif //CONFIGFILEPARSER_HPP