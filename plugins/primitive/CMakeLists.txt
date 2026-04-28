cmake_minimum_required(VERSION 3.5)
project(arcade)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SPHERE
    raytracer_sphere
)

set(SRCS_SPHERE
    ${SPHERE}/PrimitiveSphere.cpp
)

add_library(${SPHERE} SHARED ${SRCS_SPHERE} ${SHARED_SRCS})
set_target_properties(${SPHERE} PROPERTIES PREFIX "")

target_compile_options(${SPHERE} PRIVATE -g)

add_custom_target(move ALL
    DEPENDS ${SPHERE}
    COMMAND mv *.so ../
)
