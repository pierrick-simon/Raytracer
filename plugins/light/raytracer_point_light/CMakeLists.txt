cmake_minimum_required(VERSION 3.28.3)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SHARED_SRCS
        Parser/ParserUtils.cpp
        Objects/Lights/ALightSource.cpp
        Objects/materials/Material.cpp
        maths/Color.cpp
)

list(TRANSFORM SHARED_SRCS PREPEND ${CMAKE_SOURCE_DIR}/src/)

set(POINT_LIGHT
    raytracer_point_light
)

set(SRCS_POINT_LIGHT
        src/PointLight.cpp
        src/LibEntryPoints.cpp
        src/PointLightPlugin.cpp
)


add_library(${POINT_LIGHT} SHARED ${SRCS_POINT_LIGHT} ${SHARED_SRCS})
set_target_properties(${POINT_LIGHT} PROPERTIES PREFIX "")
target_include_directories(${POINT_LIGHT} PRIVATE include)
