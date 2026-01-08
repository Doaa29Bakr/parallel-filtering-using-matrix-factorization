cmake_minimum_required(VERSION 3.20)
project(MatFact_Serial C)

set(CMAKE_C_STANDARD 99)

# We call the executable "MatFact_Serial" and link it to main.c
add_executable(MatFact_Serial main.c)
# This creates a separate program just for mapping titles
add_executable(MovieMapper mapper.c)
add_executable(DataConverter converter.c)