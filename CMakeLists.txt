cmake_minimum_required(VERSION 3.28.3)
project(RayTracer CXX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MAIN
    src/Main.cpp
)

set(SRCS
    src/PortablePixMap.cpp
    src/RayTracer.cpp
    src/PortablePixMap.cpp
    src/Parser/ConfigFileParser.cpp
    src/Parser/ParserUtils.cpp
    src/Objects/Camera.cpp
    src/Objects/Lights/LightConfig.cpp
    src/Objects/Lights/ALightSource.cpp
    src/Objects/materials/Material.cpp
    src/Objects/materials/PresetMaterialBuilders.cpp
    src/Objects/texture/Texture.cpp
    src/Objects/Rectangle.cpp
    src/Objects/Utils/TriangleShape.cpp
    src/Objects/Utils/PrimitiveTriangles.cpp
    src/maths/Quaternion.cpp
    src/maths/Color.cpp
)

set(HEADERS
    include/
    include/maths
    include/display
    include/Objects
    include/Parser
    include/Objects/Lights
    include/Objects/materials
    include/Objects/Utils
    include/Objects/texture
)

include_directories(${HEADERS})

option(ENABLE_ASAN "Enable Address Sanitizer" OFF)

if (ENABLE_ASAN)
    set(ASAN_FLAGS -fsanitize=address -fno-omit-frame-pointer)
    add_compile_options(${ASAN_FLAGS})
    add_link_options(${ASAN_FLAGS})
endif()

add_executable(raytracer ${MAIN} ${SRCS})
target_link_libraries(raytracer sfml-graphics sfml-window sfml-system config++)

target_compile_options(raytracer PRIVATE -g)

add_custom_target(main
    DEPENDS raytracer
)

find_library(CRITERION criterion REQUIRED)

set(SRCS_TESTS
    tests/tests_init.cpp
    tests/tests_PPM.cpp
    tests/maths/tests_quaternions.cpp
    tests/maths/tests_matrix.cpp
    tests/maths/tests_vector.cpp
)

add_executable(tests_run_bin EXCLUDE_FROM_ALL ${SRCS_TESTS} ${SRCS})
target_compile_options(tests_run_bin PRIVATE --coverage)
target_link_libraries(tests_run_bin criterion --coverage sfml-graphics sfml-window sfml-system config++)

add_custom_target(tests_run
    COMMAND find ${CMAKE_BINARY_DIR} -name "*.gcda" -delete
    COMMAND ${CMAKE_COMMAND} -E rm -f screenshots/test_save.ppm screenshots/test.ppm
    COMMAND ./tests_run_bin
    DEPENDS tests_run_bin
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

list(TRANSFORM SRCS PREPEND ${CMAKE_SOURCE_DIR}/)

add_subdirectory(plugins/display/raytracer_sfml)
add_subdirectory(plugins/primitive/raytracer_sphere)
add_subdirectory(plugins/primitive/raytracer_plane)
add_subdirectory(plugins/primitive/raytracer_pyramid)
add_subdirectory(plugins/primitive/raytracer_cylinder)
add_subdirectory(plugins/primitive/raytracer_models)

add_custom_target(display
    DEPENDS raytracer_sfml)

add_custom_target(primitives
    DEPENDS raytracer_sphere
        raytracer_plane
        raytracer_pyramid
        raytracer_cylinder)

add_subdirectory(plugins/light/raytracer_point_light)
add_subdirectory(plugins/light/raytracer_spot_light)

add_custom_target(lights
        DEPENDS raytracer_point_light
            raytracer_spot_light)

add_subdirectory(plugins/textureGeneration/raytracer_chessboard)
add_subdirectory(plugins/textureGeneration/raytracer_perlinnoise)

add_custom_target(textureGenerations
    DEPENDS raytracer_chessboard raytracer_perlinnoise)

add_custom_target(plugins
    DEPENDS primitives display lights textureGenerations)
