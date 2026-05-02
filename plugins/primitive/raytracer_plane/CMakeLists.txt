cmake_minimum_required(VERSION 3.28.3)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SPHERE
    raytracer_plane
)

set(SHARED_SRCS
    Parser/ParserUtils.cpp
    Objects/materials/Material.cpp
)

list(TRANSFORM SHARED_SRCS PREPEND ${CMAKE_SOURCE_DIR}/src/)

set(SRCS_PLANE
    src/PrimitivePlane.cpp
    src/LibEntryPoints.cpp
    src/PlanePlugin.cpp
)

add_library(${SPHERE} SHARED ${SRCS_PLANE} ${SHARED_SRCS})
set_target_properties(${SPHERE} PROPERTIES PREFIX "")
target_include_directories(${SPHERE} PRIVATE include)
