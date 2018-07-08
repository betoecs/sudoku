cmake_minimum_required(VERSION 2.8)
project(sudoku)

configure_file(Assets.h.cmake ${CMAKE_SOURCE_DIR}/include/Assets.h)
include_directories(${CMAKE_SOURCE_DIR}/include)
set(SRC src/main.cpp src/MainMenu.cpp src/Sudoku.cpp src/SudokuScene.cpp src/SudokuBoard.cpp src/Timer.cpp)

add_executable(sudoku ${SRC})
target_link_libraries(sudoku -llittle-knight -lsfml-window -lsfml-graphics -lsfml-system -llittle-knight-tile-map)
