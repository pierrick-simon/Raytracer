cmake_minimum_required(VERSION 3.5)
project(RayTracer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MAIN
    src/Main.cpp
)

set(SRCS
    src/PortablePixMap.cpp
    src/RayTracer.cpp
    src/PortablePixMap.cpp
    src/Parser/ConfigFileParser.cpp
    src/Objects/Camera.cpp
    src/Objects/Sphere.cpp
    src/Objects/Lights/Lights.cpp
    src/Objects/Lights/LightConfig.cpp
    src/Objects/Lights/LightDirectional.cpp
    src/Objects/Lights/PointLight.cpp
)

set(HEADERS
    include/
    include/maths
    include/display
    include/Objects
    include/Parser
    include/Objects/Lights
)

include_directories(${HEADERS})

add_executable(raytracer ${MAIN} ${SRCS})
target_link_libraries(raytracer sfml-graphics sfml-window sfml-system config++)

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
target_compile_options(tests_run_bin PRIVATE --coverage)
target_link_libraries(tests_run_bin criterion --coverage sfml-graphics sfml-window sfml-system config++)

add_custom_target(tests_run
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_SOURCE_DIR}/*.gcda
    COMMAND ${CMAKE_COMMAND} -E rm -f screenshots/test_save.ppm screenshots/test.ppm
    COMMAND ./tests_run_bin
    DEPENDS tests_run_bin
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_subdirectory(plugins/display)

add_custom_target(display
        DEPENDS raytracer_sfml)

file(GLOB_RECURSE LIBS
    "${CMAKE_SOURCE_DIR}/plugins/raytracer_*.so"
)

add_custom_target(clean_libs
    COMMAND rm -f ${LIBS}
)