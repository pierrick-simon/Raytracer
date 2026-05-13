cmake_minimum_required(VERSION 3.28.3)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MODEL
    raytracer_model
)

set(SHARED_SRCS
    Parser/ParserUtils.cpp
    Objects/materials/Material.cpp
    maths/Color.cpp
)

list(TRANSFORM SHARED_SRCS PREPEND ${CMAKE_SOURCE_DIR}/src/)

set(SRCS_MODEL
    src/Model.cpp
    src/LibEntryPoints.cpp
    src/ModelPlugin.cpp
    src/data/Vertex.cpp
    src/data/VertexNormal.cpp
    src/data/VertexTexture.cpp
    src/data/Face.cpp
)

add_library(${MODEL} SHARED ${SRCS_MODEL} ${SHARED_SRCS})
set_target_properties(${MODEL} PROPERTIES PREFIX "")
target_include_directories(${MODEL} PRIVATE include)
