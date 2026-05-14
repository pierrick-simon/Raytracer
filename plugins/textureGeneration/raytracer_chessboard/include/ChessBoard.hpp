/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#ifndef CHESSBOARD_HPP
    #define CHESSBOARD_HPP

    #include "ITextureGeneration.hpp"

namespace RayTracer {
    class ChessBoard : public ITextureGeneration {
    public:
        ChessBoard(std::size_t size, std::size_t nbSquare, Maths::Color color);

        PortablePixMap generate();

    private:
        Maths::Color getColor(std::size_t width, std::size_t height);

        std::size_t _size;
        std::size_t _nbSquare;
        std::size_t _sizeSquare;
        Maths::Color _color;
    };
};

#endif