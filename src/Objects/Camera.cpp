/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#include "Camera.hpp"

namespace RayTracer {
    Camera::Camera(Maths::Vector3<unsigned int> const &resolution, Maths::Vector3<int> const &position,
        Maths::Vector3<int> const &rotation, double const fov) :
    _resolution(resolution), _position(position), _rotation(rotation), _fov(fov) {}

    void Camera::setResolution(Maths::Vector3<unsigned int> const &reso)
    {
        _resolution = reso;
    }

    void Camera::setPosition(Maths::Vector3<int> const &pos)
    {
        _position = pos;
    }

    void Camera::setRotation(Maths::Vector3<int> const &rot)
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

    Maths::Vector3<unsigned int> Camera::getResolution() const
    {
        return _resolution;
    }

    Maths::Vector3<int> Camera::getPosition() const
    {
        return _position;
    }

    Maths::Vector3<int> Camera::getRotation() const
    {
        return _rotation;
    }
}
