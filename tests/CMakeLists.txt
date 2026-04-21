enable_testing()

add_executable(test_lexer test_lexer.cpp)
target_link_libraries(test_lexer PRIVATE axMini_core)
target_include_directories(test_lexer PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/doctest
)
add_test(NAME test_lexer COMMAND test_lexer)

add_executable(test_parser test_parser.cpp)
target_link_libraries(test_parser PRIVATE axMini_core)
target_include_directories(test_parser PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/doctest
)
add_test(NAME test_parser COMMAND test_parser)

add_executable(test_motor test_motor.cpp)
target_link_libraries(test_motor PRIVATE axMini_core)
target_include_directories(test_motor PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/doctest
)
add_test(NAME test_motor COMMAND test_motor)

add_executable(test_valve test_valve.cpp)
target_link_libraries(test_valve PRIVATE axMini_core)
target_include_directories(test_valve PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/doctest
)
add_test(NAME test_valve COMMAND test_valve)

add_executable(test_engine test_engine.cpp)
target_link_libraries(test_engine PRIVATE axMini_core)
target_include_directories(test_engine PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/doctest
)
add_test(NAME test_engine COMMAND test_engine)

add_executable(test_execution_engine test_execution.cpp)
target_link_libraries(test_execution_engine PRIVATE axMini_core)
target_include_directories(test_execution_engine PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/doctest
)
add_test(NAME test_execution_engine COMMAND test_execution_engine)

add_executable(test_persistence_manager test_persistence.cpp)
target_link_libraries(test_persistence_manager PRIVATE axMini_core)
target_include_directories(test_persistence_manager PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/doctest
)
add_test(NAME test_persistence_manager COMMAND test_persistence_manager)

