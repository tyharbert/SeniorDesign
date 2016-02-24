cmake_minimum_required(VERSION 3.3)

# some of the project requires c++ 11
SET(CMAKE_CXX_FLAGS "-std=c++11")

#project declarations
project(full_lib CXX)
project(main CXX)

#add library .cpp files
file(GLOB full_lib_src
    libraries/*.cpp
)

add_library(full_lib STATIC
    ${full_lib_src}
)

#main program
add_executable(main main.cpp)

target_link_libraries(main LINK_PUBLIC full_lib)