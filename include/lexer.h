//
// Created by maxmo on 5/22/2026.
//

#ifndef PHONK_LANG_LEXER_H
#define PHONK_LANG_LEXER_H
#include <vector>

#include "token.h"

class Lexer {
public:
    Lexer(std::string  source);

    std::vector<Token> tokenize();

private:
    std::string src_;
    size_t pos_;
    size_t line_;
    size_t col_;

    char current() const;
    char peek() const;
    char advance();
    bool isAtEnd() const;

    void skipWhitespaceAndComments();

    Token makeToken(TokenType type, const std::string& value) const;
    Token makeToken(TokenType type, const std::string& value, size_t col) const;

    Token readNumber();
    Token readString();
    Token readIdentifierOrKeyword();
};

#endif //PHONK_LANG_LEXER_H
