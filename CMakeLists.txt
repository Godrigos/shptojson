# CMake version check
cmake_minimum_required(VERSION 3.30)

# set the project name and version
project(shptojson VERSION 1.1 LANGUAGES CXX)

# specify the C++ compiler and standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "./build")

# which compilers to use for C and C++
if(CMAKE_CROSSCOMPILING)
    set(CMAKE_C_COMPILER "/usr/bin/x86_64-w64-mingw32-gcc-posix")
    set(CMAKE_CXX_COMPILER "/usr/bin/x86_64-w64-mingw32-g++-posix")
    set(CMAKE_BUILD_TYPE Release) 
    target_link_libraries("/usr/x86_64-w64-mingw32/lib/libole32.a")
else()
    set(CMAKE_C_COMPILER "/usr/bin/gcc")
    set(CMAKE_CXX_COMPILER "/usr/bin/g++")
    set(CMAKE_BUILD_TYPE Release)
endif()

# set source files list
set(source_files ./src/main.cpp ./src/parser.cpp ./src/summary.cpp
    ./src/download.cpp ./src/checkDir.cpp ./src/bar.cpp ./src/convert.cpp
    ./src/confirmDownload.cpp ./src/confirmConvert.cpp)

# Conan settings
find_package(GDAL REQUIRED)
find_package(cpr REQUIRED)
find_package(libzip REQUIRED)
find_package(indicators REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} "${source_files}")

target_link_libraries(${CMAKE_PROJECT_NAME} -ltbb indicators::indicators cpr::cpr GDAL::GDAL libzip::zip)

target_include_directories(${CMAKE_PROJECT_NAME}
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc"                          
)
