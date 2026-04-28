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
            Camera() {};
            Camera(Maths::Vector3U const &resolution, Maths::Vector3I const &position, Maths::Vector3I const &rotation, double fov);
            void setResolution(Maths::Vector3U const &reso);
            void setPosition(Maths::Vector3I const &pos);
            void setRotation(Maths::Vector3I const &rot);
            void setFov(double fov);

            [[nodiscard]] double getFov() const;
            [[nodiscard]] Maths::Vector3U getResolution() const;
            [[nodiscard]] Maths::Vector3I getPosition() const;
            [[nodiscard]] Maths::Vector3I getRotation() const;
        private:
            Maths::Vector3U _resolution;
            Maths::Vector3I _position;
            Maths::Vector3I _rotation;
            double _fov;
    };
}

#endif //CAMERA_HPP