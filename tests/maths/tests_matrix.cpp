/*
** EPITECH PROJECT, 2026
** day10
** File description:
** DESCRIPTION
*/

#include <cmath>
#include <iostream>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "Matrix.hpp"

static void givenMain()
{
    Maths::MatrixD<3, 1> point;
    Maths::MatrixD<3, 3> translation;
    Maths::MatrixD<3, 3> rotation;

    point(0, 0) = 3;
    point(1, 0) = 2;
    point(2, 0) = 1;
    std::cout << "P: " << point << std::endl;

    translation(0, 0) = translation(1, 1) = translation(2, 2) = 1.0;
    translation(0, 2) = 4;
    translation(1, 2) = 2;
    point = translation * point;
    std::cout << "T: " << translation << std::endl;
    std::cout << "P: " << point << std::endl;

    rotation(0, 0) = +std::cos(std::numbers::pi / 2);
    rotation(0, 1) = -std::sin(std::numbers::pi / 2);
    rotation(1, 0) = +std::sin(std::numbers::pi / 2);
    rotation(1, 1) = +std::cos(std::numbers::pi / 2);
    rotation(2, 2) = 1;
    point = rotation * point;
    std::cout << "R: " << rotation << std::endl;
    std::cout << "P: " << point << std::endl;

}

Test(matrix, givenExample)
{
    cr_redirect_stdout();

    givenMain();

    std::flush(std::cout);

    cr_assert_stdout_eq_str(
        "P: [[3], [2], [1]]\n"
        "T: [[1, 0, 4], [0, 1, 2], [0, 0, 1]]\n"
        "P: [[7], [4], [1]]\n"
        "R: [[6.12323e-17, -1, 0], [1, 6.12323e-17, 0], [0, 0, 1]]\n"
        "P: [[-4], [7], [1]]\n"
    );
}

Test(matrix, concepts)
{
    static_assert(Maths::Multipliable<int, int>);
    static_assert(!Maths::Multipliable<int, std::string>);

    static_assert(Maths::AddAssignable<int>);
    static_assert(!Maths::AddAssignable<const int>);
}
