cmake_minimum_required(VERSION 3.5)
project(arcade)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SHARED
    ../../include/
    ../../include/display
    ../../include/maths
)

set(SFML
    raytracer_sfml
)

set(SRCS_SFML
    ${SFML}/DisplaySFML.cpp
)

add_library(${SFML} SHARED ${SRCS_SFML})
target_include_directories(${SFML} PRIVATE ${SFML} ${SHARED})
target_link_libraries(${SFML} sfml-graphics sfml-window sfml-system sfml-audio)
set_target_properties(${SFML} PROPERTIES PREFIX "")

target_compile_options(${SFML} PRIVATE -g)

add_custom_target(move ALL
    DEPENDS ${SFML}
    COMMAND mv *.so ../
)
