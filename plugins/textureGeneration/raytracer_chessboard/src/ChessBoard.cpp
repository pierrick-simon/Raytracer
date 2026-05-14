/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ChessBoard
*/

#include <iostream>
#include "ChessBoard.hpp"

namespace RayTracer {
    ChessBoard::ChessBoard(std::size_t size, std::size_t nbSquare,
        Maths::Color color)
        : _size(size * 2), _nbSquare(nbSquare * 2), _color(color)
    {
        _sizeSquare = _size / nbSquare;
    }

    Maths::Color ChessBoard::getColor(std::size_t col, std::size_t row)
    {
        std::size_t squareCol = (col * _nbSquare) / _size;
        std::size_t squareRow = (row * _nbSquare) / _size;

        if ((squareCol + squareRow) % 2 == 0)
            return _color;
        return Maths::Color::WHITE;
    }

    PortablePixMap ChessBoard::generate()
    {
        PortablePixMap map(_size, _size);
        for (std::size_t i = 0; i < _size; i++)
            for (std::size_t j = 0; j < _size; j++)
                map.setPix(i, j, getColor(i, j));
        return map;
    }
}
