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
    #include "Camera.hpp"

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
    private:
        static Maths::Vector3<int> parseVector3I(libconfig::Setting const &element);
        std::string _filepath;
    };
}

#endif //CONFIGFILEPARSER_HPP