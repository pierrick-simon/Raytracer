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

Test(PPM_LOAD, normal)
{
    std::string filename = "normal";
    filename = "tests/testFile/PPM/" + filename + ".ppm";

    try {
        RayTracer::PortablePixMap tmp(filename);
        filename = "test";
        tmp.save(filename);
        filename += ".ppm";
        cr_assert_str_eq(readFile("screenshots/" + filename, false).c_str(), readFile(filename, true).c_str());
    } catch (RayTracer::PortablePixMap::NoSuchFileException &_) {
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::WrongExtensionException &_) {
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::FileException &_) {
        cr_assert(false);
    }
}

Test(PPM_LOAD, NoSuchFile)
{
    try {
        RayTracer::PortablePixMap tmp("toto.ppm");
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::NoSuchFileException &e) {
        cr_assert_str_eq(e.what(), "No Such File.");
    } catch (RayTracer::PortablePixMap::WrongExtensionException &_) {
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::FileException &_) {
        cr_assert(false);
    }
}

Test(PPM_LOAD, WrongExtension)
{
    std::string filename = "wrong_extension.txt";
    filename = "tests/testFile/PPM/" + filename;

    try {
        RayTracer::PortablePixMap tmp(filename);
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::NoSuchFileException &_) {
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::WrongExtensionException &e) {
        cr_assert_str_eq(e.what(), "Wrong File Extension.");
    } catch (RayTracer::PortablePixMap::FileException &_) {
        cr_assert(false);
    }
}

Test(PPM_LOAD, JustExtension)
{
    std::string filename = ".ppm";

    try {
        RayTracer::PortablePixMap tmp(filename);
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::NoSuchFileException &_) {
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::WrongExtensionException &e) {
        cr_assert_str_eq(e.what(), "Wrong File Extension.");
    } catch (RayTracer::PortablePixMap::FileException &_) {
        cr_assert(false);
    }
}

Test(PPM_LOAD, empty)
{
    std::string filename = "empty";
    filename = "tests/testFile/PPM/" + filename + ".ppm";

    try {
        RayTracer::PortablePixMap tmp(filename);
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::NoSuchFileException &_) {
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::WrongExtensionException &_) {
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::FileException &e) {
        cr_assert_str_eq(e.what(), "File Error.");
    }
}

Test(PPM_LOAD, missing_size)
{
    std::string filename = "missing_size";
    filename = "tests/testFile/PPM/" + filename + ".ppm";

    try {
        RayTracer::PortablePixMap tmp(filename);
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::NoSuchFileException &_) {
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::WrongExtensionException &_) {
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::FileException &e) {
        cr_assert_str_eq(e.what(), "File Error.");
    }
}

Test(PPM_LOAD, wrong_body)
{
    std::string filename = "wrong_body";
    filename = "tests/testFile/PPM/" + filename + ".ppm";

    try {
        RayTracer::PortablePixMap tmp(filename);
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::NoSuchFileException &_) {
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::WrongExtensionException &_) {
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::FileException &e) {
        cr_assert_str_eq(e.what(), "File Error.");
    }
}

Test(PPM_LOAD, wrong_max)
{
    std::string filename = "wrong_max_size";
    filename = "tests/testFile/PPM/" + filename + ".ppm";

    try {
        RayTracer::PortablePixMap tmp(filename);
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::NoSuchFileException &_) {
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::WrongExtensionException &_) {
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::FileException &e) {
        cr_assert_str_eq(e.what(), "File Error.");
    }
}

Test(PPM_LOAD, wrong_size)
{
    std::string filename = "wrong_size";
    filename = "tests/testFile/PPM/" + filename + ".ppm";

    try {
        RayTracer::PortablePixMap tmp(filename);
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::NoSuchFileException &_) {
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::WrongExtensionException &_) {
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::FileException &e) {
        cr_assert_str_eq(e.what(), "File Error.");
    }
}

Test(PPM_LOAD, wrong_type)
{
    std::string filename = "wrong_type";
    filename = "tests/testFile/PPM/" + filename + ".ppm";

    try {
        RayTracer::PortablePixMap tmp(filename);
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::NoSuchFileException &_) {
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::WrongExtensionException &_) {
        cr_assert(false);
    } catch (RayTracer::PortablePixMap::FileException &e) {
        cr_assert_str_eq(e.what(), "File Error.");
    }
}
