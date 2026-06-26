//
// Created by maxmo on 6/20/2026.
//

#ifndef PHONK_TOKEN_HPP
#define PHONK_TOKEN_HPP
#include <string>
#include <phonk/source/source_range.hpp>

namespace phonk::lexer {

enum class TokenType {
    Unknown,
    EndOfFile,

    Identifier,

    IntegerLiteral,
    FloatLiteral,
    StringLiteral,
    BooleanLiteral,

    Plus,
    Minus,
    Star,
    Slash,
    Percent,

    PlusPlus,
    MinusMinus,

    Equal,
    EqualEqual,
    Bang,
    BangEqual,

    Greater,
    GreaterEqual,
    Less,
    LessEqual,

    AndAnd,
    OrOr,

    OpenParen,
    CloseParen,
    OpenBrace,
    CloseBrace,
    OpenBracket,
    CloseBracket,

    Semicolon,
    Comma,
    Colon,
    Dot,
};

struct Token {
    TokenType type;
    std::string lexeme;
    source::SourceRange range;
};

}

#endif //PHONK_TOKEN_HPP