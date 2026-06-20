//
// Created by maxmo on 6/20/2026.
//

#ifndef PHONK_LEXER_HPP
#define PHONK_LEXER_HPP
#include <vector>
#include <phonk/lexer/Token.hpp>
#include <phonk/source/SourceFile.hpp>

namespace phonk::lexer {

class Lexer {
public:
    explicit Lexer(const source::SourceFile& source);

    std::vector<Token> tokenize();

private:
    source::SourceFile source_;
    size_t pos_;
    size_t line_;
    size_t col_;

    char current() const;

    char peek() const;

    char advance();

    bool isAtEnd() const;

    void skipWhitespaceAndComments();

    Token readIdentifierOrKeyword();

    Token readNumber();

    Token readString();

};

}

#endif //PHONK_LEXER_HPP