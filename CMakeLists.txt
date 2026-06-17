cmake_minimum_required(VERSION 3.20)
project(phonk_lang)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

include(FetchContent)
enable_testing()

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

# Prevent GoogleTest from overriding compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(phonk_lang
        include/Lexer.h
        include/Token.h
        src/main.cpp
        src/Lexer.cpp
        include/error.h
        include/Parser.h
        include/expression.h
        src/parser.cpp
        include/statement.h
        src/transpiler.cpp
        include/transpiler.h
)

add_executable(phonk_lang_tests
        tests/lexer_tests.cpp

        src/Lexer.cpp
        src/transpiler.cpp
        tests/lexer_tests.cpp
        tests/lexer_tests.cpp
)

target_link_libraries(phonk_lang_tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(phonk_lang_tests)