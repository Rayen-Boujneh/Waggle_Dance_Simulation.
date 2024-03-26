cmake_minimum_required(VERSION 3.25)
project(waggledance2)

# Set the path to SDL2 (modify this path accordingly)
set(SDL2_PATH "path for the library ")
# Find SDL2
find_package(SDL2 REQUIRED)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include SDL2 header files
include_directories(${SDL2_INCLUDE_DIRS})

# Add your source files
add_executable(waggledance2 main.cpp Beehive2.cpp )

# Link against SDL2 libraries
target_link_libraries(waggledance2 ${SDL2_LIBRARIES})

# Set the application type to console
set(CMAKE_WIN32_EXECUTABLE OFF)
