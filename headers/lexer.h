//
// Created by maxmo on 5/22/2026.
//

#ifndef CSA_FINAL_LEXER_H
#define CSA_FINAL_LEXER_H
#include <vector>

#include "token.h"

class Lexer {
public:
    Lexer(const std::string& source);

    std::vector<Token> tokenize();

private:
    std::string src_;
    int pos_;
    int line_;

    char current() const;
    char peek() const;
    char advance();
    bool isAtEnd() const;

    void skipWhitespaceAndComments();

    Token makeToken(TokenType type, const std::string& value) const;

    Token readNumber();
    Token readString();
    Token readIdentifierOrKeyword();
};

#endif //CSA_FINAL_LEXER_H
