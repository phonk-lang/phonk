//
// Created by maxmo on 6/26/2026.
//

#include <gtest/gtest.h>
#include <phonk/lexer/lexer.hpp>
#include <phonk/source/source_file.hpp>

TEST(LexerTests, TokenizesIntegerLiteral) {
    const phonk::source::SourceFile sourceFile{"test.phonk", "123"};
    phonk::lexer::Lexer lexer{sourceFile};
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(
        tokens[0].type,
        phonk::lexer::TokenType::IntegerLiteral
        );

    EXPECT_EQ(
        tokens[1].type,
        phonk::lexer::TokenType::EndOfFile
        );
}