/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Texture
*/

#ifndef TEXTURE_HPP
    #define TEXTURE_HPP

    #include "PortablePixMap.hpp"
    #include "Vector.hpp"

namespace RayTracer {
    class Texture {
        public:
            Texture(std::string filename);

            Maths::Color getColor(Maths::Vector2D uv, bool inf) const;

        private:
            PortablePixMap _ppm;
    };
}

#endif
