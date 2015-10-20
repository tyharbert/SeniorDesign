cmake_minimum_required(VERSION 3.3)

# project declarations
project(imglib C)
project(filelib C)
project(utilslib C)
project(main C)

# image library
add_library (imglib STATIC
 Libraries/imglib.c	
)

# file io library
add_library (filelib STATIC
 Libraries/file_io.c	
)

# utilities library
add_library (utilslib STATIC
 Libraries/utils.c	
)

#Evaluation program
add_executable(main main.c)

target_link_libraries(main LINK_PUBLIC imglib)
target_link_libraries(main LINK_PUBLIC filelib)
target_link_libraries(main LINK_PUBLIC utilslib)