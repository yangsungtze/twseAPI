# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(TWSEAPIFetcher VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable
add_executable(TWSEAPIFetcher
    source/main.cpp
    source/callbacks.cpp
)

# Find CURL library
find_package(CURL REQUIRED)

# Link CURL library to the executable
target_link_libraries(TWSEAPIFetcher CURL::libcurl)
