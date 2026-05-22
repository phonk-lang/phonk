#include<string>
#include<unordered_map>

#include "lexer.h"

#include <stdexcept>

#include "token.h"

static std::unordered_map<std::string, TokenType> KEYWORDS = {
    {"fn",      TokenType::Kw_Fn},
    {"returns", TokenType::Kw_Returns},
    {"if",      TokenType::Kw_If},
    {"else",    TokenType::Kw_Else},
    {"for",     TokenType::Kw_For},
    {"print",   TokenType::Kw_Print},
    {"true",    TokenType::Kw_True},
    {"false",   TokenType::Kw_False},
    {"int",     TokenType::Kw_Int},
    {"bool",    TokenType::Kw_Bool},
    {"str",     TokenType::Kw_Str},
};

Lexer::Lexer(const std::string &source) : src_(source), pos_(0), line_(1) {}

char Lexer::current() const {
    return isAtEnd() ? '\0' : src_[pos_];
}

char Lexer::peek() const {
    return (pos_ + 1 >= src_.size()) ? '\0' : src_[pos_ + 1];
}

char Lexer::advance() {
    return src_[pos_++];
}

bool Lexer::isAtEnd() const {
    return pos_ >= static_cast<int>(src_.size());
}

void Lexer::skipWhitespaceAndComments() {
    while (!isAtEnd()) {
        char c = current();
        if (c == '\n') {
            line_++;
            pos_++;
        } else if (c == ' ' || c == '\r' || c == '\t') {
            pos_++;
        } else if (c == '/' && peek() == '/') {
            // Single-line comment — skip to end of line
            while (!isAtEnd() && current() != '\n')
                pos_++;
        } else {
            break;
        }
    }
}

Token Lexer::makeToken(const TokenType type, const std::string& value) const {
    return Token{type, value, line_};
}

Token Lexer::readNumber() {
    const int start = pos_;
    while (!isAtEnd() && std::isdigit(current())) {
        advance();
    }
    return makeToken(TokenType::Number, src_.substr(start, pos_ - start));
}

Token Lexer::readString() {
    advance(); // consume opening "
    const int start = pos_;

    while (!isAtEnd() && current() != '"') {
        if (current() == '\n') line_++;
        advance();
    }

    if (isAtEnd()) {
        throw std::runtime_error("Line " + std::to_string(line_) + ": unterminated string");
    }

    const std::string value = src_.substr(start, pos_ - start);
    advance(); // consume closing "
    return makeToken(TokenType::String_Lit, value);
}

Token Lexer::readIdentifierOrKeyword() {
    const int start = pos_;
    while (!isAtEnd() && (std::isalnum(current()) || current() == '_'))
        advance();
    const std::string word = src_.substr(start, pos_ - start);

    auto it = KEYWORDS.find(word);
    if (it != KEYWORDS.end()) {
        return makeToken(it->second, word);   // it's a keyword
    }

    return makeToken(TokenType::Identifier, word); // it's a variable/function name
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (true) {
        skipWhitespaceAndComments();

        if (isAtEnd()) {
            tokens.push_back(makeToken(TokenType::Eof_Token, ""));
            break;
        }

        const char c = current();

        // Numbers
        if (std::isdigit(c)) {
            tokens.push_back(readNumber());
            continue;
        }

        // Strings
        if (c == '"') {
            tokens.push_back(readString());
            continue;
        }

        // Identifiers and keywords
        if (std::isalpha(c) || c == '_') {
            tokens.push_back(readIdentifierOrKeyword());
            continue;
        }

        // Anything remaining must be a symbol
        advance(); // Consume the character
        switch (c) {
            case '(': tokens.push_back(makeToken(TokenType::L_Paren, "(")); break;
            case ')': tokens.push_back(makeToken(TokenType::R_Paren, ")")); break;
            case '{': tokens.push_back(makeToken(TokenType::L_Brace, "{")); break;
            case '}': tokens.push_back(makeToken(TokenType::R_Brace, "}")); break;
            case ';': tokens.push_back(makeToken(TokenType::Semicolon, ";")); break;
            case ',': tokens.push_back(makeToken(TokenType::Comma, ",")); break;
            case '+': tokens.push_back(makeToken(TokenType::Plus, "+")); break;
            case '-': tokens.push_back(makeToken(TokenType::Minus, "-")); break;
            case '*': tokens.push_back(makeToken(TokenType::Star, "*")); break;
            case '/': tokens.push_back(makeToken(TokenType::Slash, "/")); break;
            case '<':
                if (current() == '=') { advance(); tokens.push_back(makeToken(TokenType::Lte, "<=")); }
                else tokens.push_back(makeToken(TokenType::Lt, "<"));
                break;
            case '>':
                if (current() == '=') { advance(); tokens.push_back(makeToken(TokenType::Gte, ">=")); }
                else tokens.push_back(makeToken(TokenType::Gt, ">"));
                break;
            case '=':
                if (current() == '=') { advance(); tokens.push_back(makeToken(TokenType::Eq, "==")); }
                else tokens.push_back(makeToken(TokenType::Assign, "="));
                break;
            case '!':
                if (current() == '=') { advance(); tokens.push_back(makeToken(TokenType::N_Eq, "!=")); }
                else throw std::runtime_error("Line " + std::to_string(line_) + ": unexpected '!'");
                break;
            default:
                throw std::runtime_error("Line " + std::to_string(line_) + ": Unrecognized character '" + c + "'");
        }
    }

    return tokens;
}