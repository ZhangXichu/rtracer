cmake_minimum_required(VERSION 3.20)
project(rtracer)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(rtracer src/main.cpp)

target_include_directories(rtracer PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(rtracer ${OpenCV_LIBS})
target_sources(rtracer PRIVATE ${CMAKE_SOURCE_DIR}/include/ray.hpp)