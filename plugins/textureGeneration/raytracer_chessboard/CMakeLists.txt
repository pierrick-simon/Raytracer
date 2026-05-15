cmake_minimum_required(VERSION 3.28.3)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CHESSBOARD
    raytracer_chessboard
)

set(SHARED_SRCS
    Parser/ParserUtils.cpp
    maths/Color.cpp
    PortablePixMap.cpp
)

list(TRANSFORM SHARED_SRCS PREPEND ${CMAKE_SOURCE_DIR}/src/)

set(SRCS_CHESSBOARD
    src/ChessBoard.cpp
    src/LibEntryPoints.cpp
    src/ChessBoardPlugin.cpp
)

add_library(${CHESSBOARD} SHARED ${SRCS_CHESSBOARD} ${SHARED_SRCS})
set_target_properties(${CHESSBOARD} PROPERTIES PREFIX "")
target_include_directories(${CHESSBOARD} PRIVATE include)
