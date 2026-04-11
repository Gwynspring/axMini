cmake_minimum_required(VERSION 3.25)
project(axMini VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

# Interface Library
add_library(axMini_options INTERFACE)
target_compile_options(axMini_options INTERFACE -Wall -Wextra -Wpedantic)
target_include_directories(axMini_options INTERFACE
    ${CMAKE_SOURCE_DIR}/include
)

# Dependencies
add_subdirectory(lib/spdlog)

# Subdirectories
add_subdirectory(src)
add_subdirectory(tests)

