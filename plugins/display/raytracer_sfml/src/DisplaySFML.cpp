/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DisplaySFML
*/

#include "../include/DisplaySFML.hpp"

#include "LibType.hpp"

RayTracer::DisplaySFML::DisplaySFML()
    : _window(sf::RenderWindow(
        sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, WINDOW_BITS),
    "RayTracer", sf::Style::Close | sf::Style::Resize)),
    _view(sf::FloatRect(0.0, 0.0, WINDOW_SIZE_X, WINDOW_SIZE_Y))
{
    _window.setView(_view);
    _background.setSize({WINDOW_SIZE_X, WINDOW_SIZE_Y});
    _pix.setSize({1, 1});
    _background.setFillColor(sf::Color::Black);
    _window.setFramerateLimit(FPS);
}

RayTracer::Event RayTracer::DisplaySFML::getEvent()
{
    sf::Vector2i mouspos = sf::Mouse::getPosition(_window);
    sf::Vector2u size = _window.getSize();
    Maths::Vector3D pos(
        (float)(mouspos.x) / size.x, (float)(mouspos.y) / size.y, 0);
    Action action = Action::None;
    Event value = {action, pos};
    sf::Event event;

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            value = {Action::Close, pos};
        action = keyPressed(event);
        if (action != Action::None)
            value = {action, pos};
        action = mousseButton(event);
        if (action != Action::None)
            value = {action, pos};
        if (event.type == sf::Event::Resized)
            resized();
    }
    return value;
}

RayTracer::Action RayTracer::DisplaySFML::keyPressed(sf::Event event)
{
    Action action = Action::None;

    if (event.type == sf::Event::KeyPressed) {
        auto tmp = _keyMap.find(event.key.code);
        if (tmp != _keyMap.end())
            action = tmp->second;
    }
    return action;
}

RayTracer::Action RayTracer::DisplaySFML::mousseButton(sf::Event event)
{
    Action action = Action::None;

    if(event.type == sf::Event::MouseButtonPressed){
        auto tmp = _mouseButtonMap.find(event.mouseButton.button);
        if (tmp != _mouseButtonMap.end())
            action = tmp->second;
    }
    return action;
}

void RayTracer::DisplaySFML::draw(PortablePixMap ppm)
{
    _size = {static_cast<float>(ppm.getWidth()),
        static_cast<float>(ppm.getHeight())};
     _window.clear(DARKBLUE);
    resized();
    _background.setSize(_size);
    _window.draw(_background);
    for (size_t i = 0; i < ppm.getHeight(); i++) {
        for (size_t j = 0; j < ppm.getWidth(); j++) {
            auto color = ppm.getPix(j, i);
            _pix.setFillColor({color.getX(), color.getY(), color.getZ()});
            _pix.setPosition({static_cast<float>(j), static_cast<float>(i)});
            _window.draw(_pix);
        }
    }
    _window.display();
}

void RayTracer::DisplaySFML::resized()
{
    _view.reset(sf::FloatRect(0, 0, _size.x, _size.y));
    float windowRatio = static_cast<float>(_window.getSize().x) /
                        static_cast<float>(_window.getSize().y);
    float viewRatio   = _size.x / _size.y;
    sf::Vector2f size = {1, 1};
    sf::Vector2f pos  = {0, 0};

    if (windowRatio >= viewRatio) {
        size.x = viewRatio / windowRatio;
        pos.x  = (1.0f - size.x) / 2.0f;
    } else {
        size.y = windowRatio / viewRatio;
        pos.y  = (1.0f - size.y) / 2.0f;
    }

    _view.setViewport(sf::FloatRect(pos.x, pos.y, size.x, size.y));
    _window.setView(_view);
}

const std::unordered_map<sf::Keyboard::Key, RayTracer::Action>
    RayTracer::DisplaySFML::_keyMap = {
    {sf::Keyboard::Key::Unknown, Action::None},
    {sf::Keyboard::Key::A, Action::A},
    {sf::Keyboard::Key::B, Action::B},
    {sf::Keyboard::Key::C, Action::C},
    {sf::Keyboard::Key::D, Action::D},
    {sf::Keyboard::Key::E, Action::E},
    {sf::Keyboard::Key::F, Action::F},
    {sf::Keyboard::Key::G, Action::G},
    {sf::Keyboard::Key::H, Action::H},
    {sf::Keyboard::Key::I, Action::I},
    {sf::Keyboard::Key::J, Action::J},
    {sf::Keyboard::Key::K, Action::K},
    {sf::Keyboard::Key::L, Action::L},
    {sf::Keyboard::Key::M, Action::M},
    {sf::Keyboard::Key::N, Action::N},
    {sf::Keyboard::Key::O, Action::O},
    {sf::Keyboard::Key::P, Action::P},
    {sf::Keyboard::Key::Q, Action::Q},
    {sf::Keyboard::Key::R, Action::R},
    {sf::Keyboard::Key::S, Action::S},
    {sf::Keyboard::Key::T, Action::T},
    {sf::Keyboard::Key::U, Action::U},
    {sf::Keyboard::Key::V, Action::V},
    {sf::Keyboard::Key::W, Action::W},
    {sf::Keyboard::Key::X, Action::X},
    {sf::Keyboard::Key::Y, Action::Y},
    {sf::Keyboard::Key::Z, Action::Z},
    {sf::Keyboard::Key::Num1, Action::Num1},
    {sf::Keyboard::Key::Num2, Action::Num2},
    {sf::Keyboard::Key::Num3, Action::Num3},
    {sf::Keyboard::Key::Num4, Action::Num4},
    {sf::Keyboard::Key::Num5, Action::Num5},
    {sf::Keyboard::Key::Num6, Action::Num6},
    {sf::Keyboard::Key::Num7, Action::Num7},
    {sf::Keyboard::Key::Num8, Action::Num8},
    {sf::Keyboard::Key::Num9, Action::Num9},
    {sf::Keyboard::Key::Num0, Action::Num0},
    {sf::Keyboard::Key::Return, Action::Enter},
    {sf::Keyboard::Key::Escape, Action::Escape},
    {sf::Keyboard::Key::BackSpace, Action::Backspace},
    {sf::Keyboard::Key::Tab, Action::Tab},
    {sf::Keyboard::Key::Space, Action::Space},
    {sf::Keyboard::Key::Subtract, Action::Subtract},
    {sf::Keyboard::Key::Equal, Action::Equal},
    {sf::Keyboard::Key::LBracket, Action::LBracket},
    {sf::Keyboard::Key::RBracket, Action::RBracket},
    {sf::Keyboard::Key::BackSlash, Action::Backslash},
    {sf::Keyboard::Key::SemiColon, Action::Semicolon},
    {sf::Keyboard::Key::Quote, Action::Apostrophe},
    {sf::Keyboard::Key::Comma, Action::Comma},
    {sf::Keyboard::Key::Period, Action::Period},
    {sf::Keyboard::Key::Slash, Action::Slash},
    {sf::Keyboard::Key::F1, Action::F1},
    {sf::Keyboard::Key::F2, Action::F2},
    {sf::Keyboard::Key::F3, Action::F3},
    {sf::Keyboard::Key::F4, Action::F4},
    {sf::Keyboard::Key::F5, Action::F5},
    {sf::Keyboard::Key::F6, Action::F6},
    {sf::Keyboard::Key::F7, Action::F7},
    {sf::Keyboard::Key::F8, Action::F8},
    {sf::Keyboard::Key::F9, Action::F9},
    {sf::Keyboard::Key::F10, Action::F10},
    {sf::Keyboard::Key::F11, Action::F11},
    {sf::Keyboard::Key::F12, Action::F12},
    {sf::Keyboard::Key::Pause, Action::Pause},
    {sf::Keyboard::Key::Insert, Action::Insert},
    {sf::Keyboard::Key::Home, Action::Home},
    {sf::Keyboard::Key::PageUp, Action::PageUp},
    {sf::Keyboard::Key::Delete, Action::Delete},
    {sf::Keyboard::Key::End, Action::End},
    {sf::Keyboard::Key::PageDown, Action::PageDown},
    {sf::Keyboard::Key::Right, Action::Right},
    {sf::Keyboard::Key::Left, Action::Left},
    {sf::Keyboard::Key::Down, Action::Down},
    {sf::Keyboard::Key::Up, Action::Up},
    {sf::Keyboard::Key::Divide, Action::Divide},
    {sf::Keyboard::Key::Multiply, Action::Multiply},
    {sf::Keyboard::Key::Subtract, Action::Subtract},
    {sf::Keyboard::Key::Add, Action::Add},
    {sf::Keyboard::Key::Enter, Action::Enter},
    {sf::Keyboard::Key::Numpad1, Action::Numpad1},
    {sf::Keyboard::Key::Numpad2, Action::Numpad2},
    {sf::Keyboard::Key::Numpad3, Action::Numpad3},
    {sf::Keyboard::Key::Numpad4, Action::Numpad4},
    {sf::Keyboard::Key::Numpad5, Action::Numpad5},
    {sf::Keyboard::Key::Numpad6, Action::Numpad6},
    {sf::Keyboard::Key::Numpad7, Action::Numpad7},
    {sf::Keyboard::Key::Numpad8, Action::Numpad8},
    {sf::Keyboard::Key::Numpad9, Action::Numpad9},
    {sf::Keyboard::Key::Numpad0, Action::Numpad0},
    {sf::Keyboard::Key::Period, Action::Period},
    {sf::Keyboard::Key::F13, Action::F13},
    {sf::Keyboard::Key::F14, Action::F14},
    {sf::Keyboard::Key::F15, Action::F15},
    {sf::Keyboard::Key::LShift, Action::LShift},
    {sf::Keyboard::Key::RShift, Action::RShift},
};

const std::unordered_map<int, RayTracer::Action>
    RayTracer::DisplaySFML::_mouseButtonMap = {
    {sf::Mouse::Left, Action::LeftMouse},
    {sf::Mouse::Middle, Action::MiddleMouse},
    {sf::Mouse::Right, Action::RightMouse},
};

extern "C" RayTracer::IDisplay *rayTracerLibEntryPoint()
{
    return new RayTracer::DisplaySFML();
}

extern "C" RayTracer::LibType rayTracerType()
{
    return RayTracer::LibType::GRAPHICS;
}
