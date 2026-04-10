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
  src/Lexer.cpp
  src/Parser.cpp
  src/AutomationFactory.cpp
  src/Motor.cpp
  src/Valve.cpp
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
  src/Parser.cpp
  tests/test_lexer.cpp
)

target_link_libraries(
  test_lexer
  PRIVATE axMini_options
)

target_include_directories(
  test_lexer
  PRIVATE ${CMAKE_SOURCE_DIR}/tests
)

add_executable(test_parser
  src/Lexer.cpp
  src/Parser.cpp
  tests/test_parser.cpp
)

target_link_libraries(
  test_parser
  PRIVATE axMini_options
)

target_include_directories(
  test_parser
  PRIVATE ${CMAKE_SOURCE_DIR}/tests
)

add_executable(test_motor
  src/VariableEngine.cpp
  src/Motor.cpp
  tests/test_motor.cpp
)

target_link_libraries(
  test_motor
  PRIVATE axMini_options
)

target_include_directories(
  test_motor
  PRIVATE ${CMAKE_SOURCE_DIR}/tests
)

add_executable(test_valve
  src/VariableEngine.cpp
  src/Valve.cpp
  tests/test_valve.cpp
)

target_link_libraries(
  test_valve
  PRIVATE axMini_options
)

target_include_directories(
  test_valve
  PRIVATE ${CMAKE_SOURCE_DIR}/tests
)

