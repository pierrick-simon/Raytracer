/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PerlinNoise
*/

#include <iostream>
#include <cstdlib>
#include "PerlinNoise.hpp"

namespace RayTracer {
    PerlinNoise::PerlinNoise(Maths::Vector2U size, std::size_t seed)
        : _size(size), _seed(seed)
    {
        std::srand(seed);
    }

    Maths::Color PerlinNoise::getColor(std::size_t width, std::size_t height)
    {
        Maths::Color color(
            std::round(std::rand() % 2),
            std::round(std::rand() % 2),
            std::round(std::rand() % 2)
        );
        if (std::rand() % 2 == 0)
            return Maths::Color::WHITE;
        std::size_t disruptions = 1 + std::rand() % 4;
        for (std::size_t i = 0; i < disruptions; i++) {
            std::size_t channel = std::rand() % 3;
            double factor = std::rand() % 100 / 100.0;
            double extreme = (std::rand() % 2 == 0)
                ? factor * factor : std::sqrt(factor);
            if (channel == 0)
                color.getX() *= extreme;
            if (channel == 1)
                color.getY() *= extreme;
            if (channel == 2)
                color.getZ() *= extreme;
        }
        return color;
    }

    Maths::Color PerlinNoise::getNextPix(const PortablePixMap &copy,
        std::size_t width, std::size_t height, int i, int j)
    {
        int x = static_cast<int>(width) + i;
        int y = static_cast<int>(height) + j;
        int sx = static_cast<int>(_size.getX());
        int sy = static_cast<int>(_size.getY());

        if (x < 0)
            x += sx;
        if (y < 0)
            y += sy;
        if (x >= sx)
            x -= sx;
        if (y >= sy)
            y -= sy;
        return copy.getPix(static_cast<std::size_t>(x),
                        static_cast<std::size_t>(y));
    }

    Maths::Color PerlinNoise::smoothPix(const PortablePixMap &copy,
        std::size_t width, std::size_t height)
    {
        std::vector<Maths::Color> closeColors;

        for (int i = -3; i <= 3; i++) {
            for (int j = -3; j <= 3; j++) {
                closeColors.push_back(getNextPix(copy, width, height, i , j));
            }
        }
        Maths::Color color = Maths::Color::BLACK;
        for (auto closeColor: closeColors) {
            color.getX() += closeColor.getX();
            color.getY() += closeColor.getY();
            color.getZ() += closeColor.getZ();
            color.getW() += closeColor.getW();
        }
        return color / static_cast<double>(closeColors.size());
    }

    void PerlinNoise::smooth(PortablePixMap &map)
    {
        PortablePixMap copy = map;

        for (std::size_t i = 0; i < _size.getX(); i++) {
            for (std::size_t j = 0; j < _size.getY(); j++) {
                map.setPix(i, j, smoothPix(copy, i, j));
            }
        }
    }

    PortablePixMap PerlinNoise::generate()
    {
        PortablePixMap map(_size.getX(), _size.getY());

        for (std::size_t i = 0; i < _size.getX(); i++) {
            for (std::size_t j = 0; j < _size.getY(); j++) {
                map.setPix(i, j, getColor(i, j));
            }
        }
        for (size_t i = 0; i < 10; i++) {
            smooth(map);
        }
        return map;
    }
}
