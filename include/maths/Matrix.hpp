/*
** EPITECH PROJECT, 2026
** day10
** File description:
** DESCRIPTION
*/

#ifndef MATRIX_HPP
    #define MATRIX_HPP
    #include <array>
    #include <cstddef>
    #include <ostream>
    #include <utility>

namespace Maths {
    template<typename A, typename B>
    concept Multipliable = requires(A a, B b)
    {
        { a * b };
    };

    template<typename T>
    concept AddAssignable = requires(T a, T b)
    {
        { a += b } -> std::same_as<T &>;
    };

    template<typename A, typename B>
    concept Addable = requires(A a, B b)
    {
        { a + b };
    };

    template<std::size_t NbRow, std::size_t NbColumn, typename Type>
    class Matrix {
    public:
        using MatrixType = std::array<std::array<Type, NbColumn>, NbRow>;

        explicit Matrix() :
            _matrix{}
        {
        };

        explicit Matrix(Type defaultValue)
        {
            for (std::size_t x = 0; x < NbRow; ++x)
                for (std::size_t y = 0; y < NbColumn; ++y)
                    this->_matrix[x][y] = defaultValue;
        }

        explicit Matrix(MatrixType matrix) :
            _matrix(matrix)
        {
        }

        Type operator()(std::size_t row, std::size_t col) const
        {
            return this->_matrix[row][col];
        }

        Type &operator()(std::size_t row, std::size_t col)
        {
            return this->_matrix[row][col];
        }

        template<class OtherType>
        using ProductType = decltype(
            std::declval<Type>() * std::declval<OtherType>());

        template<class OtherType>
        using AdditionType = decltype(
            std::declval<Type>() + std::declval<OtherType>());

        template<class OtherType>
        using SubtractionType = decltype(
            std::declval<Type>() - std::declval<OtherType>());

        template<std::size_t OtherNbColumn, class OtherType> requires
            Multipliable<Type, OtherType> && AddAssignable<ProductType<
                OtherType>>
        void calculateLine(
            const Matrix<NbColumn, OtherNbColumn, OtherType> &other,
            Matrix<NbRow, OtherNbColumn, ProductType<OtherType>> &result,
            std::size_t i) const
        {
            for (std::size_t j = 0; j < OtherNbColumn; ++j) {
                result(i, j) = ProductType<OtherType>{};
                for (std::size_t k = 0; k < NbColumn; ++k) {
                    result(i, j) += (*this)(i, k) *
                        other(k, j);
                }
            }
        }

        template<std::size_t OtherNbColumn, class OtherType> requires
            Multipliable<Type, OtherType> && AddAssignable<ProductType<
                OtherType>>
        Matrix<NbRow, OtherNbColumn, ProductType<OtherType>> operator*(
            const Matrix<NbColumn, OtherNbColumn, OtherType> &other) const
        {
            Matrix<NbRow, OtherNbColumn, ProductType<OtherType>> result(
                ProductType<OtherType>{});
            for (std::size_t i = 0; i < NbRow; ++i) {
                calculateLine<OtherNbColumn, OtherType>(other, result, i);
            }
            return result;
        }

        template<typename OtherType> requires Addable<Type, OtherType>
        Matrix<NbRow, NbColumn, AdditionType<OtherType>> operator+(
            const Matrix<NbRow, NbColumn, OtherType> &other) const
        {
            Matrix<NbRow, NbColumn, AdditionType<OtherType>> result;

            for (std::size_t i = 0; i < NbRow; ++i)
                for (std::size_t j = 0; j < NbColumn; ++j)
                    result(i, j) = (*this)(i, j) + other(i, j);
            return result;
        }

        template<typename OtherType> requires Addable<Type, OtherType>
        Matrix<NbRow, NbColumn, SubtractionType<OtherType>> operator-(
            const Matrix<NbRow, NbColumn, OtherType> &other) const
        {
            Matrix<NbRow, NbColumn, SubtractionType<OtherType>> result;

            for (std::size_t i = 0; i < NbRow; ++i)
                for (std::size_t j = 0; j < NbColumn; ++j)
                    result(i, j) = (*this)(i, j) - other(i, j);
            return result;
        }

        template<typename ScalarType> requires Multipliable<Type, ScalarType>
        Matrix<NbRow, NbColumn, ProductType<ScalarType>> operator*(
            const ScalarType &scalar) const
        {
            Matrix<NbRow, NbColumn, ProductType<ScalarType>> result;

            for (std::size_t i = 0; i < NbRow; ++i)
                for (std::size_t j = 0; j < NbColumn; ++j)
                    result(i, j) = (*this)(i, j) * scalar;
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
        MatrixType _matrix;
    };

    template<std::size_t NbRow, std::size_t NbColumn, typename Type>
    std::ostream &operator<<(std::ostream &input,
        const Matrix<NbRow, NbColumn, Type> &matrix)
    {
        input << "[";
        for (std::size_t i = 0; i < NbRow; ++i) {
            input << "[";
            for (std::size_t j = 0; j < NbColumn; ++j) {
                input << matrix.getMatrix()[i][j];
                if (j + 1 != NbColumn)
                    input << ", ";
            }
            input << "]";
            if (i + 1 != NbRow)
                input << ", ";
        }
        input << "]";
        return input;
    }

    template<size_t NbRow, size_t NbColumn>
    using MatrixD = Matrix<NbRow, NbColumn, double>;
}

#endif
