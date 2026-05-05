/*
** EPITECH PROJECT, 2026
** day10
** File description:
** DESCRIPTION
*/

#pragma once
#include <array>

namespace Maths {
    template<typename A, typename B>
    concept Multipliable = requires(A a, B b)
    {
        a * b;
        a + b;
    };

    template<std::size_t NbRow, std::size_t NbColumn, typename Type>
    class Matrix {
    public:
        Matrix(Type defaultValue)
        {
            for (std::size_t x = 0; x < NbRow; ++x)
                for (std::size_t y = 0; y < NbColumn; ++y)
                    this->_matrix[x][y] = defaultValue;
        }

        double operator()(std::size_t row, std::size_t col) const
        {
            return this->_matrix[row][col];
        }

        double &operator()(std::size_t row, std::size_t col)
        {
            return this->_matrix[row][col];
        }

        template<std::size_t OtherNbColumn, class OtherType> requires
            Multipliable<OtherType, Type>
        using ResultType = Matrix<NbRow, OtherNbColumn, decltype(
            std::declval<Type> * std::declval<OtherType>())>;

        template<std::size_t OtherNbColumn, class OtherType> requires
            Multipliable<OtherType, Type>
        void calculateLine(
            const Matrix<NbColumn, OtherNbColumn, OtherType> &other,
            ResultType<OtherNbColumn, OtherType> result, std::size_t i)
        {
            for (std::size_t j = 0; j < OtherNbColumn; ++j) {
                for (std::size_t k = 0; k < NbColumn; ++k) {
                    result(i, j) += (*this)(i, k) *
                        other(k, j);
                }
            }
        }

        template<std::size_t OtherNbColumn, class OtherType> requires
            Multipliable<OtherType, Type>
        ResultType<OtherNbColumn, OtherType> operator*(
            const Matrix<NbColumn, OtherNbColumn, OtherType> &other)
        {
            ResultType<OtherNbColumn, OtherType> result;
            for (std::size_t i = 0; i < NbRow; ++i) {
                calculateLine<OtherNbColumn, OtherType>(other, result, i);
            }
            return result;
        }

        template<std::size_t OtherNbColumn, typename OtherType>
        Matrix &operator*=(
            const Matrix<NbColumn, OtherNbColumn, OtherType> &other)
        {
            *this = *this * other;
            return *this;
        }

        const std::array<std::array<Type, NbColumn>, NbRow> &getMatrix() const
        {
            return this->_matrix;
        }

    private:
        std::array<std::array<Type, NbColumn>, NbRow> _matrix;
    };

    template<std::size_t NbRow, std::size_t NbColumn, typename OtherType>
    std::ostream &operator<<(std::ostream &input,
        const Matrix<NbRow, NbColumn, OtherType> &matrix)
    {
        input << matrix.getMatrix();
        return input;
    }
}
