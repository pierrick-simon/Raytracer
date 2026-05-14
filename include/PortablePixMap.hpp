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

    #include "Color.hpp"
    #include "Vector.hpp"

namespace RayTracer {
    constexpr std::string_view SCREEN = "screenshots";
    constexpr std::string_view EXT = ".ppm";
    constexpr std::string_view PPM_TYPE = "P3";

    class PortablePixMap {
        public:
            PortablePixMap() {};
            PortablePixMap(Maths::Vector2U vec)
                : _width(vec.getX()), _height(vec.getY()), _map(_width * _height) {};
            PortablePixMap(std::size_t width, std::size_t height)
                : _width(width), _height(height), _map(width * height) {};
            PortablePixMap(std::string filepath);

            void setPix(std::size_t width, std::size_t height, Maths::Color pix);

            Maths::Color getPix(std::size_t width, std::size_t height) const;
            size_t getHeight() const {return _height;}
            size_t getWidth() const {return _width;}

            void save(std::string name);

            class OutOfRangeException : public std::exception {
                public:
                    const char *what() const noexcept override
                        { return "Portable PixMap out of range."; }
            };

            class WrongExtensionException : public std::exception {
                public:
                    const char *what() const noexcept override
                        { return "Wrong File Extension."; }
            };

            class NoSuchFileException : public std::exception {
                public:
                    const char *what() const noexcept override
                        { return "No Such File."; }
            };

            class FileException : public std::exception {
                public:
                    const char *what() const noexcept override
                        { return "File Error."; }
            };

        private:
            bool customGetline(std::reference_wrapper<std::string> str,
                std::reference_wrapper<std::ifstream> file);
            bool readType(std::reference_wrapper<std::ifstream> file);
            bool readSize(std::reference_wrapper<std::ifstream> file);
            bool readMaxSize(std::reference_wrapper<std::ifstream> file);
            bool readBody(std::string line);

            std::size_t _width;
            std::size_t _height;
            std::vector<Maths::Color> _map = {};
    };
};

#endif
