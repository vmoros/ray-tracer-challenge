cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RayTracer)

enable_testing()
add_subdirectory(src)
add_subdirectory(tests)