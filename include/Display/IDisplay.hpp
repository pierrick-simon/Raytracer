/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** IDisplay
*/

#ifndef IDISPLAY_HPP
    #define IDISPLAY_HPP

    #include "Display.hpp"
    #include "PortablePixMap.hpp"

namespace RayTracer {

    class IDisplay {
        public:
            virtual ~IDisplay() = default;

            virtual Event event() = 0;
            virtual void draw(PortablePixMap) = 0;
    };
};

#endif
