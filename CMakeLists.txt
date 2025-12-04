#cmake
cmake_minimum_required(VERSION 3.10)
project(InvertedProject)
add_executable (inverted main.cpp)

file(COPY baby-dataset-flowers DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/moviesdb")
    file(COPY moviesdb DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
else()
    message(WARNING "Required data folder 'moviesdb' not found in source directory.")
endif()