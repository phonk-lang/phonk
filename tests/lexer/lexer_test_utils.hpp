//
// Created by maxmo on 6/26/2026.
//

#ifndef PHONK_LEXER_TEST_UTILS_HPP
#define PHONK_LEXER_TEST_UTILS_HPP

#include <gtest/gtest.h>

#include <string>
#include <string_view>
#include <vector>

#include <phonk/lexer/lexer.hpp>
#include <phonk/source/source_file.hpp>

namespace phonk::tests {

struct ExpectedToken {
    lexer::TokenType type;
    std::string_view lexeme;
};

inline std::vector<lexer::Token> lex(std::string_view input) {
    const source::SourceFile sourceFile{
        "test.phonk",
        std::string{input}
    };

    lexer::Lexer lexer{sourceFile};

    return lexer.tokenize();
}

inline void expectTokens(
    std::string_view input,
    const std::vector<ExpectedToken>& expected
    ) {
    const auto tokens = lex(input);

    ASSERT_EQ(tokens.size(), expected.size());

    for (std::size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expected[i].type) << "at token index " << i;
        EXPECT_EQ(tokens[i].lexeme, expected[i].lexeme) << "at token index " << i;
    }
}

}

#endif // PHONK_LEXER_TEST_UTILS_HPP