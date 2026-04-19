add_library(axMini_core STATIC
    Logger.cpp
    VariableEngine.cpp
    Lexer.cpp
    Parser.cpp
    AutomationFactory.cpp
    Motor.cpp
    Valve.cpp
    ExecutionEngine.cpp
    DslRuntime.cpp
    PersistenceManager.cpp
)

target_include_directories(axMini_core PUBLIC
    ${CMAKE_SOURCE_DIR}/lib/nlohmann-json/single_include
)

target_link_libraries(axMini_core PUBLIC
  axMini_options
  spdlog::spdlog
)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/data)
target_compile_definitions(axMini_core PUBLIC
    AXMINI_DATA_DIR="${CMAKE_SOURCE_DIR}/data"
)

add_executable(axMini main.cpp)
target_include_directories(axMini PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/cpp-httplib
)
target_link_libraries(axMini PRIVATE axMini_core)

