cmake_minimum_required(VERSION 3.5)
project(compiladores)

# Require MPI for this project:
find_package(MPI REQUIRED)
# Recursive add folders
file(GLOB ENDF6_SRC_TOP src/*.c)
file(GLOB_RECURSE ENDF6_SRC_NESTED
        src/Benchmarks/*.c
        src/Benchmarks/*.h)
set(ENDF6_SRC ${ENDF6_SRC_TOP} ${ENDF6_SRC_NESTED})

add_executable(MPI ${ENDF6_SRC})
set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})

include_directories(MPI_INCLUDE_PATH)
target_link_libraries(MPI ${MPI_LIBRARIES})