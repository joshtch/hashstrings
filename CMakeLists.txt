cmake_minimum_required(VERSION 3.10)
project(HashStrings)

set( CMAKE_C_STANDARD 11 )
set( CMAKE_C_FLAGS    "-Wall -Wextra" )

include_directories(.)

add_executable( hashstrings
        hashstrings.c  hashstrings.h
        argtable3.c    argtable3.h )

target_link_libraries( hashstrings m config )

set( CMAKE_INSTALL_PREFIX /usr )
install( TARGETS hashstrings )