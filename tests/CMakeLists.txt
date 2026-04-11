add_executable(test_lexer test_lexer.cpp)
target_link_libraries(test_lexer PRIVATE axMini_core)
target_include_directories(test_lexer PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/doctest
)

add_executable(test_parser test_parser.cpp)
target_link_libraries(test_parser PRIVATE axMini_core)
target_include_directories(test_parser PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/doctest
)

add_executable(test_motor test_motor.cpp)
target_link_libraries(test_motor PRIVATE axMini_core)
target_include_directories(test_motor PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/doctest
)

add_executable(test_valve test_valve.cpp)
target_link_libraries(test_valve PRIVATE axMini_core)
target_include_directories(test_valve PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/doctest
)
