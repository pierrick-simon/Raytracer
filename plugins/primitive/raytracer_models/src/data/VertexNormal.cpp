/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#include <iostream>

#include "data/VertexNormal.hpp"

namespace RayTracer {
    double &VertexNormal::operator[](size_t index) noexcept
    {
        return this->_vector[index];
    }

    std::istream &operator>>(std::istream &stream, VertexNormal &vertex)
    {
        for (size_t i = 0; i < 3; ++i) {
            if (stream.eof())
                throw std::invalid_argument(
                    "Required argument for vertex at index "
                    + std::to_string(i));
            stream >> vertex[i];
            if (!stream)
                throw std::invalid_argument(
                    "Invalid argument for vertex at index "
                    + std::to_string(i));
        }
        return stream;
    }
} // RayTracer
