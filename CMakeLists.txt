cmake_minimum_required(VERSION 3.25)
project(game_engine_gui VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)


set(DIR_SRC ${PROJECT_SOURCE_DIR}/src)
set(DIR_TEST ${PROJECT_SOURCE_DIR}/test)

add_subdirectory(src)
add_subdirectory(test)
