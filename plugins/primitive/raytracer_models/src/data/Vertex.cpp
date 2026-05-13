/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#include <iostream>

#include "data/Vertex.hpp"

namespace RayTracer {
    Vertex::Vertex() :
        _weight(1)
    {
    }

    double &Vertex::operator[](size_t index) noexcept
    {
        return this->_position[index];
    }

    double &Vertex::getWeight() noexcept
    {
        return this->_weight;
    }

    std::istream &operator>>(std::istream &stream, Vertex &vertex)
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
        stream >> std::ws;
        if (!stream.eof()) {
            stream >> vertex.getWeight();
            if (!stream)
                throw std::invalid_argument(
                    "Invalid argument for vertex for weight");
        }
        return stream;
    }
} // RayTracer
