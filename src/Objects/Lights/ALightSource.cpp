/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#include "ALightSource.hpp"

namespace RayTracer {
    ALightSource::ALightSource(const Maths::Point3D &pos) :
        _pos(pos)
    {
    }

    Maths::Point3D ALightSource::getPosition() const
    {
        return this->_pos;
    }
} // RayTracer
