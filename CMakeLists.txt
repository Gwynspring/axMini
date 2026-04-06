cmake_minimum_required(VERSION 3.25)
project(axMini
        VERSION 0.1.0
        LANGUAGES CXX
      )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

add_library(axMini_options INTERFACE)
target_compile_options(axMini_options INTERFACE -Wall -Wextra -Wpedantic)
target_include_directories(axMini_options INTERFACE
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(axMini
  src/main.cpp
  src/VariableEngine.cpp
)

target_include_directories(
  axMini
  PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/cpp-httplib
    ${CMAKE_SOURCE_DIR}/lib/nlohmann-json/single_include
)

target_link_libraries(axMini PRIVATE axMini_options)

add_executable(test_lexer
  src/Lexer.cpp
  tests/test_lexer.cpp
)

target_link_libraries(test_lexer PRIVATE axMini_options)

