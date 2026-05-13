/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef VERTEX_HPP
    #define VERTEX_HPP
    #include <iosfwd>

    #include "Vector.hpp"

namespace RayTracer {
    class Vertex {
    public:
        explicit Vertex();

        double &operator[](size_t index) noexcept;

        double &getWeight() noexcept;

    private:
        Maths::Vector3D _position;
        double _weight;
    };

    std::istream &operator>>(std::istream &stream, Vertex &vertex);
} // RayTracer

#endif
