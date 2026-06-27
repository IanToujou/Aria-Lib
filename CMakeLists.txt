cmake_minimum_required(VERSION 3.22)
project(Aria_Lib C)

set(CMAKE_C_STANDARD 11)

add_library(Aria_Lib STATIC
        include/color.h
        include/argument.h
        src/argument.c
)
