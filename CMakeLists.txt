cmake_minimum_required(VERSION 3.10)
project(HashStrings)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable( hashstrings
        hashstrings.c  hashstrings.h
        argtable3.c    argtable3.h )

target_link_libraries( hashstrings m config )
