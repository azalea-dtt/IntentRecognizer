cmake_minimum_required(VERSION 3.16)


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

project(intentrecognition LANGUAGES CXX)
# set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)




include_directories(src)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()


