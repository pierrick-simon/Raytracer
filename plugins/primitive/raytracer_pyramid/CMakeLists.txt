cmake_minimum_required(VERSION 3.28.3)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PYRAMID
    raytracer_pyramid
)

set(SHARED_SRCS
    Parser/ParserUtils.cpp
    Objects/Utils/TriangleShape.cpp
    Objects/materials/Material.cpp
    Objects/Utils/PrimitiveTriangles.cpp
        maths/Color.cpp
)

list(TRANSFORM SHARED_SRCS PREPEND ${CMAKE_SOURCE_DIR}/src/)

set(SRCS_PYRAMID
    src/Pyramid.cpp
    src/LibEntryPoints.cpp
    src/PyramidPlugin.cpp
)

add_library(${PYRAMID} SHARED ${SRCS_PYRAMID} ${SHARED_SRCS})
set_target_properties(${PYRAMID} PROPERTIES PREFIX "")
target_include_directories(${PYRAMID} PRIVATE include)
