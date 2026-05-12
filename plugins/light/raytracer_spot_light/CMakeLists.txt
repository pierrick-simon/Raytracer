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

set(SPOT_LIGHT
    raytracer_spot_light
)

set(SRCS_SPOT_LIGHT
        src/SpotLight.cpp
        src/LibEntryPoints.cpp
        src/SpotLightPlugin.cpp
)


add_library(${SPOT_LIGHT} SHARED ${SRCS_SPOT_LIGHT} ${SHARED_SRCS})
set_target_properties(${SPOT_LIGHT} PROPERTIES PREFIX "")
target_include_directories(${SPOT_LIGHT} PRIVATE include)
