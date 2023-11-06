cmake_minimum_required(VERSION 3.10)
project(renatoolkits VERSION 0.1.0 LANGUAGES C CXX)

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)