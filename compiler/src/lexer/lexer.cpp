//
// Created by maxmo on 6/20/2026.
//
#include <phonk/lexer/lexer.hpp>
#include <cctype>
#include <sstream>
#include <string>

namespace phonk::lexer {

Lexer::Lexer(const source::SourceFile& source, diagnostics::DiagnosticEngine* diagnosticEngine,
             const LexerOptions options)
    : source_(source), input_(source.getContent()), diagnosticEngine_(diagnosticEngine),
      options_(options) {
}

Token Lexer::nextToken() {
    // Included trivia option to be added later
    if (!options_.includeTrivia) {
        skipTrivia();
    }

    if (isAtEnd()) {
        return makeToken(TokenType::EndOfFile, {offset_});
    }

    if (isAlpha(current())) {
        return readIdentifierOrKeyword();
    }

    if (isDigit(current())) {
        return readNumber();
    }

    if (current() == '"') {
        return readString();
    }

    return readOperatorOrPunctuation();
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens{};

    while (true) {
        Token token{nextToken()};
        const bool isEndOfFile{token.type == TokenType::EndOfFile};

        tokens.push_back(std::move(token));

        if (isEndOfFile) {
            break;
        }
    }

    return tokens;
}

char Lexer::current() const {
    if (isAtEnd()) {
        return '\0';
    }

    return input_[offset_];
}

char Lexer::peek(const std::size_t distance) const {
    const std::size_t position{offset_ + distance};

    if (position >= input_.size()) {
        return '\0';
    }

    return input_[position];
}

char Lexer::advance() {
    return input_[offset_++];
}

bool Lexer::isAtEnd() const {
    return offset_ >= input_.size();
}

bool Lexer::match(const char expected) {
    if (isAtEnd() || current() != expected) {
        return false;
    }

    advance();
    return true;
}

// Cast to unsigned char as negative char values can cause incorrect behavior
bool Lexer::isAlpha(const char character) {
    return character == '_' || std::isalpha(static_cast<unsigned char>(character));
}

bool Lexer::isDigit(const char character) {
    return std::isdigit(static_cast<unsigned char>(character));
}

bool Lexer::isAlphaNumeric(const char character) {
    return character == '_' || std::isalnum(static_cast<unsigned char>(character));
}

bool Lexer::isWhitespace(const char character) {
    return std::isspace(static_cast<unsigned char>(character));
}

void Lexer::skipTrivia() {
    while (!isAtEnd()) {
        if (isWhitespace(current())) {
            advance();
            continue;
        }

        if (current() == '/' && peek() == '/') {
            while (!isAtEnd() && current() != '\n') {
                advance();
            }

            continue;
        }

        if (current() == '/' && peek() == '*') {
            const source::SourceLocation begin{offset_};

            advance(); // Consume '/'
            advance(); // Consume '*'

            bool terminated = false;

            while (!isAtEnd()) {
                if (current() == '*' && peek() == '/') {
                    advance(); // Consume '*'
                    advance(); // Consume '/'

                    terminated = true;
                    break;
                }

                advance();
            }

            if (!terminated) {
                reportError("unterminated block comment", begin);
            }

            continue;
        }

        break; // Current character is not trivia
    }
}

Token Lexer::readIdentifierOrKeyword() {
    const source::SourceLocation begin{offset_};
    std::stringstream ss{};

    while (!isAtEnd() && isAlphaNumeric(current())) {
        ss << current();
        advance();
    }

    return makeToken(keywordType(ss.str()), begin);
}

Token Lexer::readNumber() {
    auto type{TokenType::IntegerLiteral};

    const source::SourceLocation begin = {offset_};

    // Read integer part
    while (!isAtEnd() && isDigit(current())) {
        advance();
    }

    // Read decimal part if present
    if (!isAtEnd() && current() == '.' && isDigit(peek())) {
        type = TokenType::FloatLiteral;
        advance(); // consume '.'
        while (!isAtEnd() && isDigit(current())) {
            advance();
        }
    }

    return makeToken(type, begin);
}

Token Lexer::readString() {
    const source::SourceLocation begin{offset_};

    advance(); // Consume opening "

    while (!isAtEnd() && current() != '"') {
        advance();
    }

    if (isAtEnd()) {
        reportError("unterminated string literal", {offset_});
        return makeToken(TokenType::StringLiteral, begin);
    }

    advance(); // Consume closing "

    return makeToken(TokenType::StringLiteral, begin);;
}

Token Lexer::readOperatorOrPunctuation() {
    const source::SourceLocation begin{offset_};

    const char character = advance();

    switch (character) {
    case '+':
        return makeToken(TokenType::Plus, begin);

    case '-':
        return makeToken(TokenType::Minus, begin);

    case '*':
        return makeToken(TokenType::Star, begin);

    case '/':
        return makeToken(TokenType::Slash, begin);

    case '%':
        return makeToken(TokenType::Percent, begin);

    case '(':
        return makeToken(TokenType::OpenParen, begin);

    case ')':
        return makeToken(TokenType::CloseParen, begin);

    case '{':
        return makeToken(TokenType::OpenBrace, begin);

    case '}':
        return makeToken(TokenType::CloseBrace, begin);

    case '[':
        return makeToken(TokenType::OpenBracket, begin);

    case ']':
        return makeToken(TokenType::CloseBracket, begin);

    case ',':
        return makeToken(TokenType::Comma, begin);

    case '.':
        return makeToken(TokenType::Dot, begin);

    case ';':
        return makeToken(TokenType::Semicolon, begin);

    case ':':
        return makeToken(TokenType::Colon, begin);

    case '=':
        if (match('=')) {
            return makeToken(TokenType::EqualEqual, begin);
        }

        return makeToken(TokenType::Equal, begin);

    case '!':
        if (match('=')) {
            return makeToken(TokenType::BangEqual, begin);
        }

        return makeToken(TokenType::Bang, begin);

    case '<':
        if (match('=')) {
            return makeToken(TokenType::LessEqual, begin);
        }

        return makeToken(TokenType::Less, begin);

    case '>':
        if (match('=')) {
            return makeToken(TokenType::GreaterEqual, begin);
        }

        return makeToken(TokenType::Greater, begin);

    case '&':
        if (match('&')) {
            return makeToken(TokenType::AndAnd, begin);
        }

        break;

    case '|':
        if (match('|')) {
            return makeToken(TokenType::OrOr, begin);
        }

        break;

    default:
        break;
    }

    reportError(
        "Unexpected character '" + std::string(1, character) + "'",
        begin
        );

    return makeToken(TokenType::Unknown, begin);
}

Token Lexer::makeToken(const TokenType type, const source::SourceLocation& begin) const {
    const source::SourceLocation end{offset_};

    const std::string_view lexeme{input_.substr(begin.offset, end.offset - begin.offset)};

    return Token{type, std::string{lexeme}, source::SourceRange{begin, end}};
}

void Lexer::reportError(const std::string& message, const source::SourceLocation& location) const {
    if (diagnosticEngine_ != nullptr) {
        diagnosticEngine_->report(diagnostics::Severity::Error, message, location);
    }
}

TokenType Lexer::keywordType(const std::string_view text) {
    if (text == "phonk") {
        return TokenType::Kw_Phonk;
    }
    if (text == "return") {
        return TokenType::Kw_Return;
    }
    if (text == "returns") {
        return TokenType::Kw_Returns;
    }
    if (text == "if") {
        return TokenType::Kw_If;
    }
    if (text == "else") {
        return TokenType::Kw_Else;
    }
    if (text == "for") {
        return TokenType::Kw_For;
    }
    if (text == "while") {
        return TokenType::Kw_While;
    }
    if (text == "break") {
        return TokenType::Kw_Break;
    }
    if (text == "true") {
        return TokenType::Kw_True;
    }
    if (text == "false") {
        return TokenType::Kw_False;
    }
    if (text == "bool") {
        return TokenType::Kw_Bool;
    }
    if (text == "int") {
        return TokenType::Kw_Int;
    }
    if (text == "float") {
        return TokenType::Kw_Float;
    }
    if (text == "str") {
        return TokenType::Kw_Str;
    }
    if (text == "and") {
        return TokenType::Kw_And;
    }
    if (text == "or") {
        return TokenType::Kw_Or;
    }
    if (text == "not") {
        return TokenType::Kw_Not;
    }

    return TokenType::Identifier;
}

}