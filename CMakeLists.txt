cmake_minimum_required(VERSION 4.2)
project(csa_final)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(csa_final
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
