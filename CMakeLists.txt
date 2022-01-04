# CMake version check
cmake_minimum_required(VERSION 3.15)

# set the project name and version
project(shptojson VERSION 1.0 LANGUAGES CXX)

add_subdirectory(Linux)

target_include_directories(${CMAKE_PROJECT_NAME}
    PUBLIC "${CMAKE_CURRENT_LIST_DIR}/inc"                          
)