# Define minimum CMake version
cmake_minimum_required(VERSION 3.22)

# If you wish to specifiy compiler do it before project, otherwise it won't work
# For that use this part of commented out code:
# find_program(CMAKE_C_COMPILER NAMES $ENV{CC} gcc PATHS ENV PATH NO_DEFAULT_PATH)
# find_program(CMAKE_CXX_COMPILER NAMES $ENV{CXX} g++ PATHS ENV PATH NO_DEFAULT_PATH)
# Better use env variables for that, or have specific toolchain sourced.
# CXX for C++ and CC for C

# Name project and tack versions
project(my_project_name
  VERSION 1.0
  LANGUAGES CXX)

# Set cpp standard and make it a must
set(CMAKE_CXX_STANDARD 20)
# Also disable any platform specifc optimizations
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED On)

# Set Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror \
  -Wextra --pedantic -Wold-style-cast \
  -Wwrite-strings")

# Pull any external libs
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
find_package(benchmark REQUIRED)

# Add subprojects
# Include dirs is for hdrs files, so it is easier to reference hdrs from root dir in project
include_directories(src)
# This is for and directory that should be included in build
add_subdirectory(src)

# For testing, and thta ctest can find tests
enable_testing()
add_subdirectory(benchmark)

