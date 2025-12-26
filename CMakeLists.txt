cmake_minimum_required(VERSION 3.16)
project(Shogi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio)

add_library(shogi_core
    core/Piece.cpp
    core/Board.cpp
    core/Move.cpp
)

target_include_directories(shogi_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/core/include/core
)

add_executable(shogi src/main.cpp)

target_link_libraries(shogi PRIVATE
    shogi_core
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)