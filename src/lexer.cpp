#include<string>
#include<unordered_map>

#include "lexer.h"
#include "token.h"

#include "lexer_error.h"

static std::unordered_map<std::string, TokenType> kKeywords = {
    {"fn",      TokenType::Kw_Fn},
    {"return",  TokenType::Kw_Return},
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

Lexer::Lexer(const std::string &source) : src_(source), pos_(0), line_(1), col_(1) {}

char Lexer::current() const {
    return isAtEnd() ? '\0' : src_[pos_];
}

char Lexer::peek() const {
    return (pos_ + 1 >= src_.size()) ? '\0' : src_[pos_ + 1];
}

char Lexer::advance() {
    const char c = src_[pos_++];
    if (c == '\n') {
        line_++;
        col_ = 1;
    } else {
        col_++;
    }
    return c;
}

bool Lexer::isAtEnd() const {
    return pos_ >= static_cast<int>(src_.size());
}

void Lexer::skipWhitespaceAndComments() {
    while (!isAtEnd()) {
        const char c = current();
        if (c == '\n' || c == ' ' || c == '\r' || c == '\t') {
            advance();
        } else if (c == '/' && peek() == '/') {
            // Single-line comment — skip to end of line
            while (!isAtEnd() && current() != '\n')
                advance();
        } else {
            break;
        }
    }
}

Token Lexer::makeToken(const TokenType type, const std::string& value) const {
    return Token{type, value, line_, col_};
}

Token Lexer::makeToken(TokenType type, const std::string& value, const size_t col) const {
    return Token{type, value, line_, col};
}

Token Lexer::readNumber() {
    const size_t token_col = col_;
    const size_t start = pos_;
    while (!isAtEnd() && std::isdigit(current())) {
        advance();
    }
    return Token{TokenType::Number, src_.substr(start, pos_ - start), line_, token_col};
}

Token Lexer::readString() {
    const size_t start_line = line_;   // ← save line
    const size_t start_col  = col_;    // ← save col
    advance(); // consume opening "
    const size_t start = pos_;

    while (!isAtEnd() && current() != '"') {
        advance();
    }

    if (isAtEnd()) {
        throw LexerError(start_line, start_col, "unterminated string literal");
    }

    const std::string value = src_.substr(start, pos_ - start);

    advance(); // consume closing "
    return Token{TokenType::String_Lit, value, start_line, start_col};
}

Token Lexer::readIdentifierOrKeyword() {
    const size_t token_col = col_;
    const size_t start = pos_;
    while (!isAtEnd() && (std::isalnum(current()) || current() == '_')) {
        advance();
    }
    const std::string word = src_.substr(start, pos_ - start);

    const auto it = kKeywords.find(word);
    if (it != kKeywords.end()) {
        return Token{it->second, word, line_, token_col};   // it's a keyword
    }

    return Token{TokenType::Identifier, word, line_, token_col}; // it's a variable/function name
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
        const size_t token_col = col_;
        advance(); // Consume the character
        switch (c) {
            case '(': tokens.push_back(makeToken(TokenType::L_Paren, "(", token_col)); break;
            case ')': tokens.push_back(makeToken(TokenType::R_Paren, ")", token_col)); break;
            case '{': tokens.push_back(makeToken(TokenType::L_Brace, "{", token_col)); break;
            case '}': tokens.push_back(makeToken(TokenType::R_Brace, "}", token_col)); break;
            case ';': tokens.push_back(makeToken(TokenType::Semicolon, ";", token_col)); break;
            case ',': tokens.push_back(makeToken(TokenType::Comma, ",", token_col)); break;
            case '+': tokens.push_back(makeToken(TokenType::Plus, "+", token_col)); break;
            case '-': tokens.push_back(makeToken(TokenType::Minus, "-", token_col)); break;
            case '*': tokens.push_back(makeToken(TokenType::Star, "*", token_col)); break;
            case '/': tokens.push_back(makeToken(TokenType::Slash, "/", token_col)); break;
            case '<':
                if (current() == '=') { advance(); tokens.push_back(makeToken(TokenType::Lte, "<=", token_col)); }
                else tokens.push_back(makeToken(TokenType::Lt, "<", token_col));
                break;
            case '>':
                if (current() == '=') { advance(); tokens.push_back(makeToken(TokenType::Gte, ">=", token_col)); }
                else tokens.push_back(makeToken(TokenType::Gt, ">", token_col));
                break;
            case '=':
                if (current() == '=') { advance(); tokens.push_back(makeToken(TokenType::Eq, "==", token_col)); }
                else tokens.push_back(makeToken(TokenType::Assign, "=", token_col));
                break;
            case '!':
                if (current() == '=') { advance(); tokens.push_back(makeToken(TokenType::N_Eq, "!=", token_col)); }
                else throw LexerError(line_, token_col, "'!' must be followed by '=' (did you mean '!='?)");
                break;
            default:
                throw LexerError(line_, token_col, "unknown character '" + std::string(1, c) + "'");
        }
    }

    return tokens;
}