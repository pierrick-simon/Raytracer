/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#include "Camera.hpp"
#include <iostream>

namespace RayTracer {
    Camera::Camera(Maths::Vector2U const &resolution, Maths::Point3D const &position,
        Maths::Quaternion const &rotation, double const fov):
    _resolution(resolution), _position(position), _rotation(rotation), _fov(fov),
    _screen(Maths::Point3D(), Maths::Vector3D(), Maths::Vector3D()),
    _nbPix(resolution.getX() * resolution.getY())
    {
        updateCamera();
    }

    void Camera::setResolution(Maths::Vector2U const &reso) noexcept
    {
        _resolution = reso;
    }

    void Camera::setPosition(Maths::Point3D const &pos) noexcept
    {
        _position = pos;
    }

    void Camera::setRotation(Maths::Quaternion const &rot) noexcept
    {
        _rotation = rot;
    }

    void Camera::setFov(double fov) noexcept
    {
        _fov = fov;
    }

    std::size_t Camera::getNbPixel() const noexcept
    {
        return _nbPix;
    }

    double Camera::getFov() const noexcept
    {
        return _fov;
    }

    Maths::Vector2U Camera::getResolution() const noexcept
    {
        return _resolution;
    }

    Maths::Point3D Camera::getPosition() const noexcept
    {
        return _position;
    }

    Maths::Quaternion Camera::getRotation() const noexcept
    {
        return _rotation;
    }

    void Camera::updateCamera() noexcept
    {
        double dist = fabs(_resolution.getY() / (tan(TORAD(_fov / 2.0)) * 2.0));
        Maths::Point3D rectOrigin(dist, (_resolution.getX() * -1.0) / 2.0, _resolution.getY() / 2.0);
        Maths::Point3D pointU(dist, _resolution.getX() / 2.0, _resolution.getY() / 2.0);
        Maths::Point3D pointV(dist, (_resolution.getX() * -1.0) / 2.0, (_resolution.getY() * -1.0) / 2.0);
        rectOrigin *= _rotation;
        pointU *= _rotation;
        pointV *= _rotation;
        rectOrigin += _position;
        pointU += _position;
        pointV += _position;
        _screen.setOrigin(rectOrigin);
        _screen.setTopSide(rectOrigin - pointU);
        _screen.setLeftSide(rectOrigin - pointV);
    }

    Ray Camera::ray(const double &u, const double &v) const noexcept
    {
        Maths::Point3D p = _screen.pointAt(u, v);
        return {_position, _position - p};
    }

}
