cmake_minimum_required(VERSION 3.21)
project(TuffoMod VERSION 1.0.0)

# Configure GEODE_SDK to the Geode SDK directory before building.
add_subdirectory(${GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

setup_geode_mod(${PROJECT_NAME})
