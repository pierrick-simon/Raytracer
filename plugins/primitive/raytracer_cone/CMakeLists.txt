cmake_minimum_required(VERSION 3.28.3)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CONE
        raytracer_cone
)

set(SHARED_SRCS
        Parser/ParserUtils.cpp
        Objects/materials/Material.cpp
        maths/Color.cpp
)

list(TRANSFORM SHARED_SRCS PREPEND ${CMAKE_SOURCE_DIR}/src/)

set(SRCS_CONE
        src/PrimitiveCone.cpp
        src/LibEntryPoints.cpp
        src/ConePlugin.cpp
)

add_library(${CONE} SHARED ${SRCS_CONE} ${SHARED_SRCS})
set_target_properties(${CONE} PROPERTIES PREFIX "")
target_include_directories(${CONE} PRIVATE include)
