cmake_minimum_required(VERSION 3.2)

project(ray)

#find_package(OPENMP REQUIRED)

# Create a debug build
IF (APPLE)
    set(CMAKE_CXX_FLAGS "-DRT_USE_BILINEAR_TEXTURE_FILTERING -Xpreprocessor -fopenmp -Wall -O3 --std=c++14 -g -lomp")
ELSE ()
    set(CMAKE_CXX_FLAGS "-DRT_USE_BILINEAR_TEXTURE_FILTERING -Xpreprocessor -Wall -O3 --std=c++14 -g -fopenmp")
ENDIF ()



#set(CMAKE_CXX_FLAGS, "-Wall -O3 -std=c++14 -g -fopenmp")

# Set all CPP files to be source files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Code/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
