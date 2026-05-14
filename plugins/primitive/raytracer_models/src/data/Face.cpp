/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#include <sstream>

#include "data/Face.hpp"

namespace RayTracer {
    const std::vector<FaceIndex> &Face::getIndices() const noexcept
    {
        return _indices;
    }
    std::vector<FaceIndex> &Face::getIndices() noexcept
    {
        return _indices;
    }
    void Face::addIndex(const FaceIndex &index)
    {
        _indices.push_back(index);
    }

    std::istream &operator>>(std::istream &stream, FaceIndex &index)
    {
        std::string token;
        std::string part;
        int values[3] = {0, 0, 0};
        int count = 0;

        if (!(stream >> token))
            return stream;

        std::istringstream tss(token);
        while (std::getline(tss, part, '/') && count < 3) {
            if (!part.empty())
                values[count] = std::stoi(part);
            count++;
        }
        index = {values[0], values[1], values[2]};
        return stream;
    }

    std::istream &operator>>(std::istream &stream, Face &face)
    {
        FaceIndex index{};
        bool hasToken = false;

        face = Face{};
        while (stream >> index) {
            face.addIndex(index);
            hasToken = true;
        }
        if (!hasToken)
            stream.setstate(std::ios::failbit);
        return stream;
    }
} // RayTracer