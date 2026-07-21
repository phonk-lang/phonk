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

    Kw_Phonk,
    Kw_Return,
    Kw_Returns,
    Kw_If,
    Kw_Else,
    Kw_For,
    Kw_While,
    Kw_Break,
    Kw_True,
    Kw_False,
    Kw_Bool,
    Kw_Int,
    Kw_Float,
    Kw_Str,
    Kw_And,
    Kw_Or,
    Kw_Not,
};

struct Token {
    TokenType type;
    std::string lexeme;
    source::SourceRange range;
};

}

#endif //PHONK_TOKEN_HPP