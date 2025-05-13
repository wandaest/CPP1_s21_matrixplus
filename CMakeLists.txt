cmake_minimum_required(VERSION 3.2)
enable_testing()
project(s21_matrix_plus)
add_compile_options(-Wall -Wextra -Werror)

add_library(s21_matrix_plus STATIC
s21_matrix_oop.h
s21_matrix_oop.cpp
)

add_subdirectory(test)
include_directories(.)
add_subdirectory(googletest)
