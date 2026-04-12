add_library(axMini_core STATIC
    Logger.cpp
    VariableEngine.cpp
    Lexer.cpp
    Parser.cpp
    AutomationFactory.cpp
    Motor.cpp
    Valve.cpp
    ExecutionEngine.cpp
)
target_link_libraries(axMini_core PUBLIC axMini_options spdlog::spdlog)

add_executable(axMini main.cpp)
target_include_directories(axMini PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/cpp-httplib
    ${CMAKE_SOURCE_DIR}/lib/nlohmann-json/single_include
)
target_link_libraries(axMini PRIVATE axMini_core)
