cmake_minimum_required(VERSION 3.28.3)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CYLINDER
        raytracer_cylinder
)

set(SHARED_SRCS
        Parser/ParserUtils.cpp
        Objects/materials/Material.cpp
        maths/Color.cpp
        Objects/texture/Texture.cpp
        PortablePixMap.cpp
)

list(TRANSFORM SHARED_SRCS PREPEND ${CMAKE_SOURCE_DIR}/src/)

set(SRCS_CYLINDER
        src/PrimitiveCylinder.cpp
        src/LibEntryPoints.cpp
        src/CylinderPlugin.cpp
)

add_library(${CYLINDER} SHARED ${SRCS_CYLINDER} ${SHARED_SRCS})
set_target_properties(${CYLINDER} PROPERTIES PREFIX "")
target_include_directories(${CYLINDER} PRIVATE include)
