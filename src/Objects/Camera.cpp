/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#include "Camera.hpp"

namespace RayTracer {
    Camera::Camera(Maths::Vector3U const &resolution, Maths::Vector3I const &position,
        Maths::Vector3I const &rotation, double const fov) :
    _resolution(resolution), _position(position), _rotation(rotation), _fov(fov) {}

    void Camera::setResolution(Maths::Vector3U const &reso)
    {
        _resolution = reso;
    }

    void Camera::setPosition(Maths::Vector3I const &pos)
    {
        _position = pos;
    }

    void Camera::setRotation(Maths::Vector3I const &rot)
    {
        _rotation = rot;
    }

    void Camera::setFov(double fov)
    {
        _fov = fov;
    }

    double Camera::getFov() const
    {
        return _fov;
    }

    Maths::Vector3U Camera::getResolution() const
    {
        return _resolution;
    }

    Maths::Vector3I Camera::getPosition() const
    {
        return _position;
    }

    Maths::Vector3I Camera::getRotation() const
    {
        return _rotation;
    }
}
