/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#ifndef PERLINNOISE_HPP
    #define PERLINNOISE_HPP

    #include "ITextureGeneration.hpp"

namespace RayTracer {
    class PerlinNoise : public ITextureGeneration {
    public:
        PerlinNoise(Maths::Vector2U size, std::size_t seed);

        PortablePixMap generate();

    private:

        Maths::Vector2U _size;
        std::size_t _seed;
    };
};

#endif