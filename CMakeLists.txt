cmake_minimum_required(VERSION 3.25)
project(axMini
        VERSION 0.1.0
        LANGUAGES CXX
      )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

add_executable(axMini
  src/main.cpp
  src/VariableEngine.cpp
)

target_include_directories(
  axMini
  PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/cpp-httplib
    ${CMAKE_SOURCE_DIR}/include
)
