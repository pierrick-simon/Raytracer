cmake_minimum_required(VERSION 3.5)
project(Raytracer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MAIN
    src/Main.cpp
        include/LibType.hpp
)

set(SRCS
    src/PortablePixMap.cpp
    src/RayTracer.cpp
)

set(HEADERS
    include/
    include/maths
    include/display
)

add_executable(raytracer ${MAIN} ${SRCS})
target_include_directories(raytracer PRIVATE ${HEADERS})

target_compile_options(raytracer PRIVATE -g)

add_custom_target(main
    DEPENDS raytracer
)

find_library(CRITERION criterion REQUIRED)

set(SRCS_TESTS
    tests/tests_init.cpp
    tests/tests_PPM.cpp
)

add_executable(tests_run_bin EXCLUDE_FROM_ALL ${SRCS_TESTS} ${SRCS})
target_include_directories(tests_run_bin PRIVATE ${HEADERS})
target_compile_options(tests_run_bin PRIVATE --coverage)
target_link_libraries(tests_run_bin criterion --coverage)

add_custom_target(tests_run
    DEPENDS tests_run_bin
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/*.gcda
    COMMAND ${CMAKE_COMMAND} -E rm -f screenshots/test.ppm
    COMMAND ./tests_run_bin
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_target(display ALL
    COMMAND ${CMAKE_COMMAND} -B../plugins/display -S../plugins/display
    COMMAND make -C ../plugins/display
)

file(GLOB_RECURSE LIBS
    "${CMAKE_SOURCE_DIR}/plugins/raytracer_*.so"
)

add_custom_target(clean_libs
    COMMAND rm -f ${LIBS}
)