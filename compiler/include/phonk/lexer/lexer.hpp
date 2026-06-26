//
// Created by maxmo on 6/20/2026.
//

#ifndef PHONK_LEXER_HPP
#define PHONK_LEXER_HPP

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

#include <phonk/diagnostics/diagnostic_engine.hpp>
#include <phonk/lexer/token.hpp>
#include <phonk/source/source_file.hpp>

namespace phonk::lexer {

struct LexerOptions {
    bool includeTrivia = false;
};

class Lexer {
public:
    explicit Lexer(
        const source::SourceFile& source,
        diagnostics::DiagnosticEngine* diagnosticEngine = nullptr,
        LexerOptions options = {}
        );

    Token nextToken();

    std::vector<Token> tokenize();

private:
    struct Cursor {
        std::size_t offset = 0;
    };

    const source::SourceFile& source_;
    std::string_view input_;
    diagnostics::DiagnosticEngine* diagnosticEngine_;
    LexerOptions options_;
    Cursor cursor_;

    char current() const;

    char peek(std::size_t distance = 1) const;

    char advance();

    bool isAtEnd() const;

    bool match(char expected);

    static bool isAlpha(char character);

    static bool isDigit(char character);

    static bool isAlphaNumeric(char character);

    static bool isWhitespace(char character);

    void skipTrivia();

    Token readIdentifierOrKeyword();

    Token readNumber();

    Token readString();

    Token readOperatorOrPunctuation();

    Token makeToken(TokenType type, source::SourceLocation begin) const;

    void reportError(std::string message, source::SourceLocation location);

    static TokenType keywordType(std::string_view text);
};

} // namespace phonk::lexer

#endif // PHONK_LEXER_HPP