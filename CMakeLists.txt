cmake_minimum_required(VERSION 3.20)
project(rtracer)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${OpenCV_INCLUDE_DIRS})

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

add_executable(rtracer 
                src/main.cpp
                src/utils.cpp)

target_include_directories(rtracer PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(rtracer ${OpenCV_LIBS})
target_sources(rtracer 
                PRIVATE 
                ${CMAKE_SOURCE_DIR}/include/ray.hpp
                ${CMAKE_SOURCE_DIR}/include/utils.hpp)