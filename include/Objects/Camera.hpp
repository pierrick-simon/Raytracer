/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#ifndef CAMERA_HPP
    #define CAMERA_HPP

#include "Vector3.hpp"
#include "Rectangle.hpp"
#include "Ray.hpp"

namespace RayTracer {
    class Camera {
        public:
            Camera() = default;
            Camera(Maths::Vector3U const &resolution, Maths::Point3D const
                &position, Maths::Vector3D const &rotation, double fov);

            Ray ray(const double &u, const double &v) const noexcept;
            void updateCamera() noexcept;

            void setResolution(Maths::Vector3U const &reso) noexcept;
            void setPosition(Maths::Point3D const &pos) noexcept;
            void setRotation(Maths::Vector3D const &rot) noexcept;
            void setFov(double fov) noexcept;

            [[nodiscard]] double getFov() const noexcept;
            [[nodiscard]] std::size_t getNbPixel() const noexcept;
            [[nodiscard]] Maths::Vector3U getResolution() const noexcept;
            [[nodiscard]] Maths::Point3D getPosition() const noexcept;
            [[nodiscard]] Maths::Vector3D getRotation() const noexcept;
        private:
            Maths::Vector3U _resolution;
            std::size_t _nbPix;
            Maths::Point3D _position;
            Maths::Vector3D _rotation;
            double _fov;
            Rectangle _screen;
    };
}

#endif //CAMERA_HPP