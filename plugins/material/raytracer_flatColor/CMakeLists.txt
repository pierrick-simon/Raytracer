cmake_minimum_required(VERSION 3.28.3)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SPHERE
    raytracer_flatColor
)

set(SHARED_SRCS
    Parser/ParserUtils.cpp
)

list(TRANSFORM SHARED_SRCS PREPEND ${CMAKE_SOURCE_DIR}/src/)

set(SRCS_FLAT_COLOR
    src/MaterialFlatColor.cpp
    src/LibEntryPoints.cpp
    src/FlatColorPlugin.cpp
)

add_library(${SPHERE} SHARED ${SRCS_FLAT_COLOR} ${SHARED_SRCS})
set_target_properties(${SPHERE} PROPERTIES PREFIX "")
target_include_directories(${SPHERE} PRIVATE include)
