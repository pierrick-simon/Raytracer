cmake_minimum_required(VERSION 3.5)
project(Raytracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2 COMPONENTS graphics window system REQUIRED)

set(MAIN
    src/Main.cpp
)

set(SRCS
    src/PortablePixMap.cpp
    src/PortablePixMap.cpp
    src/Parser/ConfigFileParser.cpp
    src/Objects/Camera.cpp
    src/Objects/Sphere.cpp
    src/Objects/Lights.cpp
)

set(HEADERS
    include/
    include/maths
    include/Objects
    include/Parser
)

add_executable(raytracer ${MAIN} ${SRCS})
target_include_directories(raytracer PRIVATE ${HEADERS})
target_link_libraries(raytracer sfml-graphics sfml-window sfml-system config++)

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
    COMMAND ./tests_run_bin
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)