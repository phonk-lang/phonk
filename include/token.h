//
// Created by maxmo on 5/22/2026.
//

#ifndef CSA_FINAL_TOKEN_H
#define CSA_FINAL_TOKEN_H
#include <string>

enum class TokenType {
    // Literals
    Number,
    String_Lit,
    Identifier,

    // Keywords
    Kw_Fn,
    Kw_Returns,
    Kw_If,
    Kw_Else,
    Kw_For,
    Kw_Print,
    Kw_True,
    Kw_False,
    Kw_Bool,
    Kw_Int,
    Kw_Str,

    // Math
    Plus,
    Minus,
    Star,
    Slash,

    // Symbols
    L_Paren,
    R_Paren,
    L_Brace,
    R_Brace,
    Semicolon,
    Comma,
    Assign,

    // Comparison
    Eq,     // ==
    N_Eq,   // !=
    Lt,     // <
    Gt,     // >
    Lte,    // <=
    Gte,    // >=

    Dot,
    Newline,
    Unknown,
    Eof_Token
};

struct Token {
    TokenType type;
    std::string value;
    size_t line;
    size_t col;
};

#endif //CSA_FINAL_TOKEN_H
