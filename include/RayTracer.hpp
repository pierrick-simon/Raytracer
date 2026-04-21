/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Raytracer
*/

#ifndef RAYTRACER_HPP
    #define RAYTRACER_HPP

    #include <queue>
    #include <string>
    #include <optional>
    #include <exception>
    #include "PortablePixMap.hpp"
    #include "DLLoader.hpp"
    #include "IDisplay.hpp"

namespace RayTracer {

    constexpr int EPISUCCESS = 0;
    constexpr int EPIERROR = 84;
    constexpr std::string_view HELP = "docs/help.txt";
    constexpr std::string_view HELP_FLAG = "--help";
    constexpr std::string_view DISPLAY_FLAG = "--display";
    constexpr std::string_view ARG_EXT = ".ppm";

    class RayTracer {
        public:
            RayTracer(std::queue<std::string> args);

            void run();

            static void showHelp();

            class HelpException : public std::exception {
                public:
                    const char *what() const noexcept override
                        { return "Show Help."; }
            };

            class IncorrectLibTypeException : public std::exception {
                public:
                    const char *what() const noexcept override;
            };

        private:
            void runDisplay();

            std::optional<DLLoader<IDisplay>> _display = std::nullopt;
            PortablePixMap _ppm;
            std::string _name;
    };
};

#endif
