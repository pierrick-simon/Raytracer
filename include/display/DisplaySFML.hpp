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
    constexpr unsigned int WINDOW_BITS = 32;
    inline const sf::Color DARKBLUE = sf::Color(51, 75, 99);

    class DisplaySFML : public IDisplay {
        public:
            DisplaySFML();

            Event getEvent();
            void draw(PortablePixMap);

        private:
            Action keyPressed(sf::Event event);
            Action mousseButton(sf::Event event);
            void resized();

            static const std::unordered_map<sf::Keyboard::Key, Action> _keyMap;
            static const std::unordered_map<int, Action> _mouseButtonMap;
            sf::RenderWindow _window;
            sf::View _view;
            sf::RectangleShape _background;
            sf::RectangleShape _pix;
            sf::Vector2f _size = {WINDOW_SIZE_X, WINDOW_SIZE_Y};
    };
};

#endif
