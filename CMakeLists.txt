cmake_minimum_required(VERSION 2.8)

# some of the project requires c++ 11
add_definitions(-std=c++11)

# add subdirectories
add_subdirectory(
	imagecorrection
)

add_subdirectory(
	xbee
)

add_subdirectory(
	motorcontrols
)

add_subdirectory(
	powersystem
)

# include directories to look for headers
include_directories(
	imagecorrection/libraries
	xbee/libraries
	motorcontrols/libraries
	powersystem/software
)

#project declaration
project(main CXX)
project(calibrate CXX)

#main program
add_executable(main integration/main.cpp)
add_executable(calibrate integration/calibrate.cpp)

target_link_libraries(main LINK_PUBLIC pthread wiringPi m)
target_link_libraries(main LINK_PUBLIC img_lib)
target_link_libraries(main LINK_PUBLIC xbee_lib)
target_link_libraries(main LINK_PUBLIC calib_lib)
target_link_libraries(main LINK_PUBLIC spi_lib)

target_link_libraries(calibrate LINK_PUBLIC calib_lib pthread wiringPi)
