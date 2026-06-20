//
// Created by maxmo on 6/20/2026.
//

#ifndef PHONK_TOKEN_HPP
#define PHONK_TOKEN_HPP
#include <string>
#include <phonk/source/SourceLocation.hpp>

namespace phonk::lexer {

enum class TokenType {
    Unknown,
    Identifier,

    // Literals
    NumericLiteral,
    StringLiteral,
    BooleanLiteral,

    // Operators
    Plus,
    Minus,
    Star,
    Slash,
    Percent,
    Increment, // ++
    Decrement, // --
    Eq, // ==
    Bang, // !
    Gt, // >
    Lt, // <
    Gte, // >=
    Lte, // <=

    // Symbols
    OpenParen,
    CloseParen,
    OpenBrace,
    CloseBrace,
    OpenBracket,
    CloseBracket,
    Semicolon,
    Comma,
    Colon,
    Assign,
    Dot,

    Eof
};

struct Token {
    TokenType type;
    std::string lexeme;
    source::SourceLocation location;
};

}

#endif //PHONK_TOKEN_HPP