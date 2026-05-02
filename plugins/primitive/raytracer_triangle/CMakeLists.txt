cmake_minimum_required(VERSION 3.28.3)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TRIANGLE
    raytracer_triangle
)

set(SHARED_SRCS
    Parser/ParserUtils.cpp
)

list(TRANSFORM SHARED_SRCS PREPEND ${CMAKE_SOURCE_DIR}/src/)

set(SRCS_TRIANGLE
    src/PrimitiveTriangle.cpp
    src/LibEntryPoints.cpp
    src/TrianglePlugin.cpp
)

add_library(${TRIANGLE} SHARED ${SRCS_TRIANGLE} ${SHARED_SRCS})
set_target_properties(${TRIANGLE} PROPERTIES PREFIX "")
target_include_directories(${TRIANGLE} PRIVATE include)
