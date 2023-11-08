cmake_minimum_required(VERSION 3.10)
project(renatoolkits VERSION 0.1.0 LANGUAGES C CXX)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(RENATOOLKITS_NO_RICH)
    add_definitions(-D__RENATOOLKITS_NO_RICH__)
endif()

if(RENATOOLKITS_NO_MAGIC_ENUM)
    add_definitions(-D__RENATOOLKITS_NO_MAGIC_ENUM__)
endif()

if(RENATOOLKITS_NO_CMDLINE)
    add_definitions(-D__RENATOOLKITS_NO_CMDLINE__)
endif()

if(RENATOOLKITS_NO_KBE)
    add_definitions(-D__RENATOOLKITS_NO_KBE__)
endif()

include_directories(include)
add_subdirectory(src)

if(RENATOOLKITS_MAKE_EXAMPLE)
    add_subdirectory(example)
endif()