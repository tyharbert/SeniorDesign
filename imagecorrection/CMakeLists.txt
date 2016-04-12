cmake_minimum_required(VERSION 2.8)

# some of the project requires c++ 11
add_definitions(-std=c++11)

# project declarations
project(img_lib CXX)
project(transform CXX)

# add library .cpp files
file(GLOB img_lib_src
    libraries/*.cpp
)

add_library(img_lib STATIC
    ${img_lib_src}
)

# include directories to look for headers
include_directories(
	libraries
)

# main program
add_executable(transform tests/transform.cpp)

target_link_libraries(transform LINK_PUBLIC img_lib)