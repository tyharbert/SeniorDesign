cmake_minimum_required(VERSION 2.8)

# some of this project requires c 99
add_definitions(-std=c99)

# project declarations
project(spi_lib C)

# add library .c files
file(GLOB spi_lib_src
    software/*.c
)

add_library(spi_lib STATIC
    ${spi_lib_src}
)

# include directories to look for headers
include_directories(
	software
)

