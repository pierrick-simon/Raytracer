cmake_minimum_required(VERSION 3.5)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SHARED_SRCS
    ../../src/PortablePixMap.cpp
)

set(SFML
    raytracer_sfml
)

set(SRCS_SFML
    ${SFML}/DisplaySFML.cpp
)

add_library(${SFML} SHARED ${SRCS_SFML} ${SHARED_SRCS})
target_link_libraries(${SFML} sfml-graphics sfml-window sfml-system sfml-audio)
set_target_properties(${SFML} PROPERTIES PREFIX "")

add_custom_target(move ALL
    DEPENDS ${SFML}
    COMMAND mv *.so ../
)
