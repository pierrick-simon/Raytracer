/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ChessBoard
*/

#include <iostream>
#include "ChessBoard.hpp"

namespace RayTracer {
    ChessBoard::ChessBoard(std::size_t size, std::size_t nbSquare)
        : _size(size * 2), _nbSquare(nbSquare * 2)
    {
        std::cout << size << std::endl << nbSquare << std::endl;
        std::cout << _size << std::endl << _nbSquare << std::endl;
        _sizeSquare = _size / nbSquare;
        _size2Square = _sizeSquare * 2;

        std::cout << _sizeSquare << std::endl << _size2Square << std::endl;
    }

    Maths::Color ChessBoard::getColor(std::size_t width, std::size_t height)
    {
        Maths::Color color = Maths::Color::WHITE;
        if ((width % _size2Square < _sizeSquare
            && height % _size2Square < _sizeSquare)
            || (width % _size2Square >= _sizeSquare
            && height % _size2Square >= _sizeSquare))
            color = Maths::Color::BLACK;
        return color;
    }

    PortablePixMap ChessBoard::generate()
    {
        PortablePixMap map(_size, _size);

        for (std::size_t i = 0; i < _size; i++) {
            for (std::size_t j = 0; j < _size; j++) {
                map.setPix(i, j, getColor(i, j + i * _size));
            }
        }
        return map;
    }
}
