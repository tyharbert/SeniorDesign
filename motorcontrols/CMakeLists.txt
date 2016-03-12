cmake_minimum_required(VERSION 2.8)

# project declarations
project(servo_lib C)
project(capture_test C)

# add library .c files
file(GLOB servo_lib_src
    libraries/*.c
)

add_library(servo_lib STATIC
    ${servo_lib_src}
)

# include directories to look for headers
include_directories(
	libraries
)

# main program
add_executable(capture_test tests/capture.c)

target_link_libraries(capture_test LINK_PUBLIC servo_lib pthread wiringPi)