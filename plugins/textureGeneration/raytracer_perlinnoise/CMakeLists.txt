cmake_minimum_required(VERSION 3.28.3)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PERLINNOISE
    raytracer_perlinnoise
)

set(SHARED_SRCS
    Parser/ParserUtils.cpp
    maths/Color.cpp
    PortablePixMap.cpp
)

list(TRANSFORM SHARED_SRCS PREPEND ${CMAKE_SOURCE_DIR}/src/)

set(SRCS_PERLINNOISE
    src/PerlinNoise.cpp
    src/LibEntryPoints.cpp
    src/PerlinNoisePlugin.cpp
)

add_library(${PERLINNOISE} SHARED ${SRCS_PERLINNOISE} ${SHARED_SRCS})
set_target_properties(${PERLINNOISE} PROPERTIES PREFIX "")
target_include_directories(${PERLINNOISE} PRIVATE include)
