cmake_minimum_required(VERSION 3.20)
project(matFact_OpenMP C)

set(CMAKE_C_STANDARD 99)

# Find and enable OpenMP (Parallel processing)
find_package(OpenMP REQUIRED)
if(OpenMP_C_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_C_FLAGS}")
endif()

# CRITICAL FIX BELOW: Changed "main.c" to "matFact-omp.c"
add_executable(MatFact_OpenMP matFact-omp.c)
add_executable(MovieMapper mapper.c)
add_executable(DataConverter converter.c)