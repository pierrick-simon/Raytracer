/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/


#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std()
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(Example, example_test)
{
    cr_assert_eq(true, true);
}