cmake_minimum_required(VERSION 2.8)

# some of the project requires c++ 11
add_definitions(-std=c++11)

# add subdirectories
add_subdirectory(
	ImageCorrection
	Xbee
)

# include directories to look for headers
include_directories(
	ImageCorrection/libraries
	Xbee/libraries
)

#project declaration
project(main CXX)

#main program
add_executable(main main.cpp)

target_link_libraries(main LINK_PUBLIC img_lib)