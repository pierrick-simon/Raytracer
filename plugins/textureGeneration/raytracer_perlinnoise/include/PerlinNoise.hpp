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
        Maths::Color getColor(std::size_t width, std::size_t height);
        void smooth(PortablePixMap &map);
        Maths::Color smoothPix(const PortablePixMap &copy,
            std::size_t width, std::size_t height);
        Maths::Color getNextPix(const PortablePixMap &copy,
            std::size_t width, std::size_t height, int i, int j);

        Maths::Vector2U _size;
        std::size_t _seed;
    };
};

#endif