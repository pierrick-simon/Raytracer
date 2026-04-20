/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DisplaySFML
*/

#ifndef DISPLAYSFML_HPP
    #define DISPLAYSFML_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "IDisplay.hpp"

namespace RayTracer {

    constexpr std::size_t FPS = 120;
    constexpr unsigned int WINDOW_SIZE_X = 1920;
    constexpr unsigned int WINDOW_SIZE_Y = 1080;
    constexpr unsigned int WINDOW_BITS = 144;

    class DisplaySFML : public IDisplay {
        public:
            DisplaySFML();

            Event getEvent();
            void draw(PortablePixMap);

        private:
            Action keyPressed(sf::Event event);
            Action mousseButton(sf::Event event);

            static const std::unordered_map<sf::Keyboard::Key, Action> _keyMap;
            static const std::unordered_map<int, Action> _mouseButtonMap;
            sf::RenderWindow _window;
    };
};

#endif
