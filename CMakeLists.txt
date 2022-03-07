cmake_minimum_required(VERSION 3.21)
project(MicroCompiler C)

set(CMAKE_C_STANDARD 99)

add_executable(MicroCompiler main.c translator.c translator.h symbols_table.c symbols_table.h)
