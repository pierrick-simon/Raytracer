/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#ifndef CAMERA_HPP
    #define CAMERA_HPP
#include "Vector3.hpp"

namespace RayTracer {
    class Camera {
    public:
        Camera(Maths::Vector3<unsigned int> const &resolution, Maths::Vector3<int> const &position, Maths::Vector3<int> const &rotation, double fov);
        void setResolution(Maths::Vector3<unsigned int> const &reso);
        void setPosition(Maths::Vector3<int> const &pos);
        void setRotation(Maths::Vector3<int> const &rot);
        void setFov(double fov);

        [[nodiscard]] double getFov() const;
        [[nodiscard]] Maths::Vector3<unsigned int> getResolution() const;
        [[nodiscard]] Maths::Vector3<int> getPosition() const;
        [[nodiscard]] Maths::Vector3<int> getRotation() const;
    private:
        Maths::Vector3<unsigned int> _resolution;
        Maths::Vector3<int> _position;
        Maths::Vector3<int> _rotation;
        double _fov;
    };
}

#endif //CAMERA_HPP