/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#include "Camera.hpp"

namespace RayTracer {
    Camera::Camera(Maths::Vector3U const &resolution, Maths::Point3D const &position,
        Maths::Vector3D const &rotation, double const fov):
    _resolution(resolution), _position(position), _rotation(rotation), _fov(fov),
    _screen(Maths::Point3D(), Maths::Vector3D(), Maths::Vector3D())
    {
        updateCamera();
    }


    void Camera::setResolution(Maths::Vector3U const &reso) noexcept
    {
        _resolution = reso;
    }

    void Camera::setPosition(Maths::Point3D const &pos) noexcept
    {
        _position = pos;
    }

    void Camera::setRotation(Maths::Vector3D const &rot) noexcept
    {
        _rotation = rot;
    }

    void Camera::setFov(double fov) noexcept
    {
        _fov = fov;
    }

    double Camera::getFov() const noexcept
    {
        return _fov;
    }

    Maths::Vector3U Camera::getResolution() const noexcept
    {
        return _resolution;
    }

    Maths::Point3D Camera::getPosition() const noexcept
    {
        return _position;
    }

    Maths::Vector3D Camera::getRotation() const noexcept
    {
        return _rotation;
    }

    void Camera::updateCamera() noexcept
    {
        double dist = abs(_resolution.y / (tan(_fov) * 2));
        Maths::Point3D rectOrigin(dist, (_resolution.x * -1.0) / 2.0, _resolution.y / 2.0);
        Maths::Point3D pointU(dist, _resolution.x / 2.0, _resolution.y / 2.0);
        Maths::Point3D pointV(dist, (_resolution.x * -1.0) / 2.0, (_resolution.y * -1.0) / 2.0);
        _screen.setOrigin(rectOrigin);
        _screen.setTopSide(Maths::Vector3D(rectOrigin, pointU));
        _screen.setLeftSide(Maths::Vector3D(rectOrigin, pointV));
    }

    Ray Camera::ray(const double &u, const double &v) const noexcept
    {
        Maths::Point3D p = _screen.pointAt(u, v);
        return {_position, Maths::Vector3D(_position, p), Maths::RGB(255, 255, 255)};
    }

}
