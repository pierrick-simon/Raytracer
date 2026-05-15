/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#include <iostream>

#include "data/VertexTexture.hpp"

namespace RayTracer {
    double &VertexTexture::operator[](size_t index) noexcept
    {
        return this->_texturePosition[index];
    }

    const double &VertexTexture::operator[](size_t index) const noexcept
    {
        return this->_texturePosition[index];
    }

    std::istream &operator>>(std::istream &stream, VertexTexture &vertex)
    {
        bool readAny = false;

        for (size_t i = 0; i < 3; ++i) {
            if (!stream.eof())
                stream >> std::ws;
            if (stream.eof())
                break;
            stream >> vertex[i];
            if (!stream)
                throw std::invalid_argument(
                    "Invalid argument for vertex at index "
                    + std::to_string(i));
            readAny = true;
        }
        if (!readAny)
            throw std::invalid_argument(
                "Required argument for vertical texture pos");
        return stream;
    }
} // RayTracer
