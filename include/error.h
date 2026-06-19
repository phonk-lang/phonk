//
// Created by maxmo on 5/22/2026.
//

#ifndef PHONK_LANG_ERROR_H
#define PHONK_LANG_ERROR_H
#include <string>
#include <stdexcept>

class LexerError : public std::runtime_error {
public:
    size_t line;
    size_t col;
    std::string error_message;

    LexerError(const size_t line, const size_t col, const std::string& message)
        : std::runtime_error(buildMessage(line, col, message)),
        line(line), col(col), error_message(message) {}

private:
    static std::string buildMessage(const size_t line, const size_t col, const std::string& msg) {
        return "[Lexer Error] Line " + std::to_string(line) + ", Col " + std::to_string(col) + ": " + msg;
    }
};

class ParserError : public std::runtime_error {
public:
    size_t line;
    size_t col;
    std::string error_message;

    ParserError(const size_t line, const size_t col, const std::string& message)
        : std::runtime_error(buildMessage(line, col, message)),
        line(line), col(col), error_message(message) {}

private:
    static std::string buildMessage(const size_t line, const size_t col, const std::string& msg) {
        return "[Parser Error] Line " + std::to_string(line) + ", Col " + std::to_string(col) + ": " + msg;
    }
};

#endif //PHONK_LANG_ERROR_H
