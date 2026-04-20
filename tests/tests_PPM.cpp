/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** tests_PPM
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "PortablePixMap.hpp"

static void redirect_all_std()
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(PPM, getPix_out_of_range)
{
    std::size_t w = 3;
    std::size_t h = 3;
    RayTracer::PortablePixMap tmp(w, h);

    try {
        tmp.getPix(w, h);
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::OutOfRangeException &e) {
        cr_assert_str_eq(e.what(), "Portable PixMap out of range.");
    }
}

Test(PPM, setPix_out_of_range)
{
    std::size_t w = 3;
    std::size_t h = 3;
    RayTracer::PortablePixMap tmp(w, h);

    try {
        tmp.setPix(w, h, Maths::RGB());
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::OutOfRangeException &e) {
        cr_assert_str_eq(e.what(), "Portable PixMap out of range.");
    }
}

Test(PPM, setPix_getPix_success)
{
    std::size_t w = 3;
    std::size_t h = 3;
    std::size_t n = 0;
    std::size_t pix = 128;
    RayTracer::PortablePixMap tmp(w, h);
    Maths::RGB color(pix, pix, pix);

    
    try {
        tmp.setPix(n, n, color);
        Maths::RGB test = tmp.getPix(n, n);
        cr_assert_eq(test.x, color.x);
        cr_assert_eq(test.y, color.y);
        cr_assert_eq(test.z, color.z);
    } catch (RayTracer::PortablePixMap::OutOfRangeException &_) {
        cr_assert(false);
    }
}

static std::string readFile(std::string path, bool test)
{
    if (test)
        path = "tests/testResult/" + path;

    std::ifstream file(path);
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

Test(PPM, save)
{
    std::string filename = "test";
    std::size_t w = 3;
    std::size_t h = 3;
    RayTracer::PortablePixMap tmp(w, h);

    tmp.save(filename);
    filename += ".ppm";
    cr_assert_str_eq(readFile("screenshots/" + filename, false).c_str(), readFile(filename, true).c_str());
}
