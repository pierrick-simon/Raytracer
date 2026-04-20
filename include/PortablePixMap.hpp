/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PortablePixMap
*/

#ifndef PORTABLEPIXMAP_HPP
    #define PORTABLEPIXMAP_HPP

    #include <cstddef>
    #include <vector>
    #include <string>
    #include <string_view>
    #include <exception>
    #include <filesystem>
    #include <fstream>
    #include "Vector3.hpp"

namespace RayTracer {
    constexpr std::string_view SCREEN = "screenshots";
    constexpr std::string_view EXT = ".ppm";
    constexpr std::string_view PPM_TYPE = "P3";

    class PortablePixMap {
        public:
            PortablePixMap(std::size_t width, std::size_t height)
                : _width(width), _height(height), _map(width * height) {};

            void setPix(std::size_t width, std::size_t height, Maths::RGB pix);
            Maths::RGB getPix(std::size_t width, std::size_t height);

            void save(std::string name);

            class OutOfRangeException : public std::exception {
                public:
                    const char *what() const noexcept override
                        { return "Portable PixMap out of range."; };
            };

        private:
        std::size_t _width;
        std::size_t _height;
        std::vector<Maths::RGB> _map = {};
    };
};

#endif
