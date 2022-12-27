# Human's note:
# This entire file was AI generated (except where specified ;P)
# It's quite funny because by the time the AI had finished I had only just open Kate to start writing into the file :O

cmake_minimum_required(VERSION 3.10)
project(parameters) #Name change from sdl_example to parameter


list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)


# Find the SDL2 package
find_package(SDL2 REQUIRED)

# Find the SDL2_ttf library
find_package(SDL2_ttf REQUIRED)

# Add the source files
set(SOURCES src/main.cpp)

# Add the executable
add_executable(parameters ${SOURCES})

# Add SDL2 library
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Main)

# Add SDL2_ttf library
find_package(SDL2_ttf REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::TTF)

# Include the include directory
target_include_directories(parameters PRIVATE include)
