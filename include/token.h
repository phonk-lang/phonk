//
// Created by maxmo on 5/22/2026.
//

#ifndef PHONK_LANG_TOKEN_H
#define PHONK_LANG_TOKEN_H
#include <string>

enum class TokenType {
    // Literals
    Number,
    String_Lit,
    Identifier,

    // Keywords
    Kw_Phonk,
    Kw_Return,
    Kw_Returns,
    Kw_If,
    Kw_Else,
    Kw_While,
    Kw_Print,
    Kw_True,
    Kw_False,
    Kw_Bool,
    Kw_Int,
    Kw_Str,
    Kw_And,
    Kw_Or,
    Kw_Not,

    // Math
    Plus,
    Minus,
    Star,
    Slash,
    Percent,

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

    std::string toString() const {
        return "Token { " +
               std::string("type: ") + tokenTypeToString(type) +
               ", value: \"" + value + "\"" +
               ", line: " + std::to_string(line) +
               ", col: " + std::to_string(col) +
               " }";
    }

    static inline std::string tokenTypeToString(const TokenType t) {
        switch (t) {
            case TokenType::Kw_Phonk:   return "Kw_Phonk";
            case TokenType::Kw_Int:     return "Kw_Int";
            case TokenType::Kw_Bool:    return "Kw_Bool";
            case TokenType::Kw_Str:     return "Kw_Str";
            case TokenType::Kw_If:      return "Kw_If";
            case TokenType::Kw_Else:    return "Kw_Else";
            case TokenType::Kw_While:   return "Kw_While";
            case TokenType::Kw_Print:   return "Kw_Print";
            case TokenType::Kw_Return:  return "Kw_Return";
            case TokenType::Kw_Returns: return "Kw_Returns";
            case TokenType::Kw_True:    return "Kw_True";
            case TokenType::Kw_False:   return "Kw_False";
            case TokenType::Identifier: return "Identifier";
            case TokenType::Number:     return "Number";
            case TokenType::String_Lit: return "String_Lit";
            case TokenType::Plus:       return "Plus";
            case TokenType::Minus:      return "Minus";
            case TokenType::Star:       return "Star";
            case TokenType::Slash:      return "Slash";
            case TokenType::Assign:     return "Assign";
            case TokenType::Eq:         return "Eq";
            case TokenType::N_Eq:       return "N_Eq";
            case TokenType::Lt:         return "Lt";
            case TokenType::Gt:         return "Gt";
            case TokenType::Lte:        return "Lte";
            case TokenType::Gte:        return "Gte";
            case TokenType::L_Paren:    return "L_Paren";
            case TokenType::R_Paren:    return "R_Paren";
            case TokenType::L_Brace:    return "L_Brace";
            case TokenType::R_Brace:    return "R_Brace";
            case TokenType::Semicolon:  return "Semicolon";
            case TokenType::Comma:      return "Comma";
            case TokenType::Dot:        return "Dot";
            case TokenType::Newline:    return "Newline";
            case TokenType::Unknown:    return "Unknown";
            case TokenType::Eof_Token:  return "Eof_Token";
            default:                    return "???";
        }
    }
};

#endif //PHONK_LANG_TOKEN_H
