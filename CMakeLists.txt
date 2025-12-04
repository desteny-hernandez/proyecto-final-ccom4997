#cmake
cmake_minimum_required(VERSION 3.10)
project(InvertedProject)
add_executable (inverted main.cpp)

file(COPY baby-dataset-flowers DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
