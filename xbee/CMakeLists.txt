cmake_minimum_required(VERSION 2.8)

# project declarations
project(xbee_lib C)
project(xbeeTest CXX)
project(xbeeRead CXX)

# add library .c files
file(GLOB xbee_lib_src
    libraries/*.c
)

add_library(xbee_lib STATIC
    ${xbee_lib_src}
)

# some of the project requires c++ 11
# add_definitions(-std=c++11)

# include directories to look for headers
include_directories(
	libraries
)

# main program
add_executable(xbeeTest tests/xbeeTest.cpp)
add_executable(xbeeRead tests/xbeeRead.cpp)

target_link_libraries(xbeeTest LINK_PUBLIC xbee_lib)
target_link_libraries(xbeeRead LINK_PUBLIC xbee_lib)