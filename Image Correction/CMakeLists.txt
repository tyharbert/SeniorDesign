cmake_minimum_required(VERSION 3.3)

# project declarations
project(full_lib C)
project(main C)

# all library .c files
file(GLOB full_lib_src
    "Libraries/*.c"
)

add_library (full_lib STATIC
    ${full_lib_src}
)

#Evaluation program
add_executable(main main.c)

target_link_libraries(main LINK_PUBLIC full_lib)