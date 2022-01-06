cmake_minimum_required(VERSION 3.21)
project(gameoflife C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Werror)

add_executable(gameoflife main.c)
